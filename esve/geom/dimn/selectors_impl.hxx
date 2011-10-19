
#ifndef esve_geom_dimn_selectors_impl_hxx
#define esve_geom_dimn_selectors_impl_hxx

#include <esve/geom/dimn/selectors.hxx>
#include <esve/surface/geom/Regular_Parametric_Surface.hxx>
#include <esve/surface/geom/Clipped_Parametric_Surface.hxx>
#include <esve/surface/geom/Sliced_Parametric_Surface.hxx>
#include <esve/surface/base/Topology.hxx>

namespace esve { namespace geom { namespace dimn {

namespace selectors_impl {

////////////////////////////////////////////////////////
// select_category
////////////////////////////////////////////////////////

template< typename T_Surface_Spec,
          typename T_selector >
struct select_category ;

template< typename T_Surface_Spec >
struct select_category<T_Surface_Spec, selectors::category::regular>
{
    typedef
    surface::geom::Regular_Parametric_Surface<T_Surface_Spec>
    type ;
} ;

template< typename T_Surface_Spec >
struct select_category<T_Surface_Spec, selectors::category::clipped>
{
    typedef
    surface::geom::Clipped_Parametric_Surface<T_Surface_Spec>
    type ;
} ;

template< typename T_Surface_Spec >
struct select_category<T_Surface_Spec, selectors::category::sliced>
{
    typedef
    surface::geom::Sliced_Parametric_Surface<T_Surface_Spec>
    type ;
} ;

////////////////////////////////////////////////////////
// select_topology
////////////////////////////////////////////////////////

template< typename T_topology_selector >
struct select_topology ;

template<>
struct select_topology<selectors::topology::plane>
{
    static const surface::base::Topology value =
    surface::base::topology::PLANE ;
} ;

template<>
struct select_topology<selectors::topology::cylinder_wrap_width>
{
    static const surface::base::Topology value =
    surface::base::topology::CYLINDER_WRAP_WIDTH ;
} ;

template<>
struct select_topology<selectors::topology::cylinder_wrap_height>
{
    static const surface::base::Topology value =
    surface::base::topology::CYLINDER_WRAP_HEIGHT ;
} ;

template<>
struct select_topology<selectors::topology::torus>
{
    static const surface::base::Topology value =
    surface::base::topology::TORUS ;
} ;

template<>
struct select_topology<selectors::topology::moebius_band_wrap_width>
{
    static const surface::base::Topology value =
    surface::base::topology::MOEBIUS_BAND_WRAP_WIDTH ;
} ;

template<>
struct select_topology<selectors::topology::moebius_band_wrap_height>
{
    static const surface::base::Topology value =
    surface::base::topology::MOEBIUS_BAND_WRAP_HEIGHT ;
} ;

template<>
struct select_topology<selectors::topology::klein_bottle_wrap_width>
{
    static const surface::base::Topology value =
    surface::base::topology::KLEIN_BOTTLE_WRAP_WIDTH ;
} ;

template<>
struct select_topology<selectors::topology::klein_bottle_wrap_height>
{
    static const surface::base::Topology value =
    surface::base::topology::KLEIN_BOTTLE_WRAP_HEIGHT ;
} ;

template<>
struct select_topology<selectors::topology::projective_plane>
{
    static const surface::base::Topology value =
    surface::base::topology::PROJECTIVE_PLANE ;
} ;

} // namespace selectors_impl

}}} // namespace esve::geom::dimn

#endif
