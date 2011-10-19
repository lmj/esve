
#ifndef esve_geom_dim4_specs_Unit_Square_hxx
#define esve_geom_dim4_specs_Unit_Square_hxx

#include <esve/geom/dim4/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Unit_Square.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

class Unit_Square
    : public Base_Spec,
      public dimn::specs::Unit_Square<Base_Spec::complex>
{
private:
    typedef
    dimn::specs::Unit_Square<Base_Spec::complex>
    super ;

    Unit_Square( const Unit_Square & ) ;
    Unit_Square & operator=( const Unit_Square & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    Unit_Square() ;
} ;

}}}} // namespace esve::geom::dim4::specs

#endif

