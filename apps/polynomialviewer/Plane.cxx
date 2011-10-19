
#include "Plane.hxx"

Plane::
Plane()
    : m_Data(),
      m_Base(m_Data::spec)
{
    m_Base::resolution(5, 5) ;
}

Plane::
~Plane()
{
}

void
Plane::
size( real a )
{
    if( a != m_Data::spec.size )
    {
        m_Data::spec.size = a ;
        m_Base::update_surface() ;
    }
}

void
Plane::
fade( real a )
{
    if( a != m_Data::spec.fade )
    {
        m_Data::spec.fade = a ;
        m_Base::update_color() ;
    }
}
