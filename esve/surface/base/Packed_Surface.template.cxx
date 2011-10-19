
#include <esve/surface/base/Packed_Surface.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Spec >
Packed_Surface<T_Spec>::
Packed_Surface()
    : m_vertices(),
      m_facets(),
      m_fav(),
      m_facet_normals()
{
}

template< typename T_Spec >
Packed_Surface<T_Spec>::
~Packed_Surface()
{
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
vertices_reserve( Vertices_size_type n )
{
    m_vertices.reserve(n) ;
    m_fav.reserve(Facets_Around_Vertices_size_type(n)) ;
}

template< typename T_Spec >
typename Packed_Surface<T_Spec>::Facets_iterator
Packed_Surface<T_Spec>::
add_facet( const Facet & facet )
{
    m_facets.push_back(facet) ;
    m_facet_normals.push_back(Normal()) ;

    for( m_Facet_Vertex_Indexes_const_iterator vii =
             facet.vertex_indexes_begin() ;
         vii != facet.vertex_indexes_end() ;
         ++vii )
    {
        m_fav[*vii].push_back(m_facets.size() - 1) ;
    }

    return m_facets.end() - 1 ;
}

template< typename T_Spec >
typename Packed_Surface<T_Spec>::Facets_iterator
Packed_Surface<T_Spec>::
add_facet_with_fav_check( const Facet & facet )
{
    m_facets.push_back(facet) ;
    m_facet_normals.push_back(Normal()) ;

    for( m_Facet_Vertex_Indexes_const_iterator vii =
             facet.vertex_indexes_begin() ;
         vii != facet.vertex_indexes_end() ;
         ++vii )
    {
        if( m_fav[*vii].size() == m_fav[*vii].max_size() )
        {
            break ;
        }

        m_fav[*vii].push_back(m_facets.size() - 1) ;
    }

    return m_facets.end() - 1 ;
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
facets_reserve( Facets_size_type n )
{
    m_facets.reserve(n) ;
    m_facet_normals.reserve(Facet_Normals_size_type(n)) ;
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
vertices_erase( Vertices_iterator first, Vertices_iterator last )
{
    m_fav.erase(
        m_fav.begin() + (first - m_vertices.begin()),
        m_fav.begin() + (last - m_vertices.begin())) ;

    m_vertices.erase(first, last) ;
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
facets_erase( Facets_iterator first, Facets_iterator last )
{
    m_facet_normals.erase(
        m_facet_normals.begin() + (first - m_facets.begin()),
        m_facet_normals.begin() + (last - m_facets.begin())) ;

    m_facets.erase(first, last) ;
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
compute_facet_normals()
{
    m_Compute_Facet_Normal compute_facet_normal ;

    for( Facets_iterator fi = facets_begin() ;
         fi != facets_end() ;
         ++fi )
    {
        m_facet_normals[fi - m_facets.begin()] =
            compute_facet_normal(
                m_vertices[(*fi).vertex_indexes_0()],
                m_vertices[(*fi).vertex_indexes_1()],
                m_vertices[(*fi).vertex_indexes_back()]) ;
    }
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
compute_vertex_normals()
{
    m_Manual_Normalize manual_normalize ;

    for( Vertices_iterator vi = vertices_begin() ;
         vi != vertices_end() ;
         ++vi )
    {
        (*vi).normal = Normal() ;

        for( Facets_Around_Vertex_iterator favi =
                 facets_around_vertex_begin(vi) ;
             favi != facets_around_vertex_end(vi) ;
             ++favi )
        {
            (*vi).normal += m_facet_normals[*favi] ;
        }

        manual_normalize((*vi).normal) ;
    }
}

template< typename T_Spec >
void
Packed_Surface<T_Spec>::
compute_normals()
{
    compute_facet_normals() ;
    compute_vertex_normals() ;
}

}}} // namespace esve::surface::base
