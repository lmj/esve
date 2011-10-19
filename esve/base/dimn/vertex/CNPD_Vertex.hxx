//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_CNPD_Vertex_hxx
#define esve_base_dimn_vertex_CNPD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Color,
          typename T_Normal,
          typename T_Point,
          typename T_Domain_Point >
struct CNPD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::true_tag  has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Color Color ;
    typedef T_Normal Normal ;
    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Color color ;
    Normal normal ;
    Point point ;
    Domain_Point domain_point ;

    CNPD_Vertex()
        : color(),
          normal(),
          point(),
          domain_point() { }

    CNPD_Vertex( const Color & c,
                 const Normal & n,
                 const Point & p,
                 const Domain_Point & d )
        : color(c),
          normal(n),
          point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
