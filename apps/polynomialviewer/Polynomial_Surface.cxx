
#include "Polynomial_Surface.hxx"

Polynomial_Surface::
Polynomial_Surface()
    : m_Data(),
      m_Base(m_Data::spec)
{
    m_Base::facet_clip_test(m_Base::ALL_REQUIRED) ;
}

Polynomial_Surface::
~Polynomial_Surface()
{
}

void
Polynomial_Surface::
realcurves_epsilon( real a )
{
    if( a != m_Data::spec.realcurves_epsilon )
    {
        m_Data::spec.realcurves_epsilon = a ;
        m_Base::update_surface_clip() ;
    }
}

void
Polynomial_Surface::
color_scale( real a )
{
    if( m_Data::spec.color_scale != a )
    {
        m_Data::spec.color_scale = a ;
        m_Base::update_color() ;
    }
}

void
Polynomial_Surface::
refz_scale( real a )
{
    if( m_Data::spec.refz_scale != a )
    {
        m_Data::spec.refz_scale = a ;
        m_Base::update_surface() ;
    }
}

