
//
// Basic_Viewer and its descendants use a common handle_*() tree by
// default.
//
// Although convenient, this has an obvious limitation: by design, a
// handler can't tell who is emitting the handle_*() messages it uses.
//
// For more complex situations, the intended strategy is to use
// several servers to divide the handle_*() tree into appropriate
// chunks.
//
// The following is an example of such a strategy.  There are two
// cameras, two icosahedra, and two rotation handlers.  Each rotation
// handler listens to just one camera and rotates just one
// icosahedron.
//

#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/components/dim3/Rotation_Handler.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/kernel/Wake_State_Server.hxx>
#include <esve/kernel/Sync_Update_Server.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Update_Sender.hxx>
#include <esve/message/Tick_Sender.hxx>
#include <esve/geom/dim3/Icosahedron.hxx>
#include <esve/types/pure.hxx>

using esve::viewers::dim3::Basic_Viewer ;
using esve::engine::dim3::Camera ;
using esve::components::dim3::Rotation_Handler ;
using esve::engine::dim3::Make_Geom ;
using esve::engine::dim3::impl::Frame ;
using esve::kernel::Wake_State_Server ;
using esve::kernel::Sync_Update_Server ;
using esve::geom::dim3::Icosahedron ;
using esve::types::pure ;

struct Viewer : public Basic_Viewer
{
    typedef Basic_Viewer super ;

    Frame root_frame ;

    Make_Geom<Icosahedron> icos1 ;
    Make_Geom<Icosahedron> icos2 ;

    Frame offset_frame1 ;
    Frame offset_frame2 ;

    Rotation_Handler rotation_handler1 ;
    Rotation_Handler rotation_handler2 ;

    Camera & camera1 ;
    Camera & camera2 ;

    Wake_State_Server wake_state_server ;
    Sync_Update_Server synchronized_update_server ;

    Viewer()
        : super(),
          root_frame(),
          icos1(),
          icos2(),
          offset_frame1(),
          offset_frame2(),
          rotation_handler1(icos1.peek_transform()),
          rotation_handler2(icos2.peek_transform()),
          camera1(super::create_camera("Camera 1")),
          camera2(super::create_camera("Camera 2")),
          wake_state_server(),
          synchronized_update_server()
    {
        super::create_light() ;

        super::add_geom(icos1) ;
        super::add_geom(icos2) ;

        // modified frame tree

        super::add_frame(root_frame) ;

        root_frame.add(offset_frame1) ;
        root_frame.add(offset_frame2) ;
        root_frame.add(camera1.peek_frame()) ;
        root_frame.add(camera2.peek_frame()) ;

        offset_frame1.add(icos1) ;
        offset_frame2.add(icos2) ;

        offset_frame1.peek_transform().translate(pure(-1, 0, 0)) ;
        offset_frame2.peek_transform().translate(pure(1, 0, 0)) ;

        // first handle_*() tree

        super::add_handler(rotation_handler1) ;

        // second handle_*() tree

        camera2.remove_all_handlers() ;

        super::peek_kernel().add_driver_handler(wake_state_server) ;
        camera2.add_handler(wake_state_server) ;

        wake_state_server.add_handler(synchronized_update_server) ;
        wake_state_server.add_handler(rotation_handler2) ;

        // second update() tree

        synchronized_update_server.add(rotation_handler2) ;
        synchronized_update_server.add(root_frame) ;

        // tick() message
        super::
            peek_kernel().
            peek_tick_sender().
            add(synchronized_update_server) ;
    }
} ;

int main()
{
    return Viewer().takeover() ;
}
