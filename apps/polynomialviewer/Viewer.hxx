#ifndef apps_polynomialviewer_Viewer_hxx
#define apps_polynomialviewer_Viewer_hxx

#include "Polynomial_Surface.hxx"
#include "Plane.hxx"
#include "UI_Handler.hxx"
#include "UI.hxx"
#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/components/dim3/Oriented_Rotation_Handler.hxx>
#include <esve/components/dimn/Show_FPS.hxx>
#include <esve/components/dimn/Command_Line.hxx>
#include <esve/engine/dim3/Make_Frame.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/engine/dim3/Light.hxx>
#include <esve/kernel/Main_Driver.hxx>
#include <esve/message/impl/Draw_Node.hxx>

/////////////////////////////////////////////////////////////
//
// Viewer
//
/////////////////////////////////////////////////////////////

class Viewer
    : protected esve::viewers::dim3::Basic_Viewer,
      private UI_Handler
{
private:
    typedef esve::viewers::dim3::Basic_Viewer super ;

    struct Initializer
        : virtual public esve::message::impl::Draw_Receiver
    {
        void draw() { }
        void draw_initialize() ;
    } ;

    struct Axis
    {
        void draw() ;
    } ;

    typedef
    esve::engine::dim3::Make_Geom
    <
        Polynomial_Surface
    >
    Surface_Geom ;

    typedef
    esve::engine::dim3::Make_Geom
    <
        Plane
    >
    Plane_Geom ;

    Viewer( const Viewer & ) ;
    Viewer & operator=( const Viewer & ) ;

    bool handle_widget( Widget ) ;

    // util
    esve::components::dimn::Command_Line command_line ;

    // geometric objects
    Surface_Geom surface ;
    Plane_Geom plane ;
    esve::engine::dim3::Make_Frame<Axis> axis_x ;
    esve::engine::dim3::Make_Frame<Axis> axis_y ;

    // camera window
    esve::engine::dim3::Camera & camera ;

    // light
    esve::engine::dim3::Light & light ;

    // the abstract UI
    UI ui ;

    // additional components
    Initializer initializer ;
    esve::message::impl::Draw_Node scene ;
    esve::message::impl::Draw_Node plane_draw_node ;
    esve::message::impl::Draw_Node axes_draw_node ;
    esve::engine::dim3::impl::Frame object_frame ;
    esve::components::dimn::Show_FPS show_fps ;
    esve::components::dim3::Oriented_Rotation_Handler rotation_handler ;

public:
    Viewer( int argc, char** argv ) ;
    ~Viewer() ;

    using super::takeover ;
} ;

#endif

