
#ifndef esve_geom_dim3_specs_Polar_Annulus_hxx
#define esve_geom_dim3_specs_Polar_Annulus_hxx

#include <esve/geom/dim3/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Polar_Annulus.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

class Polar_Annulus
    : public Base_Spec,
      public dimn::specs::Polar_Annulus<Base_Spec::complex>
{
private:
    typedef
    dimn::specs::Polar_Annulus<Base_Spec::complex>
    super ;

    Polar_Annulus( const Polar_Annulus & ) ;
    Polar_Annulus & operator=( const Polar_Annulus & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    Polar_Annulus( real inner_radius,
                   real outer_radius ) ;
} ;

}}}} // namespace esve::geom::dim3::specs

#endif

