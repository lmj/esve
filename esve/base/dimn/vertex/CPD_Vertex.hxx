//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CPD_Vertex_hxx
#define esve_base_dimn_vertex_CPD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Point,
          typename T_Domain_Point >
struct CPD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Color Color ;
    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Color color ;
    Point point ;
    Domain_Point domain_point ;

    CPD_Vertex()
        : color(),
          point(),
          domain_point() { }

    CPD_Vertex( const Color & c,
                const Point & p,
                const Domain_Point & d )
        : color(c),
          point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
