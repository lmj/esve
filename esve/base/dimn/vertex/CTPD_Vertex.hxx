//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CTPD_Vertex_hxx
#define esve_base_dimn_vertex_CTPD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Transformed_Point,
          typename T_Point,
          typename T_Domain_Point >
struct CTPD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::true_tag  has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Color Color ;
    typedef T_Transformed_Point Transformed_Point ;
    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Color color ;
    Transformed_Point transformed_point ;
    Point point ;
    Domain_Point domain_point ;

    CTPD_Vertex()
        : color(),
          transformed_point(),
          point(),
          domain_point() { }

    CTPD_Vertex( const Color & c,
                 const Transformed_Point & t,
                 const Point & p,
                 const Domain_Point & d )
        : color(c),
          transformed_point(t),
          point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
