//
// Packed_Surface
//
// Simple OpenGL-style representation for polygons.  Packed vertices
// with packed vertex-index facets.
//
// Packed_Surface is like a Packed_Mesh with vertex normals, facet
// normals, and facets-around-vertex lists.
//
// See Packed_Surface_Spec for an example of the 'spec' template
// parameter.
//

#ifndef esve_surface_base_Packed_Surface_hxx
#define esve_surface_base_Packed_Surface_hxx

#include <vector>

namespace esve { namespace surface { namespace base {

/////////////////////////////////////////////////////
//
// Packed_Surface
//
/////////////////////////////////////////////////////

template< typename T_Spec >
class Packed_Surface
{
private:
    typedef T_Spec m_Spec ;
    typedef typename m_Spec::Vertex m_Vertex ;
    typedef typename m_Spec::Facet m_Facet ;
    typedef typename m_Spec::Facets_Around_Vertex m_Facets_Around_Vertex ;
    typedef typename m_Spec::Compute_Facet_Normal m_Compute_Facet_Normal ;
    typedef typename m_Spec::Manual_Normalize m_Manual_Normalize ;

    typedef typename m_Vertex::Normal m_Normal ;

    typedef typename
    m_Facet::Vertex_Indexes_const_iterator
    m_Facet_Vertex_Indexes_const_iterator ;

    typedef std::vector<m_Vertex> m_Vertices ;
    typedef std::vector<m_Facet> m_Facets ;
    typedef std::vector<m_Facets_Around_Vertex> m_Facets_Around_Vertices ;
    typedef std::vector<m_Normal> m_Facet_Normals ;

    m_Vertices m_vertices ;
    m_Facets m_facets ;
    m_Facets_Around_Vertices m_fav ;
    m_Facet_Normals m_facet_normals ;

public:
    //////////////////////////////
    // base types

    typedef m_Spec Spec ;
    typedef m_Vertex Vertex ;
    typedef m_Facet Facet ;
    typedef m_Facets_Around_Vertex Facets_Around_Vertex ;
    typedef m_Normal Normal ;

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
    // facet normals

    typedef typename m_Facet_Normals::iterator
                       Facet_Normals_iterator ;

    typedef typename m_Facet_Normals::const_iterator
                       Facet_Normals_const_iterator ;

    typedef typename m_Facet_Normals::size_type
                       Facet_Normals_size_type ;

    //////////////////////////////
    // facets around vertex

    typedef typename Facets_Around_Vertex::iterator
                     Facets_Around_Vertex_iterator ;

    typedef typename Facets_Around_Vertex::const_iterator
                     Facets_Around_Vertex_const_iterator ;

    typedef typename Facets_Around_Vertex::size_type
                     Facets_Around_Vertex_size_type ;

    //////////////////////////////
    // constructor

    Packed_Surface() ;

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

    //////////////////////////////
    // facet normals

    Facet_Normals_const_iterator facet_normals_begin() const
    {
        return m_facet_normals.begin() ;
    }

    Facet_Normals_iterator facet_normals_begin()
    {
        return m_facet_normals.begin() ;
    }

    Facet_Normals_const_iterator facet_normals_end() const
    {
        return m_facet_normals.end() ;
    }

    Facet_Normals_iterator facet_normals_end()
    {
        return m_facet_normals.end() ;
    }

    Facet_Normals_size_type facet_normals_size() const
    {
        return m_facet_normals.size() ;
    }

    //////////////////////////////
    // facets around vertex

    Facets_Around_Vertex_const_iterator
    facets_around_vertex_begin( Vertices_const_iterator v ) const
    {
        return m_fav[v - vertices_begin()].begin() ;
    }

    Facets_Around_Vertex_iterator
    facets_around_vertex_begin( Vertices_const_iterator v )
    {
        return m_fav[v - vertices_begin()].begin() ;
    }

    Facets_Around_Vertex_const_iterator
    facets_around_vertex_end( Vertices_const_iterator v ) const
    {
        return m_fav[v - vertices_begin()].end() ;
    }

    Facets_Around_Vertex_iterator
    facets_around_vertex_end( Vertices_const_iterator v )
    {
        return m_fav[v - vertices_begin()].end() ;
    }

    Facets_Around_Vertex_size_type
    facets_around_vertex_size( Vertices_const_iterator v ) const
    {
        return m_fav[v - vertices_begin()].size() ;
    }

    //////////////////////////////
    // add/remove vertices/facets

    Vertices_iterator add_vertex( const Vertex & ) ;
    void vertices_erase( Vertices_iterator first, Vertices_iterator last ) ;
    void vertices_reserve( Vertices_size_type n ) ;

    Facets_iterator add_facet( const Facet & ) ;
    Facets_iterator add_facet_with_fav_check( const Facet & ) ;
    void facets_erase( Facets_iterator first, Facets_iterator last ) ;
    void facets_reserve( Facets_size_type n ) ;

    //////////////////////////////
    // normals

    void compute_facet_normals() ;
    void compute_vertex_normals() ;
    void compute_normals() ;

    ~Packed_Surface() ;
} ;

template< typename T_Spec >
inline
typename Packed_Surface<T_Spec>::Vertices_iterator
Packed_Surface<T_Spec>::
add_vertex( const Vertex & a )
{
    m_vertices.push_back(a) ;
    m_fav.push_back(Facets_Around_Vertex()) ;
    return m_vertices.end() - 1 ;
}

}}} // namespace esve::surface::base

#include <esve/surface/base/Packed_Surface.template.cxx>

#endif

