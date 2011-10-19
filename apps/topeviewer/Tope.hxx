//
// Four-dimensional polytope.
//

#ifndef apps_topeviewer_Tope_hxx
#define apps_topeviewer_Tope_hxx

#include "Tube.hxx"
#include <esve/geom/dim3/Icosahedron.hxx>
#include <esve/util/member_iterator.hxx>
#include <esve/types/rgba.hxx>
#include <esve/types/quat.hxx>
#include <esve/gl/gl.hxx>
#include <vector>

class Tope
{
public:
    //////////////////////////////////////////////
    // types

    typedef unsigned int size_type ;

    struct Edge_Length_Interval
    {
        esve::types::real smallest_length ;
        esve::types::real largest_length ;

        Edge_Length_Interval( esve::types::real smallest_length_,
                              esve::types::real largest_length_ )
            : smallest_length(smallest_length_),
              largest_length(largest_length_) { }
    } ;

    //////////////////////////////////////////////
    // constructor
    Tope() ;

    //////////////////////////////////////////////
    // compiler writes memberwise copy and assign

    //////////////////////////////////////////////
    // read new set of points
    template< typename Input_Iterator >
    void points( Input_Iterator begin, Input_Iterator end ) ;

    //////////////////////////////////////////////
    // do not show edges less than this length

    esve::types::real min_length() const
    {
        return m_min_length ;
    }

    void min_length( esve::types::real a )
    {
        m_write_param(&m_min_length, a, &m_need_compute_edges) ;
    }

    //////////////////////////////////////////////
    // do not show edges greater than this length

    esve::types::real max_length() const
    {
        return m_max_length ;
    }

    void max_length( esve::types::real a )
    {
        m_write_param(&m_max_length, a, &m_need_compute_edges) ;
    }

    //////////////////////////////////////////////
    // shift the hue; mod by 1

    esve::types::real slide_color() const
    {
        return m_slide_color ;
    }

    void slide_color( esve::types::real a )
    {
        m_write_param(&m_slide_color, a, &m_need_compute_edges) ;
    }

    //////////////////////////////////////////////
    // edges which have a point closer than this are not shown

    esve::types::real cut_edges_min() const
    {
        return m_cut_edges_min ;
    }

    void cut_edges_min( esve::types::real a )
    {
        m_write_param(&m_cut_edges_min, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // edges which have a point farther than this are not shown

    esve::types::real cut_edges_max() const
    {
        return m_cut_edges_max ;
    }

    void cut_edges_max( esve::types::real a )
    {
        m_write_param(&m_cut_edges_max, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // points which are closer than this are not shown

    esve::types::real cut_balls_min() const
    {
        return m_cut_balls_min ;
    }

    void cut_balls_min( esve::types::real a )
    {
        m_write_param(&m_cut_balls_min, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // points which are farther than this are not shown

    esve::types::real cut_balls_max() const
    {
        return m_cut_balls_max ;
    }

    void cut_balls_max( esve::types::real a )
    {
        m_write_param(&m_cut_balls_max, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // radius of the ball enclosing each point

    esve::types::real ball_radius() const
    {
        return m_ball_radius ;
    }

    void ball_radius( esve::types::real a )
    {
        m_write_param(&m_ball_radius, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // radius of the tubes connecting points

    esve::types::real tube_radius() const
    {
        return m_tube_radius ;
    }

    void tube_radius( esve::types::real a )
    {
        m_write_param(&m_tube_radius, a, &m_need_transform) ;
    }

    //////////////////////////////////////////////
    // length-wise resolution of each tube

    size_type tube_length_res() const
    {
        return m_tube.length_res() ;
    }

    void tube_length_res( size_type a ) ;

    //////////////////////////////////////////////
    // wrap-wise resolution of each tube

    size_type tube_wrap_res() const
    {
        return m_tube.wrap_res() ;
    }

    void tube_wrap_res( size_type a ) ;

    //////////////////////////////////////////////
    // the (smallest, largest) of all edge lengths.
    const Edge_Length_Interval & edge_length_interval() const
    {
        return m_edge_length_interval ;
    }

    virtual ~Tope() ;

private:
    //////////////////////////////////////////////
    // private
    
    struct m_Vertex
    {
        typedef esve::types::quat Transformed_Point ;
        typedef esve::types::quat Point ;

        esve::types::quat transformed_point ;
        esve::types::quat point ;
        esve::types::real pure_point_abs ;
        bool pure_point_isnan ;
        bool ball_visible ;

        m_Vertex( const Transformed_Point & transformed_point_,
                  const Point & point_,
                  esve::types::real pure_point_abs_,
                  bool pure_point_isnan_,
                  bool ball_visible_ )
            : transformed_point(transformed_point_),
              point(point_),
              pure_point_abs(pure_point_abs_),
              pure_point_isnan(pure_point_isnan_),
              ball_visible(ball_visible_) { }
    } ;

    struct m_Edge
    {
        typedef GLuint Vertex_Index ;

        Vertex_Index index0 ;
        Vertex_Index index1 ;
        esve::types::rgba color ;
        bool visible ;

        m_Edge( Vertex_Index index0_,
                Vertex_Index index1_,
                const esve::types::rgba & color_,
                bool visible_ )
            : index0(index0_),
              index1(index1_),
              color(color_),
              visible(visible_) { }
    } ;

    struct m_Icos : private esve::geom::dim3::Icosahedron
    {
        using Icosahedron::draw ;
    } ;
    
    typedef Tube m_Tube ;

    typedef std::vector<m_Vertex> m_Vertices ;
    typedef std::vector<m_Edge> m_Edges ;

    typedef m_Vertices::iterator m_Vertices_iterator ;
    typedef m_Vertices::const_iterator m_Vertices_const_iterator ;

    void m_write_param( esve::types::real*, esve::types::real, bool* flag ) ;
    void m_write_param( size_type*, size_type, bool* flag ) ;
    void m_compute_vertices() ;
    void m_compute_edges() ;
    void m_cut_edges() ;
    void m_compute_tubes() ;
    Edge_Length_Interval m_compute_edge_length_interval() const ;

    m_Vertices m_vertices ;
    m_Edges m_edges ;
    m_Tube m_tube ;
    m_Icos m_icos ;
    Edge_Length_Interval m_edge_length_interval ;

    bool m_need_compute_edges ;
    bool m_need_compute_tube ;
    bool m_need_transform ;

    esve::types::real m_min_length ;
    esve::types::real m_max_length ;
    esve::types::real m_slide_color ;
    esve::types::real m_cut_edges_min ;
    esve::types::real m_cut_edges_max ;
    esve::types::real m_cut_balls_min ;
    esve::types::real m_cut_balls_max ;
    esve::types::real m_ball_radius ;
    esve::types::real m_tube_radius ;

protected:
    //////////////////////////////////////////////
    // OpenGL drawing routine
    virtual void draw() ;

    //////////////////////////////////////////////
    // Individual draw() functions for overriding color, lighting, etc

    virtual void draw_balls() ;
    virtual void draw_tubes() ;
    virtual void draw_lines() ;

    //////////////////////////////////////////////
    // The following are hooks into the Moebius frame system.
    // See Make_Frame.hxx.

    typedef
    esve::util::member_iterator< m_Vertices_const_iterator,
                                 const m_Vertex::Point,
                                 &m_Vertex::point >
    Points_iterator ;

    typedef
    esve::util::member_iterator< m_Vertices_iterator,
                                 m_Vertex::Transformed_Point,
                                 &m_Vertex::transformed_point >
    Transformed_Points_iterator ;

    Points_iterator points_begin() const
    {
        return Points_iterator(m_vertices.begin()) ;
    }

    Points_iterator points_end() const
    {
        return Points_iterator(m_vertices.end()) ;
    }

    Transformed_Points_iterator transformed_points_begin()
    {
        return Transformed_Points_iterator(m_vertices.begin()) ;
    }

    virtual bool changed() const ;
    virtual void pretransform() ;
    virtual void posttransform() ;
} ;

template< typename Input_Iterator >
void
Tope::
points( Input_Iterator begin, Input_Iterator end )
{
    m_vertices.clear() ;

    for( ; begin != end ; ++begin )
    {
        m_vertices.push_back(m_Vertex(esve::types::quat(),
                                      *begin,
                                      0,
                                      false,
                                      false)) ;
    }

    m_edge_length_interval = m_compute_edge_length_interval() ;
    m_need_compute_edges = true ;
}

#endif

