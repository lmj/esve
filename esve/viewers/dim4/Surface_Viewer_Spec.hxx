
#ifndef esve_viewers_dim4_Surface_Viewer_Spec_hxx
#define esve_viewers_dim4_Surface_Viewer_Spec_hxx

#include <esve/viewers/dim4/Simple_Viewer.hxx>
#include <esve/engine/dim4/Make_Geom.hxx>
#include <esve/geom/dim4/Parametric_Surface.hxx>

namespace esve { namespace viewers { namespace dim4 {

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
    engine::dim4::Make_Geom
    <
        geom::dim4::Parametric_Surface
        <
            Surface_Spec
        >
    >
    Surface ;

    typedef
    Simple_Viewer
    Viewer ;
} ;

}}} // namespace esve::viewers::dim4

#endif

