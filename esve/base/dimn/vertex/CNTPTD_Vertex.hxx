//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CNTPTD_Vertex_hxx
#define esve_base_dimn_vertex_CNTPTD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Normal,
          typename T_Transformed_Point,
          typename T_Point,
          typename T_Transformed_Domain_Point,
          typename T_Domain_Point >
struct CNTPTD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::true_tag  has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_transformed_domain_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Color Color ;
    typedef T_Normal Normal ;
    typedef T_Transformed_Point Transformed_Point ;
    typedef T_Point Point ;
    typedef T_Transformed_Domain_Point Transformed_Domain_Point ;
    typedef T_Domain_Point Domain_Point ;

    Color color ;
    Normal normal ;
    Transformed_Point transformed_point ;
    Point point ;
    Transformed_Domain_Point transformed_domain_point ;
    Domain_Point domain_point ;

    CNTPTD_Vertex()
        : color(),
          normal(),
          transformed_point(),
          point(),
          transformed_domain_point(),
          domain_point() { }

    CNTPTD_Vertex( const Color & c,
                   const Normal & n,
                   const Transformed_Point & t,
                   const Point & p,
                   const Transformed_Domain_Point & w,
                   const Domain_Point & d )
        : color(c),
          normal(n),
          transformed_point(t),
          point(p),
          transformed_domain_point(w),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
