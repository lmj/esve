
#include <esve/geom/dim3/specs/Disc_With_Two_Holes.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

Disc_With_Two_Holes::
Disc_With_Two_Holes( const Circle & disc,
                     const Circle & hole0,
                     const Circle & hole1 )
    : super(disc)
{
    super::hole<0>(hole0) ;
    super::hole<1>(hole1) ;
}

}}}} // namespace esve::geom::dim3::specs

