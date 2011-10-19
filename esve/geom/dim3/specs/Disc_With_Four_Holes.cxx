
#include <esve/geom/dim3/specs/Disc_With_Four_Holes.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

Disc_With_Four_Holes::
Disc_With_Four_Holes( const Circle & disc,
                      const Circle & hole0,
                      const Circle & hole1,
                      const Circle & hole2,
                      const Circle & hole3 )
    : super(disc)
{
    super::hole<0>(hole0) ;
    super::hole<1>(hole1) ;
    super::hole<2>(hole2) ;
    super::hole<3>(hole3) ;
}

}}}} // namespace esve::geom::dim3::specs

