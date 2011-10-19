//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_NP_Vertex_hxx
#define esve_base_dimn_vertex_NP_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Normal,
          typename T_Point >
struct NP_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::true_tag  has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Normal Normal ;
    typedef T_Point Point ;

    Normal normal ;
    Point point ;

    NP_Vertex()
        : normal(),
          point() { }

    NP_Vertex( const Normal & n,
               const Point & p )
        : normal(n),
          point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
