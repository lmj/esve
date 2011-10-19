
#ifndef esve_geom_dim4_specs_Centered_Square_hxx
#define esve_geom_dim4_specs_Centered_Square_hxx

#include <esve/geom/dim4/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Centered_Square.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

class Centered_Square
    : public Base_Spec,
      public dimn::specs::Centered_Square<Base_Spec::complex>
{
private:
    typedef
    dimn::specs::Centered_Square<Base_Spec::complex>
    super ;

    Centered_Square( const Centered_Square & ) ;
    Centered_Square & operator=( const Centered_Square & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    explicit Centered_Square( real radius ) ;
} ;

}}}} // namespace esve::geom::dim4::specs

#endif

