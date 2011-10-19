
#include "Torus.hxx"
#include "torus_func.hxx"
#include <esve/math/constants.hxx>
#include <esve/math/complex.hxx>
#include <cmath>

typedef esve::math::complex<double> complex ;

const double PI_4 = double(esve::math::constants::PI_4) ;

Torus::
Torus()
    : m_vertices(),
      m_ratio_angle(PI_4),
      m_width_res(24),
      m_height_res(24),
      m_width(24),
      m_height(24),
      m_gap(0),
      m_skew(0),
      m_wind_u(1),
      m_wind_v(0),
      m_need_compute(true)
{
}

Torus::
~Torus()
{
}

void
Torus::
m_write_param( double* v, double a )
{
    if( *v != a )
    {
        *v = a ;
        m_need_compute = true ;
    }
}

void
Torus::
m_write_param( size_type* v, size_type a )
{
    if( *v != a )
    {
        *v = a ;
        m_need_compute = true ;
    }
}

void
Torus::
m_compute_torus()
{
    m_vertices.clear() ;

    if( m_width_res == 0 || m_height_res == 0 ||
        (m_wind_u == 0.0 && m_wind_v == 0.0) )
    {
        return ;
    }

    const double r1 = std::cos(m_ratio_angle) ;
    const double r2 = std::sin(m_ratio_angle) ;
    const double skew_factor = m_skew ;

    const complex stretch_factor =
        torus_func::stretch_factor(complex(m_wind_u, m_wind_v)) ;

    const complex rotation_factor =
        torus_func::rotation_factor(complex(m_wind_u, m_wind_v)) ;

    const double t = m_gap ;

    const complex l_res = complex(1.0/m_width_res, 1.0/m_height_res) ;

    const double w = m_width ;
    const double h = m_height ;

    const bool urem = m_width - int(m_width) != 0 ;
    const bool vrem = m_height - int(m_height) != 0 ;

    const int m = urem ? int(m_width) + 1 : int(m_width) ;
    const int n = vrem ? int(m_height) + 1 : int(m_height) ;

    complex p0 ;
    complex p1 ;
    complex p2 ;
    complex p3 ;

    double u = -1 ;
    double v = -1 ;

    m_vertices.reserve(4*m*n) ;

    for( int j = 0 ; j != n ; ++j )
    {
        for( int i = 0 ; i != m ; ++i )
        {
            u = double(i) ;
            v = double(j) ;

            if( urem && vrem && i == m - 1 && j == n - 1 )
            {
                p0 = complex(u + t,       v          ) ;
                p1 = complex(w,           v + t      ) ;
                p2 = complex(w - t,       h          ) ;
                p3 = complex(u,           h - t      ) ;
            }
            else if( urem && i == m - 1 )
            {
                p0 = complex(u + t,       v          ) ;
                p1 = complex(w,           v + t      ) ;
                p2 = complex(w - t,       v + 1.0    ) ;
                p3 = complex(u,           v + 1.0 - t) ;
            }
            else if( vrem && j == n - 1 )
            {
                p0 = complex(u + t,       v          ) ;
                p1 = complex(u + 1.0,     v + t      ) ;
                p2 = complex(u + 1.0 - t, h          ) ;
                p3 = complex(u,           h - t      ) ;
            }
            else
            {
                p0 = complex(u + t,       v          ) ;
                p1 = complex(u + 1.0,     v + t      ) ;
                p2 = complex(u + 1.0 - t, v + 1.0    ) ;
                p3 = complex(u,           v + 1.0 - t) ;
            }

            m_vertices.push_back(
                torus_func::torus_vertex<complex, m_Vertex>(
                    torus_func::stretch(p0, l_res),
                    r1,
                    r2,
                    skew_factor,
                    stretch_factor,
                    rotation_factor)) ;

            m_vertices.push_back(
                torus_func::torus_vertex<complex, m_Vertex>(
                    torus_func::stretch(p1, l_res),
                    r1,
                    r2,
                    skew_factor,
                    stretch_factor,
                    rotation_factor)) ;

            m_vertices.push_back(
                torus_func::torus_vertex<complex, m_Vertex>(
                    torus_func::stretch(p2, l_res),
                    r1,
                    r2,
                    skew_factor,
                    stretch_factor,
                    rotation_factor)) ;

            m_vertices.push_back(
                torus_func::torus_vertex<complex, m_Vertex>(
                    torus_func::stretch(p3, l_res),
                    r1,
                    r2,
                    skew_factor,
                    stretch_factor,
                    rotation_factor)) ;
        }
    }
}

void
Torus::
m_compute_normals()
{
    for( m_Vertices::iterator i = m_vertices.begin() ;
         i != m_vertices.end() ;
         i += 4 )
    {
        (*i).normal
            = (*(i+1)).normal
            = (*(i+2)).normal
            = (*(i+3)).normal
            = cross(purepart((*(i+1)).transformed_point -
                             (*i).transformed_point),
                    purepart((*(i+3)).transformed_point -
                             (*i).transformed_point)) ;
    }
}

bool
Torus::
changed() const
{
    return m_need_compute ;
}

void
Torus::
pretransform()
{
    if( m_need_compute )
    {
        m_compute_torus() ;
        m_need_compute = false ;
    }
}

void
Torus::
posttransform()
{
    m_compute_normals() ;
}

void
Torus::
draw()
{
    if( m_vertices.size() != 0 )
    {
        glInterleavedArrays(
            GL_C4F_N3F_V3F,
            sizeof(m_Vertex),
            static_cast<const GLvoid*>(&*m_vertices.begin())) ;

        glDrawArrays(GL_QUADS, 0, m_vertices.size()) ;
    }
}

