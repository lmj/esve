
#include <esve/geom/dim4/specs/Disc_With_Three_Holes.hxx>

namespace esve { namespace geom { namespace dim4 { namespace specs {

Disc_With_Three_Holes::
Disc_With_Three_Holes( const Circle & disc,
                       const Circle & hole0,
                       const Circle & hole1,
                       const Circle & hole2 )
    : super(disc)
{
    super::hole<0>(hole0) ;
    super::hole<1>(hole1) ;
    super::hole<2>(hole2) ;
}

}}}} // namespace esve::geom::dim4::specs

