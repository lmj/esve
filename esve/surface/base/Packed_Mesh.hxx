//
// Packed_Mesh
//
// Simple OpenGL-style representation for polygons.  Packed vertices
// with packed vertex-index facets.
//

#ifndef esve_surface_base_Packed_Mesh_hxx
#define esve_surface_base_Packed_Mesh_hxx

#include <vector>

namespace esve { namespace surface { namespace base {

/////////////////////////////////////////////////////
//
// Packed_Mesh
//
/////////////////////////////////////////////////////

template< typename T_Vertex, typename T_Facet >
class Packed_Mesh
{
private:
    typedef std::vector<T_Vertex> m_Vertices ;
    typedef std::vector<T_Facet> m_Facets ;

    m_Vertices m_vertices ;
    m_Facets m_facets ;

public:
    //////////////////////////////
    // base types

    typedef T_Vertex Vertex ;
    typedef T_Facet Facet ;

    //////////////////////////////
    // vertices

    typedef typename m_Vertices::iterator Vertices_iterator ;
    typedef typename m_Vertices::const_iterator Vertices_const_iterator ;
    typedef typename m_Vertices::size_type Vertices_size_type ;

    //////////////////////////////
    // facets

    typedef typename m_Facets::iterator Facets_iterator ;
    typedef typename m_Facets::const_iterator Facets_const_iterator ;
    typedef typename m_Facets::size_type Facets_size_type ;

    //////////////////////////////
    // constructor

    Packed_Mesh() ;

    // compiler writes memberwise copy and assign

    //////////////////////////////
    // vertices

    const Vertex & vertices( Vertices_size_type i ) const
    {
        return m_vertices[i] ;
    }

    Vertex & vertices( Vertices_size_type i )
    {
        return m_vertices[i] ;
    }

    Vertices_const_iterator vertices_begin() const
    {
        return m_vertices.begin() ;
    }

    Vertices_iterator vertices_begin()
    {
        return m_vertices.begin() ;
    }

    Vertices_const_iterator vertices_end() const
    {
        return m_vertices.end() ;
    }

    Vertices_iterator vertices_end()
    {
        return m_vertices.end() ;
    }

    Vertices_size_type vertices_size() const
    {
        return m_vertices.size() ;
    }

    void vertices_reserve( Vertices_size_type n )
    {
        m_vertices.reserve(n) ;
    }

    //////////////////////////////
    // facets

    // no method for replacing an arbitrary facet short of erase()

    const Facet & facets( Facets_size_type i ) const
    {
        return m_facets[i] ;
    }

    Facets_const_iterator facets_begin() const
    {
        return m_facets.begin() ;
    }

    Facets_iterator facets_begin()
    {
        return m_facets.begin() ;
    }

    Facets_const_iterator facets_end() const
    {
        return m_facets.end() ;
    }

    Facets_iterator facets_end()
    {
        return m_facets.end() ;
    }

    Facets_size_type facets_size() const
    {
        return m_facets.size() ;
    }

    void facets_reserve( Facets_size_type n )
    {
        m_facets.reserve(n) ;
    }

    //////////////////////////////
    // add/remove vertices/facets

    Vertices_iterator add_vertex( const Vertex & a )
    {
        m_vertices.push_back(a) ; return m_vertices.end() - 1 ;
    }

    void vertices_erase( Vertices_iterator first, Vertices_iterator last )
    {
        m_vertices.erase(first, last) ;
    }

    Facets_iterator add_facet( const Facet & a )
    {
        m_facets.push_back(a) ; return m_facets.end() - 1 ;
    }

    void facets_erase( Facets_iterator first, Facets_iterator last )
    {
        m_facets.erase(first, last) ;
    }

    ~Packed_Mesh() ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Packed_Mesh.template.cxx>

#endif

