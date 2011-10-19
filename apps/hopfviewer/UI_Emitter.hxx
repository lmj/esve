//
// Emit custom user-interface messages.
//

#ifndef apps_hopfviewer_UI_Emitter_hxx
#define apps_hopfviewer_UI_Emitter_hxx

#include <esve/kernel/Emitter.hxx>
#include <memory>

class UI_Emitter
    : virtual public esve::kernel::Emitter
{
public:
    enum Widget
    {
        CULL_TOGGLE,
        SLIDE_SURFACE_TOGGLE,
        HELP_TOGGLE,
        RATIO_ANGLE,
        WIDTH,
        HEIGHT,
        WIDTH_RES,
        HEIGHT_RES,
        GAP,
        SKEW,
        INVERSION,
        SCALE,
        WIND_U,
        WIND_V,
        AUTOQUAD
    } ;

    ~UI_Emitter() ;

protected:
    UI_Emitter() ;

    virtual bool emit_widget( Widget ) ;
    virtual bool emit_autoquad_strips_to_squares() ;
    virtual bool emit_autoquad_squares_to_strips() ;
    virtual bool emit_autoquad_activated() ;
    virtual bool emit_autoquad_deactivated() ;

private:
    UI_Emitter( const UI_Emitter & ) ;
    UI_Emitter & operator=( const UI_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

