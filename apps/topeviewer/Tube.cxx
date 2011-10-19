
#include "Tube.hxx"
#include <esve/math/constants.hxx>

using esve::types::real ;
using esve::types::pure ;

const double TWO_PI = double(esve::math::constants::TWO_PI) ;
const double PI = double(esve::math::constants::PI) ;

Tube::
Tube()
    : m_vertices(),
      m_ridges(),
      m_normals(),
      m_length_res(0),
      m_wrap_res(0),
      m_need_compute(false)
{
}

Tube::
~Tube()
{
}

void
Tube::
m_write_param( size_type* v, size_type a )
{
    if( *v != a )
    {
        *v = a ;
        m_need_compute = true ;
    }
}

void
Tube::
compute()
{
    typedef m_complex complex ;
    
    if( !m_need_compute )
    {
        return ;
    }
    
    m_vertices.clear() ;
    m_vertices.reserve(4*m_length_res*m_wrap_res) ;

    m_ridges.clear() ;
    m_ridges.reserve(m_wrap_res) ;

    m_normals.clear() ;
    m_normals.reserve(m_wrap_res) ;

    const real wrap_res = real(m_wrap_res) ;
    const real length_res = real(m_length_res) ;

    for( size_type g = 0 ; g != m_wrap_res ; ++g )
    {
        m_normals.push_back(exp((double(g)*TWO_PI/wrap_res)
                                *
                                complex(0, 1))) ;
        
        m_ridges.push_back(exp(((double(2)*double(g) - double(1))*PI/wrap_res)
                               *
                               complex(0, 1))) ;
    }

    for( size_type g = 0 ; g != m_wrap_res ; ++g )
    {
        const pure normal = pure(real(0),
                                 m_normals[g].real(),
                                 m_normals[g].imag()) ;
        
        for( size_type h = 0 ; h != m_length_res ; ++h )
        {
            m_vertices.push_back(m_Vertex(
                normal,
                pure(real(h)/length_res,
                     m_ridges[g].real(),
                     m_ridges[g].imag()))) ;
                                          
            m_vertices.push_back(m_Vertex(
                normal,
                pure(real(h)/length_res,
                     m_ridges[(g + 1) % m_wrap_res].real(),
                     m_ridges[(g + 1) % m_wrap_res].imag()))) ;
                                          
            m_vertices.push_back(m_Vertex(
                normal,
                pure(real(h + 1)/length_res,
                     m_ridges[(g + 1) % m_wrap_res].real(),
                     m_ridges[(g + 1) % m_wrap_res].imag()))) ;
                     
            m_vertices.push_back(m_Vertex(
                normal,
                pure(real(h + 1)/length_res,
                     m_ridges[g].real(),
                     m_ridges[g].imag()))) ;
        }
    }

    m_need_compute = false ;
}

void
Tube::
draw()
{
    if( m_vertices.size() != 0 )
    {
        glInterleavedArrays(
            GL_N3F_V3F,
            sizeof(m_Vertex),
            static_cast<const GLvoid*>(&*m_vertices.begin())) ;

        glDrawArrays(GL_QUADS, 0, m_vertices.size()) ;
    }
}

