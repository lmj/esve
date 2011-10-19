
#include "Viewer.hxx"
#include <esve/engine/dim3/Camera.hxx>
#include <esve/engine/dim3/Camera_Details.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/math/constants.hxx>

//////////////////////////////////////////////////
// using
//////////////////////////////////////////////////

using esve::engine::dim4::Transform ;
using esve::types::real ;
using esve::types::pure ;

//////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////

const double PI_2 = real(esve::math::constants::PI_2) ;
const double SCALE_FUDGE = 0.75 ;
const double INITIAL_FAR_CLIP = 70.0 ;
const double INITIAL_NEAR_CLIP = 0.1 ;
const double INITIAL_INVERSION = 0.65 ;

//////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////

Viewer::
Viewer( int argc, char** argv )
    : super(argc, argv),
      torus(),
      camera(super::create_camera("hopfviewer")),
      ui(camera),
      torus_controller(ui, torus),
      clipper(camera, torus)
{
    super::create_light() ;
    super::modal_tie(ui) ;

    // handle tree
    super::peek_kernel().add_emitter(ui) ;
    super::add_handler(*this) ;
    super::add_handler(torus_controller) ;

    // compute, draw, frame trees
    super::add_geom(torus) ;

    // compute tree
    super::peek_compute_sender().add(clipper) ;

    // initial parameters
    super::scaling(1.0*SCALE_FUDGE) ;
    super::inversion(INITIAL_INVERSION) ;

    // home transform
    {
        Transform home ;
        home.rotate(0, -PI_2, pure(0, 1, 0)) ;
        super::home_transform(home) ;
        super::rotation(home.a(), home.d()) ;
    }

    // other params

    camera.peek_camera_details().near_clip(INITIAL_NEAR_CLIP) ;
    camera.peek_camera_details().far_clip(INITIAL_FAR_CLIP) ;
    torus.initial_min_z(-10) ;

    ui.inversion(super::inversion()) ;
    ui.scale(1.0) ;
    ui.signal_initialize_autoquad() ;
}

Viewer::
~Viewer()
{
}

//////////////////////////////////////////////////
// handle
//////////////////////////////////////////////////

bool
Viewer::
handle_widget( Widget widget )
{
    switch( widget )
    {
    case UI::INVERSION:
        {
            super::inversion(ui.inversion()) ;
        }
        return true ;

    case UI::SCALE:
        {
            super::scaling(ui.scale()*SCALE_FUDGE) ;
            clipper.scale(ui.scale()*SCALE_FUDGE) ;
        }
        return true ;

    case UI::SLIDE_SURFACE_TOGGLE:
        {
            super::slide(ui.slide_surface_toggle()) ;
        }
        return true ;

    case UI::CULL_TOGGLE:
        {
            if( ui.cull_toggle() )
            {
                glEnable(GL_CULL_FACE) ;
            }
            else
            {
                glDisable(GL_CULL_FACE) ;
            }
        }
        return true ;

    default:
        ;
    }

    return false ;
}

bool
Viewer::
handle_autoquad_strips_to_squares()
{
    return false ;
}

bool
Viewer::
handle_autoquad_squares_to_strips()
{
    return false ;
}

bool
Viewer::
handle_autoquad_activated()
{
    return false ;
}

bool
Viewer::
handle_autoquad_deactivated()
{
    return false ;
}

