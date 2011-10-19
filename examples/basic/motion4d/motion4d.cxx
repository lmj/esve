
#include "../../../apps/hopfviewer/Torus.hxx"
#include <esve/viewers/dim4/Basic_Viewer.hxx>
#include <esve/components/dim4/Motion_Frame.hxx>
#include <esve/components/dim4/Simple_Rotation_Handler.hxx>
#include <esve/engine/dim4/impl/Frame.hxx>
#include <esve/engine/dim4/Make_Geom.hxx>
#include <esve/types/quat.hxx>

using esve::viewers::dim4::Basic_Viewer ;
using esve::components::dim4::Motion_Frame ;
using esve::components::dim4::Simple_Rotation_Handler ;
using esve::engine::dim4::impl::Frame ;
using esve::engine::dim4::Make_Geom ;
using esve::types::quat ;
using esve::types::real ;

int main()
{
    Motion_Frame motion_frame ;

    {
        // choose two vectors ...
        quat r = quat(1, 0, 0, 0) ;
        quat s = quat(0, 1, 0, 0) ;

        // make sure they are orthonormal ..
        r /= abs(r) ;
        s -= dot(r, s)*r ;
        s /= abs(s) ;

        // choose two angular velocities: one velocity rotates in the
        // (r,s)-plane, the other rotates in the (r,s)-complement
        // plane.  (In radians per second.)
        real alpha = 0.25 ;
        real beta = 0.10 ;

        // set up the rotation
        motion_frame.rotate_velocity(alpha, beta, r, s) ;
    }

    Basic_Viewer viewer ;
    viewer.add_handler(motion_frame) ;

    Make_Geom<Torus> torus ;
    torus.gap(0.1) ;
    viewer.add_geom(torus) ;

    //
    // frame hierarchy:
    //
    // (viewer's root frame)
    //        |
    //        |
    //        | (parent of)
    //        |
    //        |
    //  inversion_frame
    //        |
    //        |
    //        | (parent of)
    //        |
    //        |
    //  rotation_frame
    //        |
    //        |
    //        | (parent of)
    //        |
    //        |
    //   motion_frame
    //        |
    //        |
    //        | (parent of)
    //        |
    //        |
    //      torus
    //

    // gcc-3.3.1 bug --- can't compile the next line:
    //Frame inversion_frame(Transform(quat(1), quat(-1), quat(1), quat(1))) ;

    Frame inversion_frame ;
    inversion_frame.peek_transform().b(quat(-1)) ;
    inversion_frame.peek_transform().c(quat(1)) ;

    Frame rotation_frame ;
    viewer.add_frame(inversion_frame) ;
    inversion_frame.add(rotation_frame) ;
    rotation_frame.add(motion_frame) ;
    motion_frame.add(torus) ;

    Simple_Rotation_Handler rotation_handler(rotation_frame.peek_transform()) ;
    viewer.add_handler(rotation_handler) ;

    viewer.create_camera("motion frame test") ;
    viewer.create_light() ;

    return viewer.takeover() ;
}

#include "../../../apps/hopfviewer/Torus.cxx"
