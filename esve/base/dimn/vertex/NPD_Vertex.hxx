//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_NPD_Vertex_hxx
#define esve_base_dimn_vertex_NPD_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Normal,
          typename T_Point,
          typename T_Domain_Point >
struct NPD_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::true_tag  has_domain_point ;

    typedef T_Normal Normal ;
    typedef T_Point Point ;
    typedef T_Domain_Point Domain_Point ;

    Normal normal ;
    Point point ;
    Domain_Point domain_point ;

    NPD_Vertex()
        : normal(),
          point(),
          domain_point() { }

    NPD_Vertex( const Normal & n,
                const Point & p,
                const Domain_Point & d )
        : normal(n),
          point(p),
          domain_point(d) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
