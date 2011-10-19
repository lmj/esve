//
// Two cameras --- one is stationary looking at the object; the other
// camera has a red light attached to itself and is orbiting the
// object.
//

#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/engine/dim3/Light.hxx>
#include <esve/components/dim3/Motion_Frame.hxx>
#include <esve/components/dim3/Rotation_Handler.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/engine/dimn/Materials.hxx>
#include <esve/geom/dim3/Icosahedron.hxx>
#include <esve/types/rgba.hxx>
#include <esve/types/pure.hxx>

using esve::viewers::dim3::Basic_Viewer ;
using esve::engine::dim3::Camera ;
using esve::engine::dim3::Light ;
using esve::components::dim3::Motion_Frame ;
using esve::components::dim3::Rotation_Handler ;
using esve::engine::dim3::Make_Geom ;
using esve::geom::dim3::Icosahedron ;
using esve::types::rgba ;
using esve::types::pure ;

int main()
{
    Motion_Frame motion_frame ;
    motion_frame.rotate_velocity(0.2, pure(0, 1, 0)) ;

    Make_Geom<Icosahedron> icos ;

    Rotation_Handler rotation_handler(icos.peek_transform()) ;

    Basic_Viewer viewer ;

    Camera & camera = viewer.create_camera() ;
    Light & light = viewer.create_light() ;

    viewer.create_camera() ;
    viewer.create_light() ;

    viewer.add_frame(motion_frame) ;
    viewer.add_geom(icos) ;
    viewer.add_handler(rotation_handler) ;
    viewer.add_handler(motion_frame) ;

    // attach first camera to the motion frame
    motion_frame.add(camera.peek_frame()) ;

    // light rides piggy-back on the moving camera
    camera.peek_frame().add(light.peek_frame()) ;
    light.peek_frame().peek_transform().identity() ;

    light.peek_materials().specular(rgba(1, 0, 0, 1)) ;
    light.peek_materials().diffuse(rgba(1, 0, 0, 1)) ;

    // just use messages from the first camera
    camera.remove_all_handlers() ;

    return viewer.takeover() ;
}
