//
// OpenGL vertex-array compatible layout.
//

#ifndef esve_base_dimn_vertex_P_Vertex_hxx
#define esve_base_dimn_vertex_P_Vertex_hxx

#include <esve/base/dimn/vertex/tags.hxx>

namespace esve { namespace base { namespace dimn { namespace vertex {

template< typename T_Point >
struct P_Vertex
{
    typedef tags::false_tag has_texture ;
    typedef tags::false_tag has_color ;
    typedef tags::false_tag has_normal ;
    typedef tags::false_tag has_transformed_point ;
    typedef tags::true_tag  has_point ;
    typedef tags::false_tag has_domain_point ;

    typedef T_Point Point ;

    Point point ;

    P_Vertex()
        : point() { }

    P_Vertex( const Point & p )
        : point(p) { }

    // compiler writes memberwise copy and assign
} ;

}}}} // namespace esve::base::dimn::vertex

#endif
