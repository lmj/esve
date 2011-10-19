
#ifndef esve_geom_dim4_Parametric_Surface_Spec_hxx
#define esve_geom_dim4_Parametric_Surface_Spec_hxx

#include <esve/base/dimn/vertex/CNTPTD_Vertex.hxx>
#include <esve/types/rgba.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace geom { namespace dim4 {

struct Parametric_Surface_Spec
{
    typedef types::real real ;
    typedef types::complex complex ;
    typedef types::pure pure ;
    typedef types::quat quat ;
    typedef types::rgba rgba ;

    typedef GLuint Vertex_Index ;

    typedef rgba Color ;
    typedef pure Normal ;
    typedef quat Transformed_Point ;
    typedef quat Point ;
    typedef complex Transformed_Domain_Point ;
    typedef complex Domain_Point ;

    typedef
    base::dimn::vertex::CNTPTD_Vertex
    <
        Color,
        Normal,
        Transformed_Point,
        Point,
        Transformed_Domain_Point,
        Domain_Point
    >
    Vertex ;

protected:
    // prevent polymorphic use
    ~Parametric_Surface_Spec() { }
} ;

}}} // namespace esve::geom::dim4

#endif

