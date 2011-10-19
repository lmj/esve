//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CNP_Vertex_hxx
#define esve_base_dimn_vertex_CNP_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Normal,
          typename T_Point >
struct CNP_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Color Color ;
    typedef T_Normal Normal ;
    typedef T_Point Point ;

    Color color ;
    Normal normal ;
    Point point ;

    CNP_Vertex()
        : color(),
          normal(),
          point() { }

    CNP_Vertex( const Color & c,
                const Normal & n,
                const Point & p )
        : color(c),
          normal(n),
          point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
