
#include <esve/geom/dim3/specs/Disc_With_One_Hole.hxx>

namespace esve { namespace geom { namespace dim3 { namespace specs {

Disc_With_One_Hole::
Disc_With_One_Hole( const Circle & disc,
                    const Circle & hole0 )
    : super(disc)
{
    super::hole<0>(hole0) ;
}

}}}} // namespace esve::geom::dim3::specs

