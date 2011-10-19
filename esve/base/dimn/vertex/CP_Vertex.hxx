//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CP_Vertex_hxx
#define esve_base_dimn_vertex_CP_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Point >
struct CP_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Color Color ;
    typedef T_Point Point ;

    Color color ;
    Point point ;

    CP_Vertex()
        : color(),
          point() { }

    CP_Vertex( const Color & c,
               const Point & p )
        : color(c),
          point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
