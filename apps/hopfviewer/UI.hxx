//
// User-interface.
//
// This is the only platform-specific class, implemented in platform/
//

#ifndef apps_hopfviewer_UI_hxx
#define apps_hopfviewer_UI_hxx

#include "UI_Emitter.hxx"
#include <esve/ui/extra/Modal_Tie.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

class Display ;

}}} // namespace esve::ui::base

class UI
    : virtual public esve::ui::extra::Modal_Tie,
      public UI_Emitter
{
public:
    UI( esve::ui::base::Display & ) ;

    // app-to-ui signals

    void toggle_display_fullscreen() ;
    void toggle_modal_visible() ;
    void signal_autoquad_sufficient() ;
    void signal_autoquad_insufficient() ;
    void signal_initialize_autoquad() ;

    // ui values

    enum Autoquad_Mode
    {
        AUTOQUAD_NONE,
        AUTOQUAD_STRIPS,
        AUTOQUAD_SQUARES
    } ;
    Autoquad_Mode autoquad_mode() const ;
    void autoquad_mode( Autoquad_Mode ) ;

    bool cull_toggle() const ;
    void cull_toggle( bool ) ;

    bool slide_surface_toggle() const ;
    void slide_surface_toggle( bool ) ;

    bool help_toggle() const ;
    void help_toggle( bool ) ;

    double ratio_angle() const ;
    void ratio_angle( double ) ;

    double width() const ;
    void width( double ) ;
    void width_range( double , double ) ;

    double height() const ;
    void height( double ) ;
    void height_range( double , double ) ;

    double gap() const ;
    void gap( double ) ;

    int width_res() const ;
    void width_res( int ) ;

    int height_res() const ;
    void height_res( int ) ;

    double skew() const ;
    void skew( double ) ;

    double inversion() const ;
    void inversion( double ) ;

    double scale() const ;
    void scale( double ) ;

    double wind_u() const ;
    void wind_u( double ) ;

    double wind_v() const ;
    void wind_v( double ) ;

    int autoquad() const ;
    void autoquad( int ) ;

    ~UI() ;

private:
    UI( const UI & ) ;
    UI & operator=( const UI & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

