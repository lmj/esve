
#ifndef esve_geom_dimn_slicers_Disc_With_Holes_hxx
#define esve_geom_dimn_slicers_Disc_With_Holes_hxx

#include <esve/geom/dimn/Slicer_Union.hxx>

namespace esve { namespace geom { namespace dimn { namespace slicers {

template< typename T_complex,
          unsigned int num_holes >
struct Disc_With_Holes
{
    typedef
    Slicer_Union
    <
        typename Disc_With_Holes<T_complex, num_holes - 1>::type,
        Hole<T_complex>
    >
    type ;
} ;

template< typename T_complex >
struct Disc_With_Holes<T_complex, 0>
{
    typedef Disc<T_complex> type ;
} ;

}}}} // namespace esve::geom::dimn::slicers

#endif

