//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_NTPD_Vertex_hxx
#define esve_base_dimn_vertex_NTPD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Normal,
          typename T_Transformed_Point,
          typename T_Point,
          typename T_Domain_Point >
struct NTPD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::true_tag  has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Normal Normal ;
    typedef T_Transformed_Point Transformed_Point ;
    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Normal normal ;
    Transformed_Point transformed_point ;
    Point point ;
    Domain_Point domain_point ;

    NTPD_Vertex()
        : normal(),
          transformed_point(),
          point(),
          domain_point() { }

    NTPD_Vertex( const Normal & n,
                 const Transformed_Point & t,
                 const Point & p,
                 const Domain_Point & d )
        : normal(n),
          transformed_point(t),
          point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
