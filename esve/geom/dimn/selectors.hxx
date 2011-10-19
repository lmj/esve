
#ifndef esve_geom_dimn_selectors_hxx
#define esve_geom_dimn_selectors_hxx

namespace esve { namespace geom { namespace dimn {

namespace selectors {

////////////////////////////////////////////////////////
// category
////////////////////////////////////////////////////////

namespace category {

// a straightforward map of the unit square
struct regular { } ;

// a surface with clipped quads
struct clipped { } ;

// a surface with clipped quads along with nice boundaries
struct sliced { } ;

} // namespace category

////////////////////////////////////////////////////////
// topology
////////////////////////////////////////////////////////

namespace topology {

struct plane { } ;
struct cylinder_wrap_width { } ;
struct cylinder_wrap_height { } ;
struct torus { } ;
struct moebius_band_wrap_width { } ;
struct moebius_band_wrap_height { } ;
struct klein_bottle_wrap_width { } ;
struct klein_bottle_wrap_height { } ;
struct projective_plane { } ;

} // namespace topology

////////////////////////////////////////////////////////
// postcompute
////////////////////////////////////////////////////////

namespace postcompute {

struct yes { } ;
struct no { } ;

} // namespace postcompute

} // namespace selectors

}}} // namespace esve::geom::dimn

#endif
