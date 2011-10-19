//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_TP_Vertex_hxx
#define esve_base_dimn_vertex_TP_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Transformed_Point,
          typename T_Point >
struct TP_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::true_tag  has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Transformed_Point Transformed_Point ;
    typedef T_Point Point ;

    Transformed_Point transformed_point ;
    Point point ;

    TP_Vertex()
        : transformed_point(),
          point() { }

    TP_Vertex( const Transformed_Point & t,
               const Point & p )
        : transformed_point(t),
          point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
