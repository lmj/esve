//
// User-interface.
//
// This is the only platform-specific class, implemented in platform/
//

#ifndef apps_polynomialviewer_UI_hxx
#define apps_polynomialviewer_UI_hxx

#include "UI_Emitter.hxx"
#include <memory>

namespace  esve { namespace ui { namespace base {

class Display ;

}}} // namespace esve::ui::base

class UI
    : public UI_Emitter
{
public:
    UI( esve::ui::base::Display & camera ) ;

    // read current coefficients
    const double* coeffs_begin() const ;
    const double* coeffs_end() const ;

    // set new coefficients
    void coeffs( const double* begin, const double* end ) ;

    double realcurves_epsilon() const ;
    void realcurves_epsilon( double ) ;

    int width_res() const ;
    void width_res( int ) ;

    int height_res() const ;
    void height_res( int ) ;

    double plane_size() const ;
    void plane_size( double ) ;

    double plane_fade() const ;
    void plane_fade( double ) ;

    double color_scale() const ;
    void color_scale( double ) ;

    double refz_scale() const ;
    void refz_scale( double ) ;

    bool axes_toggle() const ;
    void axes_toggle( bool ) ;

    ~UI() ;

private:
    UI( const UI & ) ;
    UI & operator=( const UI & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

