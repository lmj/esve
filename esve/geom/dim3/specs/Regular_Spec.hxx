
#ifndef esve_geom_dim3_specs_Regular_Spec_hxx
#define esve_geom_dim3_specs_Regular_Spec_hxx

#include <esve/geom/dim3/specs/Base_Spec.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

struct Regular_Spec
    : public Base_Spec
{
    typedef geom::dimn::selectors::category::regular category_selector ;
    typedef geom::dimn::selectors::topology::plane topology_selector ;
} ;

}}}} // namespace esve::geom::dim3::specs

#endif

