
#ifndef esve_surface_base_Packed_Quad_hxx
#define esve_surface_base_Packed_Quad_hxx

namespace esve { namespace surface { namespace base {

template< typename T_Vertex_Index >
class Packed_Quad
{
private:
    typedef T_Vertex_Index m_Vertex_Index ;

    m_Vertex_Index m[4] ;

public:
    typedef m_Vertex_Index Vertex_Index ;
    typedef Vertex_Index* Vertex_Indexes_iterator ;
    typedef const Vertex_Index* Vertex_Indexes_const_iterator ;

    Packed_Quad( Vertex_Index m0,
                 Vertex_Index m1,
                 Vertex_Index m2,
                 Vertex_Index m3 )
    {
        m[0] = m0 ;
        m[1] = m1 ;
        m[2] = m2 ;
        m[3] = m3 ;
    }

    // compiler writes memberwise copy and assign

    Vertex_Index vertex_indexes_0() const
    {
        return m[0] ;
    }

    Vertex_Index vertex_indexes_1() const
    {
        return m[1] ;
    }

    Vertex_Index vertex_indexes_2() const
    {
        return m[2] ;
    }

    Vertex_Index vertex_indexes_3() const
    {
        return m[3] ;
    }

    Vertex_Index vertex_indexes_front() const
    {
        return m[0] ;
    }

    Vertex_Index vertex_indexes_back() const
    {
        return m[3] ;
    }

    Vertex_Indexes_const_iterator vertex_indexes_begin() const
    {
        return m ;
    }

    Vertex_Indexes_iterator vertex_indexes_begin()
    {
        return m ;
    }

    Vertex_Indexes_const_iterator vertex_indexes_end() const
    {
        return m + 4 ;
    }

    Vertex_Indexes_iterator vertex_indexes_end()
    {
        return m + 4 ;
    }
} ;

}}} // namespace esve::surface::base

#endif

