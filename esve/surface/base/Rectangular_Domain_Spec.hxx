//
// Rectangular Domain: plane, torus, projective plane, etc
//
// Operates on the given mesh data.
//
// The type Vertex::Domain_Point and corresponding member
// vertex.domain_point are used (see vertex_types.hxx).
//

#ifndef esve_surface_base_Rectangular_Domain_Spec_hxx
#define esve_surface_base_Rectangular_Domain_Spec_hxx

#include <esve/surface/base/Topology.hxx>

namespace esve { namespace surface { namespace base {

template< typename Domain_Point,
          typename Facets_size_type >
struct Rectangular_Domain_Spec
{
    Domain_Point corner0 ;
    Domain_Point corner1 ;
    Facets_size_type width_resolution ;
    Facets_size_type height_resolution ;
    Topology topology ;

    Rectangular_Domain_Spec( const Domain_Point & corner0_,
                             const Domain_Point & corner1_,
                             Facets_size_type width_resolution_,
                             Facets_size_type height_resolution_,
                             Topology topology_ = topology::PLANE ) ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Rectangular_Domain_Spec.template.cxx>

#endif

