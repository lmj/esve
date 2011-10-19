
#ifndef esve_ui_base_Display_Details_hxx
#define esve_ui_base_Display_Details_hxx

#include <esve/ui/base/Display.hxx>
#include <string>

namespace esve { namespace ui { namespace base {

///
/// @class Display_Details esve/ui/base/Display_Details.hxx
/// @brief Basic properties of a display.
///

class Display_Details
{
public:
    ///@{
    /// @brief Title appearing on the display.
    virtual const std::string & label() const = 0 ;
    virtual void label( const std::string & ) = 0 ;
    ///@}

    /// Rectangluar dimensions.
    virtual const Display::Rectangle & rectangle() const = 0 ;

    ///
    /// @brief Make this display the current context.
    ///
    /// If there is more than one display showing and you wish to issue
    /// drawing commands outside of a draw tree, then you must
    /// choose which display receives the drawing commands.
    ///
    virtual void make_current() = 0 ;

    virtual ~Display_Details() = 0 ;

protected:
    Display_Details() ;

    /// Called by the system whenever the display is resized.
    virtual void reshape( const Display::Rectangle & ) = 0 ;

    // Allow subclasses to call reshape() on aggregates.
    static void call_reshape( Display_Details & display,
                              const Display::Rectangle & ) ;

private:
    Display_Details( const Display_Details & ) ;
    Display_Details & operator=( const Display_Details & ) ;
} ;

}}} // namespace esve::ui::base

#endif

