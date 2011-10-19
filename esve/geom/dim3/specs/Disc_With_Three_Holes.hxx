
#ifndef esve_geom_dim3_specs_Disc_With_Three_Holes_hxx
#define esve_geom_dim3_specs_Disc_With_Three_Holes_hxx

#include <esve/geom/dim3/specs/Base_Spec.hxx>
#include <esve/geom/dimn/specs/Disc_With_Holes.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

class Disc_With_Three_Holes
    : public Base_Spec,
      public dimn::specs::Disc_With_Holes<Base_Spec::complex, 3>
{
private:
    typedef
    dimn::specs::Disc_With_Holes<Base_Spec::complex, 3>
    super ;

    Disc_With_Three_Holes( const Disc_With_Three_Holes & ) ;
    Disc_With_Three_Holes & operator=( const Disc_With_Three_Holes & ) ;

public:
    typedef Parametric_Surface_Spec::real real ;
    typedef Parametric_Surface_Spec::complex complex ;

    Disc_With_Three_Holes( const Circle & disc,
                           const Circle & hole0,
                           const Circle & hole1,
                           const Circle & hole2 ) ;

    const Circle & hole0() const
    {
        return super::hole<0>() ;
    }

    void hole0( const Circle & circle )
    {
        super::hole<0>(circle) ;
    }

    const Circle & hole1() const
    {
        return super::hole<1>() ;
    }

    void hole1( const Circle & circle )
    {
        super::hole<1>(circle) ;
    }

    const Circle & hole2() const
    {
        return super::hole<2>() ;
    }

    void hole2( const Circle & circle )
    {
        super::hole<2>(circle) ;
    }

    bool surface_clip( const complex & unit_square,
                       const complex & domain,
                       const pure & surface ) const
    {
        return false ;
    }
} ;

}}}} // namespace esve::geom::dim3::specs

#endif

