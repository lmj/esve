
#include <esve/surface/geom/Regular_Parametric_Surface.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec >
Regular_Parametric_Surface<T_Spec>::
Regular_Parametric_Surface( const Spec & spec )
    : m_Base(),
      m_spec(spec),
      m_need_compute_resolution(true),
      m_need_compute_domain(true),
      m_need_compute_surface(true),
      m_need_compute_color(true),
      m_domain_spec(m_Domain_Spec(m_Domain_Point(0, 0),
                                  m_Domain_Point(1, 1),
                                  0, 0))
{
}

template< typename T_Spec >
Regular_Parametric_Surface<T_Spec>::
~Regular_Parametric_Surface()
{
}

template< typename T_Spec >
typename
Regular_Parametric_Surface<T_Spec>::Topology
Regular_Parametric_Surface<T_Spec>::
topology() const
{
    return m_domain_spec.topology ;
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
topology( Topology a )
{
    m_domain_spec.topology = a ;
    m_need_compute_resolution = true ;
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
resolution( Facets_size_type wr, Facets_size_type hr )
{
    m_domain_spec.width_resolution = wr ;
    m_domain_spec.height_resolution = hr ;
    m_need_compute_resolution = true ;
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
m_compute_resolution_domain_surface_color()
{
    m_Base::compute(m_domain_spec) ;
    m_compute_domain_surface_color() ;
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
m_compute_domain_surface_color()
{
    for( Vertices_iterator r = m_Base::vertices_begin() ;
         r != m_Base::vertices_end() ;
         ++r )
    {
        (*r).transformed_domain_point =
            m_spec.domain((*r).domain_point) ;

        (*r).point =
            m_spec.surface((*r).domain_point,
                           (*r).transformed_domain_point) ;
        (*r).color =
            m_spec.color((*r).domain_point,
                         (*r).transformed_domain_point,
                         (*r).point) ;
    }
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
m_compute_surface_color()
{
    for( Vertices_iterator r = m_Base::vertices_begin() ;
         r != m_Base::vertices_end() ;
         ++r )
    {
        (*r).point =
            m_spec.surface((*r).domain_point,
                           (*r).transformed_domain_point) ;
        (*r).color =
            m_spec.color((*r).domain_point,
                         (*r).transformed_domain_point,
                         (*r).point) ;
    }
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
m_compute_color()
{
    for( Vertices_iterator r = m_Base::vertices_begin() ;
         r != m_Base::vertices_end() ;
         ++r )
    {
        (*r).color =
            m_spec.color((*r).domain_point,
                         (*r).transformed_domain_point,
                         (*r).point) ;
    }
}

template< typename T_Spec >
bool
Regular_Parametric_Surface<T_Spec>::
changed() const
{
    return
        m_need_compute_resolution ||
        m_need_compute_domain ||
        m_need_compute_surface ||
        m_need_compute_color ;
}

template< typename T_Spec >
void
Regular_Parametric_Surface<T_Spec>::
compute()
{
    if( m_need_compute_resolution )
    {
        m_compute_resolution_domain_surface_color() ;
    }
    else if( m_need_compute_domain )
    {
        m_compute_domain_surface_color() ;
    }
    else if( m_need_compute_surface )
    {
        m_compute_surface_color() ;
    }
    else if( m_need_compute_color )
    {
        m_compute_color() ;
    }

    m_need_compute_resolution = false ;
    m_need_compute_domain = false ;
    m_need_compute_surface = false ;
    m_need_compute_color = false ;
}

}}} // namespace esve::surface::geom
