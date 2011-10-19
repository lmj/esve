//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CNPTD_Vertex_hxx
#define esve_base_dimn_vertex_CNPTD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Normal,
          typename T_Point,
          typename T_Transformed_Domain_Point,
          typename T_Domain_Point >
struct CNPTD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_transformed_domain_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Color Color ;
    typedef T_Normal Normal ;
    typedef T_Point Point ;
    typedef T_Transformed_Domain_Point Transformed_Domain_Point ;
    typedef T_Domain_Point Domain_Point ;

    Color color ;
    Normal normal ;
    Point point ;
    Transformed_Domain_Point transformed_domain_point ;
    Domain_Point domain_point ;

    CNPTD_Vertex()
        : color(),
          normal(),
          point(),
          transformed_domain_point(),
          domain_point() { }

    CNPTD_Vertex( const Color & c,
                  const Normal & n,
                  const Point & p,
                  const Transformed_Domain_Point & w,
                  const Domain_Point & d )
        : color(c),
          normal(n),
          point(p),
          transformed_domain_point(w),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
