
#ifndef esve_geom_dim4_specs_Regular_Spec_hxx
#define esve_geom_dim4_specs_Regular_Spec_hxx

#include <esve/geom/dim4/specs/Base_Spec.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

struct Regular_Spec
    : public Base_Spec
{
    typedef geom::dimn::selectors::category::regular category_selector ;
    typedef geom::dimn::selectors::topology::plane topology_selector ;
} ;

}}}} // namespace esve::geom::dim4::specs

#endif

