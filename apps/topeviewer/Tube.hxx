//
// A tube of radius 1 extending from the origin to (1, 0, 0), centered
// along (1, 0, 0).
//

#ifndef apps_topeviewer_Tube_hxx
#define apps_topeviewer_Tube_hxx

#include <esve/base/dimn/vertex/NP_Vertex.hxx>
#include <esve/math/complex.hxx>
#include <esve/types/pure.hxx>
#include <vector>
#include <cstddef>

class Tube
{
public:
    ////////////////////////////////////////////
    // types

    typedef std::size_t size_type ;
    
    ////////////////////////////////////////////
    // Constructor
    Tube() ;

    ////////////////////////////////////////////
    // compiler writes memberwise copy and assign

    ////////////////////////////////////////////
    // wrap resolution

    size_type wrap_res() const
    {
        return m_wrap_res ;
    }

    void wrap_res( size_type a )
    {
        m_write_param(&m_wrap_res, a) ;
    }

    ////////////////////////////////////////////
    // length resolution

    size_type length_res() const
    {
        return m_length_res ;
    }

    void length_res( size_type a )
    {
        m_write_param(&m_length_res, a) ;
    }

    ////////////////////////////////////////////
    // OpenGL rendering
    void draw() ;

    ////////////////////////////////////////////
    // computations
    void compute() ;

    ////////////////////////////////////////////
    // destructor
    ~Tube() ;

private:
    typedef
    esve::base::dimn::vertex::NP_Vertex
    <
        esve::types::pure, // normal
        esve::types::pure  // point
    >
    m_Vertex ;

    typedef esve::math::complex<double> m_complex ;
    typedef std::vector<m_Vertex> m_Vertices ;
    typedef m_Vertices::size_type m_size_type ;
    typedef std::vector<m_complex> m_Ridges ;
    typedef std::vector<m_complex> m_Normals ;

    Tube( const Tube & ) ;
    Tube & operator=( const Tube & ) ;

    void m_write_param( m_size_type* v, m_size_type a ) ;

    m_Vertices m_vertices ;
    m_Ridges m_ridges ;
    m_Normals m_normals ;
    m_size_type m_length_res ;
    m_size_type m_wrap_res ;
    bool m_need_compute ;
} ;

#endif
