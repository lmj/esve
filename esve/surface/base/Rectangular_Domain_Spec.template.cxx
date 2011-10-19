
#include <esve/surface/base/Rectangular_Domain_Spec.hxx>

namespace esve { namespace surface { namespace base {

template< typename Domain_Point,
          typename Facets_size_type >
Rectangular_Domain_Spec<Domain_Point,
                        Facets_size_type>::
Rectangular_Domain_Spec( const Domain_Point & corner0_,
                         const Domain_Point & corner1_,
                         Facets_size_type width_resolution_,
                         Facets_size_type height_resolution_,
                         Topology topology_ )
    : corner0(corner0_),
      corner1(corner1_),
      width_resolution(width_resolution_),
      height_resolution(height_resolution_),
      topology(topology_)
{
}

}}} // namespace esve::surface::base
