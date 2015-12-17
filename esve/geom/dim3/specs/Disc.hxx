
#ifndef esve_geom_dim3_specs_Disc_hxx
#define esve_geom_dim3_specs_Disc_hxx

#include <esve/geom/dim3/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Disc.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

class Disc
    : public Base_Spec,
      public dimn::specs::Disc<Base_Spec::complex>
{
private:
    typedef
    dimn::specs::Disc<Base_Spec::complex>
    super ;

    Disc( const Disc & ) ;
    Disc & operator=( const Disc & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    explicit Disc( const Circle & disc ) ;

    bool surface_clip( const complex & ,
                       const complex & ,
                       const pure & ) const
    {
        return false ;
    }
} ;

}}}} // namespace esve::geom::dim3::specs

#endif

