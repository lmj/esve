
#ifndef esve_viewers_dim3_Surface_Viewer_Spec_hxx
#define esve_viewers_dim3_Surface_Viewer_Spec_hxx

#include <esve/viewers/dim3/Simple_Viewer.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/geom/dim3/Parametric_Surface.hxx>

namespace esve { namespace viewers { namespace dim3 {

template< typename T_Surface_Spec >
struct Surface_Viewer_Spec
{
    typedef
    T_Surface_Spec
    Surface_Spec ;

    typedef typename
    Surface_Spec::category_selector
    category_selector ;

    typedef
    engine::dim3::Make_Geom
    <
        geom::dim3::Parametric_Surface
        <
            Surface_Spec
        >
    >
    Surface ;

    typedef
    Simple_Viewer
    Viewer ;
} ;

}}} // namespace esve::viewers::dim3

#endif

