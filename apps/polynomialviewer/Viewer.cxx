
#include "Viewer.hxx"
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dimn/Materials.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/message/Draw_Sender.hxx>
#include <esve/math/constants.hxx>
#include <esve/gl/gl.hxx>

using esve::engine::dim3::Camera ;
using esve::gl::gl ;
using esve::types::real ;
using esve::types::pure ;
using esve::types::rgba ;

const real PI_2 = real(esve::math::constants::PI_2) ;

//////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////

Viewer::
Viewer( int argc, char** argv )
    : Basic_Viewer(),
      command_line(argc, argv, "s:f:"),
      surface(),
      plane(),
      axis_x(),
      axis_y(),
      camera(super::create_camera("polynomialviewer",
                                  Camera::Rectangle(500, 500))),
      light(super::create_light()),
      ui(camera),
      initializer(),
      scene(),
      plane_draw_node(),
      axes_draw_node(),
      object_frame(),
      show_fps(),
      rotation_handler(object_frame.peek_transform())
{
    ///////////////////////////////
    // frame tree
    ///////////////////////////////

    super::add_frame(object_frame) ;
    object_frame.add(surface) ;
    object_frame.add(plane) ;
    object_frame.add(axis_x) ;
    object_frame.add(axis_y) ;

    // the light rides piggy-back on the camera
    camera.peek_frame().add(light.peek_frame()) ;

    ///////////////////////////////
    // draw tree
    ///////////////////////////////

    super::peek_draw_sender().add(scene) ;

    scene.add(surface) ;
    scene.add(axes_draw_node) ;
    scene.add(plane_draw_node) ;

    axes_draw_node.add(axis_x) ;
    axes_draw_node.add(axis_y) ;
    plane_draw_node.add(plane) ;

    ///////////////////////////////
    // handle tree
    ///////////////////////////////

    super::peek_kernel().add_emitter(ui) ;
    super::add_handler(*this) ;
    super::add_handler(rotation_handler) ;

    ///////////////////////////////
    // initialize tree
    ///////////////////////////////

    super::peek_draw_initializer().remove_all() ;
    super::peek_draw_initializer().add(initializer) ;

    ///////////////////////////////
    // computation tree
    ///////////////////////////////

    super::peek_compute_sender().add(surface) ;
    super::peek_compute_sender().add(plane) ;

    ///////////////////////////////
    // components
    ///////////////////////////////

    camera.peek_frame().peek_transform().identity() ;
    camera.peek_frame().peek_transform().translate(pure(0.0, 0.0, 5.0)) ;

    light.peek_frame().peek_transform().identity() ;
    light.peek_frame().peek_transform().translate(pure(-1.0, 3.0, 3.0)) ;
    light.peek_materials().diffuse(rgba(0.7, 0.7, 0.7, 1.0)) ;
    light.peek_materials().ambient(rgba(0.3, 0.3, 0.3, 1.0)) ;

    rotation_handler.sensitivity(0.75) ;

    // rotate to the y-axis
    axis_y.peek_transform().rotate(PI_2, pure(0, 0, 1)) ;

    ///////////////////////////////
    // command-line options
    ///////////////////////////////

    if( command_line.option('s') )
    {
        rotation_handler.sensitivity(
            std::atof(command_line.option_argument('s').c_str())) ;
    }
    if( command_line.option('f') )
    {
        super::peek_kernel().add_update_receiver(show_fps) ;
        show_fps.sampling_interval(
            std::atof(command_line.option_argument('f').c_str())) ;
    }

    // start off with parabola
    const int NUM_COEFFS = 3 ;
    double coeffs[NUM_COEFFS] = { -0.5, 0.0, 1.0 } ;

    // prime the cache
    ui.coeffs(coeffs, coeffs + NUM_COEFFS) ;
    ui.realcurves_epsilon(0.02) ;
    ui.width_res(300) ;
    ui.height_res(300) ;
    ui.plane_size(1.0) ;
    ui.plane_fade(0.2) ;
    ui.color_scale(1.0) ;
    ui.refz_scale(1.0) ;
    ui.axes_toggle(true) ;
}

Viewer::
~Viewer()
{
}

//////////////////////////////////////////////////
// OpenGL routines
//////////////////////////////////////////////////

void
Viewer::
Initializer::
draw_initialize()
{
    const GLfloat global_ambient[] = { 0.0, 0.0, 0.0, 1.0 } ;

    glEnable(GL_LIGHTING) ;
    glEnable(GL_COLOR_MATERIAL) ;
    glEnable(GL_DEPTH_TEST) ;
    glEnable(GL_NORMALIZE) ;
    glEnable(GL_BLEND) ;

    glShadeModel(GL_SMOOTH) ;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

    glClearColor(0.6, 0.6, 0.8, 0.0) ;

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE) ;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient) ;

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
}

void
Viewer::
Axis::
draw()
{
    gl::PushAttrib sentry(GL_LIGHTING_BIT) ;
    glDisable(GL_LIGHTING) ;

    {
        gl::Begin sentry(GL_LINES) ;
        glColor3d(0.9, 0.9, 0.9) ;
        glVertex3d(-5.0, 0.0, 0.0) ;
        glVertex3d(5.0, 0.0, 0.0) ;
    }
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
    case UI::COLOR_SCALE:
        {
            surface.color_scale(ui.color_scale()) ;
        }
        return true ;

    case UI::REFZ_SCALE:
        {
            surface.refz_scale(ui.refz_scale()) ;
        }
        return true ;

    case UI::AXES_TOGGLE:
        {
            axes_draw_node.active(ui.axes_toggle()) ;
        }
        return true ;

    case UI::REALCURVES_EPSILON:
        {
            surface.realcurves_epsilon(ui.realcurves_epsilon()) ;
        }
        return true ;

    case UI::WIDTH_RES:
    case UI::HEIGHT_RES:
        {
            surface.resolution(ui.width_res(), ui.height_res()) ;
        }
        return true ;

    case UI::PLANE_SIZE:
    case UI::PLANE_FADE:
        {
            plane.size(ui.plane_size()) ;
            plane.fade(ui.plane_fade()) ;

            if( ui.plane_size() == 0.0 ||
                ui.plane_fade() == 0.0 )
            {
                glDisable(GL_BLEND) ;
                plane_draw_node.active(false) ;
            }
            else
            {
                glEnable(GL_BLEND) ;
                plane_draw_node.active(true) ;
            }
        }
        return true ;

    case UI::COEFFS:
        {
            surface.coeffs(ui.coeffs_begin(), ui.coeffs_end()) ;
        }
        return true ;
    }

    return false ;
}
