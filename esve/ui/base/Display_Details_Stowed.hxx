
#ifndef esve_ui_base_Display_Details_Stowed_hxx
#define esve_ui_base_Display_Details_Stowed_hxx

#include <string>

namespace esve { namespace ui { namespace base {

class Display_Details ;

///
/// @class Display_Details_Stowed esve/ui/base/Display_Details_Stowed.hxx
/// @brief Stowed display details.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///

class Display_Details_Stowed
{
public:
    ///@{
    /// @brief Peek at the display details.
    virtual const ui::base::Display_Details &
    peek_display_details() const = 0 ;
    virtual ui::base::Display_Details &
    peek_display_details() = 0 ;
    ///@}

    virtual ~Display_Details_Stowed() = 0 ;

protected:
    Display_Details_Stowed() ;

private:
    Display_Details_Stowed( const Display_Details_Stowed & ) ;
    Display_Details_Stowed & operator=( const Display_Details_Stowed & ) ;
} ;

}}} // namespace esve::ui::base

#endif

