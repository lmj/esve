
#include <esve/geom/dimn/specs/Disc.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
Disc<T_complex>::
Disc( const Circle & disc )
    : m_disc(disc),
      m_slicer(m_disc)
{
}

}}}} // namespace esve::geom::dimn::specs


