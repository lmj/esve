//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_NTP_Vertex_hxx
#define esve_base_dimn_vertex_NTP_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Normal,
          typename T_Transformed_Point,
          typename T_Point >
struct NTP_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::true_tag  has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Normal Normal ;
    typedef T_Transformed_Point Transformed_Point ;
    typedef T_Point Point ;

    Normal normal ;
    Transformed_Point transformed_point ;
    Point point ;

    NTP_Vertex()
        : normal(),
          transformed_point(),
          point() { }

    NTP_Vertex( const Normal & n,
                const Transformed_Point & t,
                const Point & p )
        : normal(n),
          transformed_point(t),
          point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
