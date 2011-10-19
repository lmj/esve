//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_PD_Vertex_hxx
#define esve_base_dimn_vertex_PD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Point,
          typename T_Domain_Point >
struct PD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Point point ;
    Domain_Point domain_point ;

    PD_Vertex()
        : point(),
          domain_point() { }

    PD_Vertex( const Point & p,
               const Domain_Point & d )
        : point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
