
#ifndef platform_fltk_esve_platform_Representation_hxx
#define platform_fltk_esve_platform_Representation_hxx

#include <string>

class Fl_Gl_Window ;

namespace esve { namespace ui { namespace base {

class Display ;

}}} // namespace esve::ui::base

namespace esve { namespace platform {

//////////////////////////////////////////////////////////////
//
// Representation
//
// Get an underlying representation.
//
//////////////////////////////////////////////////////////////

struct Representation
{
    typedef Fl_Gl_Window Display_Rep ;
    static const Display_Rep & rep( const ui::base::Display & ) ;
    static Display_Rep & rep( ui::base::Display & ) ;
} ;

}} // namespace esve::platform

#endif

