
#ifndef esve_geom_dim4_specs_Base_Spec_hxx
#define esve_geom_dim4_specs_Base_Spec_hxx

#include <esve/geom/dim4/Parametric_Surface_Spec.hxx>
#include <esve/geom/dimn/selectors.hxx>
#include <esve/types/Constants.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

struct Base_Spec
    : public dim4::Parametric_Surface_Spec,
      public types::Constants
{
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;
    typedef dimn::selectors::postcompute::no postcompute_selector ;
} ;

}}}} // namespace esve::geom::dim4::specs

#endif

