#ifndef esve_ui_base_Mouse_Handler_hxx
#define esve_ui_base_Mouse_Handler_hxx

#include <esve/ui/base/Mouse.hxx>
#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

///
/// @class Mouse_Handler esve/ui/base/Mouse_Handler.hxx
/// @brief Receive handle_mouse_*() messages.
///
/// @see Mouse_Emitter 
///

class Mouse_Handler
    : virtual public kernel::Handler 
{
private:
    typedef Handler super ;

    Mouse_Handler( const Mouse_Handler & ) ;
    Mouse_Handler & operator=( const Mouse_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    ~Mouse_Handler() = 0 ;

protected:
    Mouse_Handler() ;

    /// @typedef Mouse
    /// @brief .
    typedef ui::base::Mouse Mouse ;

    /// @typedef Button
    /// @brief .
    typedef ui::base::Mouse::Button Button ;

    /// The mouse moved.
    virtual bool handle_mouse_move( const Mouse & ) = 0 ;

    /// A mouse button was pushed.
    virtual bool handle_mouse_push( Button, const Mouse & ) = 0 ;

    /// A mouse button was released.
    virtual bool handle_mouse_release( Button, const Mouse & ) = 0 ;

    /// The current state of the mouse.
    const Mouse & mouse() const ;
} ;

}}} // namespace esve::ui::base

#endif

