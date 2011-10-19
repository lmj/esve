
#include <esve/geom/dimn/specs/Disc_With_Holes.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex,
          unsigned int num_holes >
Disc_With_Holes<T_complex, num_holes>::
Disc_With_Holes( const Circle & disc )
    : m_Base(disc),
      m_hole(complex(0, 0), 0),
      m_hole_slicer(m_hole),
      m_slicer(m_Base::slicer(), m_hole_slicer)
{
}

}}}} // namespace esve::geom::dimn::specs

