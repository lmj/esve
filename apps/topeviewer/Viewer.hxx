
#ifndef apps_topeviewer_Viewer_hxx
#define apps_topeviewer_Viewer_hxx

#include "Tope_Geom.hxx"
#include "UI.hxx"
#include <esve/viewers/dim4/Canned_Viewer.hxx>
#include <esve/components/dim3/Z_Clipper.hxx>
#include <esve/components/dimn/Valuator_Class_Tie.hxx>
#include <esve/ui/extra/File_Selector_Handler.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/types/real.hxx>
#include <string>
#include <memory>

/////////////////////////////////////////////////////////////
//
// Viewer
//
/////////////////////////////////////////////////////////////

class Viewer
    : protected esve::viewers::dim4::Canned_Viewer,
      private esve::components::dimn::Valuator_Handler<esve::types::real>,
      private esve::ui::base::Keyboard_Handler,
      private esve::ui::extra::File_Selector_Handler
{
private:
    typedef esve::viewers::dim4::Canned_Viewer super ;

    struct Initialize_Super
    {
        Initialize_Super( Viewer & ) ;
    } ;

    Viewer( const Viewer & ) ;
    Viewer & operator=( const Viewer & ) ;

    // util
    void read_file( const std::string & ) ;
    void read_config( std::istream & ) ;
    void read_next_config() ;
    void write_config( std::ostream & ) ;
    void write_next_config() ;
    void default_parameters() ;

    // handle
    bool handle_key_push( Key, const Keyboard & ) ;
    bool handle_key_release( Key, const Keyboard & ) ;
    bool handle_file_selector( const File_Selector & ) ;

    bool
    handle_valuator(
        const esve::components::dimn::Valuator<esve::types::real> & ) ;

    // initialize superclass
    Initialize_Super initialize_super ;

    // polytope front-end
    Tope_Geom tope ;

    // camera window
    esve::engine::dim3::Camera & camera ;

    // abstract UI
    UI ui ;

    // additional components

    esve::components::dimn::Valuator_Class_Tie
    <
        Tope_Geom,
        esve::types::real
    >
    tie ;

    esve::components::dim3::Z_Clipper clipper ;

    bool initial_file ;

public:
    Viewer( int argc, char** argv ) ;
    ~Viewer() ;

    using super::takeover ;
} ;

#endif

