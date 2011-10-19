
#ifndef esve_surface_base_Topology_hxx
#define esve_surface_base_Topology_hxx

namespace esve { namespace surface { namespace base {

namespace topology {

enum Topology
{
    PLANE,
    CYLINDER_WRAP_WIDTH,
    CYLINDER_WRAP_HEIGHT,
    TORUS,
    MOEBIUS_BAND_WRAP_WIDTH,
    MOEBIUS_BAND_WRAP_HEIGHT,
    KLEIN_BOTTLE_WRAP_WIDTH,
    KLEIN_BOTTLE_WRAP_HEIGHT,
    PROJECTIVE_PLANE
} ;

} // namespace topology

using topology::Topology ;

}}} // namespace esve::surface::base

#endif
