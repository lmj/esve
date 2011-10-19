//
// Emit custom user-interface messages.
//

#ifndef apps_polynomialviewer_UI_Emitter_hxx
#define apps_polynomialviewer_UI_Emitter_hxx

#include <esve/kernel/Emitter.hxx>
#include <memory>

class UI_Emitter
    : virtual public esve::kernel::Emitter
{
public:
    enum Widget
    {
        COEFFS,
        REALCURVES_EPSILON,
        WIDTH_RES,
        HEIGHT_RES,
        PLANE_SIZE,
        PLANE_FADE,
        COLOR_SCALE,
        REFZ_SCALE,
        AXES_TOGGLE
    } ;

    UI_Emitter() ;
    ~UI_Emitter() ;

protected:
    virtual bool emit_widget( Widget ) ;

private:
    UI_Emitter( const UI_Emitter & ) ;
    UI_Emitter & operator=( const UI_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

