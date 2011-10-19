
#ifndef esve_geom_dim4_specs_Disc_With_One_Hole_hxx
#define esve_geom_dim4_specs_Disc_With_One_Hole_hxx

#include <esve/geom/dim4/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Disc_With_Holes.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

class Disc_With_One_Hole
    : public Base_Spec,
      public dimn::specs::Disc_With_Holes<Base_Spec::complex, 1>
{
private:
    typedef
    dimn::specs::Disc_With_Holes<Base_Spec::complex, 1>
    super ;

    Disc_With_One_Hole( const Disc_With_One_Hole & ) ;
    Disc_With_One_Hole & operator=( const Disc_With_One_Hole & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    Disc_With_One_Hole( const Circle & disc,
                        const Circle & hole ) ;

    const Circle & hole0() const
    {
        return super::hole<0>() ;
    }

    void hole0( const Circle & circle )
    {
        super::hole<0>(circle) ;
    }

    bool surface_clip( const complex & unit_square,
                       const complex & domain,
                       const quat & surface ) const
    {
        return false ;
    }
} ;

}}}} // namespace esve::geom::dim4::specs

#endif

