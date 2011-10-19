
#include <esve/surface/base/Rectangular_Surface.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Spec >
Rectangular_Surface<T_Spec>::
Rectangular_Surface()
    : m_Base(),
      m_domain(*this)
{
}

template< typename T_Spec >
Rectangular_Surface<T_Spec>::
~Rectangular_Surface()
{
}

}}} // namespace esve::surface::base
