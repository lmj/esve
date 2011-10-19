
#include "Tope.hxx"
#include <esve/math/misc.hxx>
#include <esve/base/dim3/transform_util.hxx>
#include <esve/gl/gl.hxx>
#include <cmath>
#include <limits>

using esve::math::misc::fmodp ;
using esve::base::dim3::transform_util::build_matrix ;
using esve::types::real ;
using esve::types::quat ;
using esve::types::pure ;
using esve::types::rgba ;
using esve::gl::gl ;

const real TOLERANCE = 0.0001 ;

namespace {

//
// Find an arbitrary pure orthogonal to u.
//
pure find_orthogonal( const pure & u, real tolerance )
{
    {
        const pure v = cross(u, pure(1, 0, 0)) ;
        const real abs_v = abs(v) ;
        
        if( abs_v > tolerance )
        {
            return v/abs_v ;
        }
    }
    
    //
    // u is close to i or -i.  Choose j.
    //
    const pure v = cross(u, pure(0, 1, 0)) ;
    return v/abs(v) ;
}

//
// Find a quat r for which r*u*conj(r) == v.
//
quat rotate_u_to_v( const pure & u,
                    const pure & v,
                    real tolerance )
{
    {
        const pure r = u + v ;
        const real abs_r = abs(r) ;
        
        if( abs_r > tolerance )
        {
            return quat(r/abs_r) ;
        }
    }

    //
    // u and v are close to antipodal.
    //
    // Rotate u to -v, then rotate by pi around an arbitrary axis
    // orthogonal to v.
    //
    // Such is the complication of finding ourselves near a crosscap.
    //
    const quat r = find_orthogonal(v, tolerance)*(u - v) ;
    return r/abs(r) ;
}

inline
bool isnan( const pure & a )
{
    return
        std::isnan(a.x()) ||
        std::isnan(a.y()) ||
        std::isnan(a.z()) ;
}

} // anon namespace

Tope::
Tope()
    : m_vertices(),
      m_edges(),
      m_tube(),
      m_icos(),
      m_edge_length_interval(0, 0),
      m_need_compute_edges(true),
      m_need_compute_tube(true),
      m_need_transform(true),
      m_min_length(0.0),
      m_max_length(0.0),
      m_slide_color(0.0),
      m_cut_edges_min(0.0),
      m_cut_edges_max(100.0),
      m_cut_balls_min(0.0),
      m_cut_balls_max(100.0),
      m_ball_radius(0.0),
      m_tube_radius(0.0)
{
}

Tope::
~Tope()
{
}

void
Tope::
m_write_param( real* v, real a, bool* flag )
{
    if( *v != a )
    {
        *v = a ;
        *flag = true ;
    }
}

void
Tope::
m_write_param( size_type* v, size_type a, bool* flag )
{
    if( *v != a )
    {
        *v = a ;
        *flag = true ;
    }
}

void
Tope::
tube_length_res( size_type a )
{
    if( m_tube.length_res() != a )
    {
        m_tube.length_res(a) ;

        if( m_tube_radius != 0 )
        {
            m_need_compute_tube = true ;
        }
    }
}

void
Tope::
tube_wrap_res( size_type a )
{
    if( m_tube.wrap_res() != a )
    {
        m_tube.wrap_res(a) ;

        if( m_tube_radius != 0 )
        {
            m_need_compute_tube = true ;
        }
    }
}

void
Tope::
m_compute_edges()
{
    m_edges.clear() ;

    if( m_vertices.size() == 0 )
    {
        return ;
    }

    // 
    // Skip the usual reserve().  The n*(n-1)/2 edges would probably
    // go mostly unused.
    //

    for( m_Vertices::size_type i = 0 ; i != m_vertices.size() - 1 ; ++i )
    {
        for( m_Vertices::size_type j = i + 1 ; j != m_vertices.size() ; ++j )
        {
            const real len = abs(m_vertices[i].point - m_vertices[j].point) ;

            if( len >= m_min_length && len <= m_max_length )
            {
                real hue = (len - m_min_length)/(m_max_length - m_min_length) ;

                hue = fmodp(hue + m_slide_color, real(1)) ;

                m_edges.push_back(m_Edge(m_Edge::Vertex_Index(i),
                                         m_Edge::Vertex_Index(j),
                                         rgba::from_hsva(hue, 1, 1, 1),
                                         true)) ;
            }
        }
    }
}

Tope::Edge_Length_Interval
Tope::
m_compute_edge_length_interval() const
{
    if( m_vertices.size() < 2 )
    {
        return Edge_Length_Interval(0, 0) ;
    }

    real smallest = std::numeric_limits<real>::max() ;
    real largest = real(0) ;

    for( m_Vertices::size_type i = 0 ; i != m_vertices.size() - 1 ; ++i )
    {
        for( m_Vertices::size_type j = i + 1 ; j != m_vertices.size() ; ++j )
        {
            const real len = abs(m_vertices[i].point - m_vertices[j].point) ;

            if( len < smallest )
            {
                smallest = len ;
            }

            if( len > largest )
            {
                largest = len ;
            }
        }
    }

    return Edge_Length_Interval(smallest, largest) ;
}

void
Tope::
m_compute_vertices()
{
    for( m_Vertices::iterator i = m_vertices.begin() ;
         i != m_vertices.end() ;
         ++i )
    {
        (*i).pure_point_isnan =
            isnan(purepart((*i).transformed_point)) ;

        (*i).pure_point_abs =
            abs(purepart((*i).transformed_point)) ;

        (*i).ball_visible =
            (*i).pure_point_abs >= m_cut_balls_min
            &&
            (*i).pure_point_abs <= m_cut_balls_max
            &&
            !(*i).pure_point_isnan ;
    }
}

void
Tope::
m_cut_edges()
{
    for( m_Edges::iterator ei = m_edges.begin() ;
         ei != m_edges.end() ;
         ++ei )
    {
        (*ei).visible =

            m_vertices[(*ei).index0].pure_point_abs >= m_cut_edges_min &&
            m_vertices[(*ei).index0].pure_point_abs <= m_cut_edges_max &&

            m_vertices[(*ei).index1].pure_point_abs >= m_cut_edges_min &&
            m_vertices[(*ei).index1].pure_point_abs <= m_cut_edges_max &&

            !m_vertices[(*ei).index0].pure_point_isnan &&
            !m_vertices[(*ei).index1].pure_point_isnan ;
    }
}

bool
Tope::
changed() const
{
    return
        m_need_compute_edges
        ||
        m_need_compute_tube
        ||
        m_need_transform ;
}

void
Tope::
pretransform()
{
    if( m_need_compute_edges )
    {
        m_compute_edges() ;
        m_need_compute_edges = false ;
    }
}

void
Tope::
posttransform()
{
    m_compute_vertices() ;
    m_cut_edges() ;

    if( m_need_compute_tube )
    {
        m_tube.compute() ;
        m_need_compute_tube = false ;
    }

    m_need_transform = false ;
}

void
Tope::
draw_lines()
{
    gl::Begin sentry(GL_LINES) ;
    
    for( m_Edges::const_iterator ei = m_edges.begin() ;
         ei != m_edges.end() ;
         ++ei )
    {
        if( (*ei).visible )
        {
            glColor3fv((*ei).color.data()) ;
            glVertex3fv(m_vertices[(*ei).index0].transformed_point.data()) ;
            glVertex3fv(m_vertices[(*ei).index1].transformed_point.data()) ;
        }
    }
}

void
Tope::
draw_tubes()
{
    for( m_Edges::iterator ei = m_edges.begin() ;
         ei != m_edges.end() ;
         ++ei )
    {
        if( (*ei).visible )
        {
            const pure p0 =
                purepart(m_vertices[(*ei).index0].transformed_point) ;

            const pure p1 =
                purepart(m_vertices[(*ei).index1].transformed_point) ;

            pure v = p1 - p0 ;
            
            const real length = abs(v) ;
            v /= length ;
            
            {
                gl::PushMatrix sentry ;

                GLfloat glmat[16] ;

                build_matrix(rotate_u_to_v(pure(1, 0, 0), v, TOLERANCE),
                             p0,
                             real(1),
                             glmat) ;

                glMultMatrixf(glmat) ;

                glScalef(GLfloat(length),
                         GLfloat(m_tube_radius),
                         GLfloat(m_tube_radius)) ;

                glColor3fv((*ei).color.data()) ;

                m_tube.draw() ;
            }
        }
    }
}

void
Tope::
draw_balls()
{
    for( m_Vertices::const_iterator i = m_vertices.begin() ;
         i != m_vertices.end() ;
         ++i )
    {
        if( (*i).ball_visible )
        {
            gl::PushMatrix sentry ;

            glTranslatef((*i).transformed_point.x(),
                         (*i).transformed_point.y(),
                         (*i).transformed_point.z()) ;

            glScalef(m_ball_radius,
                     m_ball_radius,
                     m_ball_radius) ;

            m_icos.draw() ;
        }
    }
}

void
Tope::
draw()
{
    if( m_tube_radius == real(0) )
    {
        draw_lines() ;
    }
    else
    {
        draw_tubes() ;
    }

    if( m_ball_radius != real(0) )
    {
        draw_balls() ;
    }
}
