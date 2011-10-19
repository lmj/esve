
#include <esve/surface/geom/Sliced_Parametric_Surface.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec, typename T_FAV >
Sliced_Parametric_Surface<T_Spec, T_FAV>::
Sliced_Parametric_Surface( const T_Spec & spec )
    : m_Base(spec),
      m_spec(spec),
      m_boundaries()
{
}

template< typename T_Spec, typename T_FAV >
Sliced_Parametric_Surface<T_Spec, T_FAV>::
~Sliced_Parametric_Surface()
{
}

template< typename T_Spec, typename T_FAV >
void
Sliced_Parametric_Surface<T_Spec, T_FAV>::
compute_surface_clip()
{
    m_Base::compute_surface_clip() ;

    m_boundaries.compute(*this) ;

    // remember original size

    m_Vertices_size_type orig_vertices_size =
        m_Base::vertices_size() ;

    // add vertices

    for( m_Boundaries_const_iterator i = m_boundaries.begin() ;
         i != m_boundaries.end() ;
         ++i )
    {
        for( m_Boundary_const_iterator j = (*i).begin() ;
             j != (*i).end() ;
             ++j )
        {
            m_Vertices_iterator v =
                m_Base::add_vertex(m_Base::vertices(*j)) ;

             (*v).transformed_domain_point =
                m_spec.domain_snap(
                    (*v).domain_point,
                    (*v).transformed_domain_point) ;

             (*v).point =
                m_spec.surface(
                    (*v).domain_point,
                    (*v).transformed_domain_point) ;
        }
    }

    // add facets

    m_Vertices_size_type count = 0 ;

    for( m_Boundaries_const_iterator i = m_boundaries.begin() ;
         i != m_boundaries.end() ;
         ++i )
    {
        assert((*i).size() >= 4) ;

        m_Boundary_const_iterator next_to_end = (*i).end() - 1 ;

        for( m_Boundary_const_iterator j = (*i).begin() ;
             j != next_to_end ;
             ++j )
        {
            m_Base::add_facet_with_fav_check(m_Facet(
                orig_vertices_size + count,
                orig_vertices_size + count + 1,
                *(j + 1),
                *j)) ;

            ++count ;
        }

        m_Base::add_facet_with_fav_check(m_Facet(
            orig_vertices_size + count,
            orig_vertices_size + count - (*i).size() + 1,
            (*i).front(),
            (*i).back())) ;

        ++count ;
    }
}

}}} // namespace esve::surface::geom

