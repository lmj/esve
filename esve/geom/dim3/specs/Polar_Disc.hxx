
#ifndef esve_geom_dim3_specs_Polar_Disc_hxx
#define esve_geom_dim3_specs_Polar_Disc_hxx

#include <esve/geom/dim3/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Polar_Disc.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

class Polar_Disc
    : public Base_Spec,
      public dimn::specs::Polar_Disc<Base_Spec::complex>
{
private:
    typedef
    dimn::specs::Polar_Disc<Base_Spec::complex>
    super ;

    Polar_Disc( const Polar_Disc & ) ;
    Polar_Disc & operator=( const Polar_Disc & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    explicit Polar_Disc( const Circle & ) ;
} ;

}}}} // namespace esve::geom::dim3::specs

#endif

