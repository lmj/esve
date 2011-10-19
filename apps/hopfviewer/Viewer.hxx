
#ifndef apps_hopfviewer_Viewer_hxx
#define apps_hopfviewer_Viewer_hxx

#include "UI.hxx"
#include "Torus_Mod.hxx"
#include "Torus_Controller.hxx"
#include <esve/viewers/dim4/Canned_Viewer.hxx>
#include <esve/components/dim4/Report_Min_Z.hxx>
#include <esve/components/dim3/Z_Clipper.hxx>
#include <esve/engine/dim4/Make_Geom.hxx>

/////////////////////////////////////////////////////////////
//
// Viewer
//
/////////////////////////////////////////////////////////////

class Viewer
    : protected esve::viewers::dim4::Canned_Viewer,
      private UI_Handler
{
private:
    typedef esve::viewers::dim4::Canned_Viewer super ;

    typedef
    esve::components::dim4::Report_Min_Z
    <
        esve::engine::dim4::Make_Geom
        <
            Torus_Mod
        >
    >
    Torus_Geom ;

    Viewer( const Viewer & ) ;
    Viewer & operator=( const Viewer & ) ;

    // messages from the UI
    bool handle_widget( Widget ) ;
    bool handle_autoquad_strips_to_squares() ;
    bool handle_autoquad_squares_to_strips() ;
    bool handle_autoquad_activated() ;
    bool handle_autoquad_deactivated() ;

    // geometric object
    Torus_Geom torus ;

    // camera window
    esve::engine::dim3::Camera & camera ;

    // abstract UI
    UI ui ;

    // handles the majority of UI messages
    Torus_Controller torus_controller ;

    // auto-adjust camera clip
    esve::components::dim3::Z_Clipper clipper ;

public:
    Viewer( int argc, char** argv ) ;
    ~Viewer() ;

    using super::takeover ;
} ;

#endif

