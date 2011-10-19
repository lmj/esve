//
// Boundaries of a clipped Packed_Surface originally formed by a
// Rectangular_Domain (such as a Rectangular_Surface).
//

#ifndef esve_surface_base_Rectangular_Boundaries_hxx
#define esve_surface_base_Rectangular_Boundaries_hxx

#include <vector>

namespace esve { namespace surface { namespace base {

/////////////////////////////////////////////////////
//
// Rectangular_Boundaries
//
/////////////////////////////////////////////////////

template< typename T_Surface >
class Rectangular_Boundaries
{
private:
    typedef T_Surface m_Surface ;

    typedef typename m_Surface::Facet::Vertex_Index m_Vertex_Index ;

    typedef std::vector<m_Vertex_Index> m_Vertex_Indexes ;
    typedef typename m_Vertex_Indexes::size_type m_Vertex_Indexes_size_type ;

    // vector<bool> is slow
    typedef std::vector<char> m_Marked_Vertices ;

    typedef std::vector<m_Vertex_Indexes> m_List ;
    typedef typename m_List::iterator m_List_iterator ;
    typedef typename m_List::const_iterator m_List_const_iterator ;
    typedef typename m_List::size_type m_List_size_type ;

    typedef typename
    m_Surface::Vertices_const_iterator
    m_Vertices_const_iterator ;

    typedef typename
    m_Surface::Vertices_size_type
    m_Vertices_size_type ;

    typedef typename
    m_Surface::Facets_Around_Vertex_const_iterator
    m_Facets_Around_Vertex_const_iterator ;

    struct m_Pair
    {
        m_Vertex_Index vertex_index ;
        signed char direction ;

        m_Pair( m_Vertex_Index v,
                signed char d )
            : vertex_index(v),
              direction(d) { }

        bool operator<( const m_Pair & a ) const
        {
            return vertex_index < a.vertex_index ;
        }
    } ;

    typedef std::vector<m_Pair> m_Pairs ;
    typedef typename m_Pairs::const_iterator m_Pairs_const_iterator ;

    static bool m_boundary_vertex( m_Vertices_const_iterator v,
                                   const m_Surface & surface )
    {
        return
            surface.facets_around_vertex_size(v) < 4
            &&
            surface.facets_around_vertex_size(v) > 0 ;
    }

    static bool m_boundary_vertex( m_Vertex_Index index,
                                   const m_Surface & surface )
    {
        return
            surface.
            facets_around_vertex_size(surface.vertices_begin() + index) < 4
            &&
            surface.
            facets_around_vertex_size(surface.vertices_begin() + index) > 0 ;
    }

    static void m_compute_boundary_fast(
        const m_Surface & surface,
        m_Vertex_Index start,
        m_Marked_Vertices & marked_vertices,
        m_Vertex_Indexes & boundary ) ;

    static void m_compute_boundary(
        const m_Surface & surface,
        m_Vertex_Index start,
        m_Marked_Vertices & marked_vertices,
        m_Vertex_Indexes & boundary ) ;

    m_List m_list ;
    m_Marked_Vertices m_marked_vertices ;
    m_List_iterator m_actual_list_end ;

public:
    typedef m_Surface Surface ;
    typedef m_List_const_iterator const_iterator ;
    typedef m_List_size_type size_type ;
    typedef m_Vertex_Indexes Boundary ;

    Rectangular_Boundaries() ;
    // compiler writes memberwise copy and assign

    const_iterator begin() const
    {
        return m_list.begin() ;
    }

    const_iterator end() const
    {
        return m_actual_list_end ;
    }

    size_type size() const
    {
        return m_list.size() ;
    }

    void compute( const Surface & surface ) ;

    ~Rectangular_Boundaries() ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Rectangular_Boundaries.template.cxx>

#endif

