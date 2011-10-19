
#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/components/dim3/Rotation_Handler.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/geom/dim3/Icosahedron.hxx>
#include <esve/types/pure.hxx>

using esve::viewers::dim3::Basic_Viewer ;
using esve::components::dim3::Rotation_Handler ;
using esve::engine::dim3::impl::Frame ;
using esve::engine::dim3::Make_Geom ;
using esve::geom::dim3::Icosahedron ;
using esve::types::pure ;

int main()
{
    Frame rotation_frame ;
    Make_Geom<Icosahedron> icos1 ;
    Make_Geom<Icosahedron> icos2 ;

    Rotation_Handler rotation_handler(rotation_frame.peek_transform()) ;

    Basic_Viewer viewer ;

    viewer.add_frame(rotation_frame) ;
    viewer.add_geom(icos1) ;
    viewer.add_geom(icos2) ;

    viewer.add_handler(rotation_handler) ;

    viewer.create_camera() ;
    viewer.create_light() ;

    // make the icosahedra children of the rotation frame

    rotation_frame.add(icos1) ;
    rotation_frame.add(icos2) ;
    icos1.peek_transform().translate(pure(1, 0, 0)) ;
    icos2.peek_transform().translate(pure(-1, 0, 0)) ;

    return viewer.takeover() ;
}
