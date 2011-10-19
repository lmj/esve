
#ifndef esve_ui_base_Keyboard_Handler_hxx
#define esve_ui_base_Keyboard_Handler_hxx

#include <esve/ui/base/Keyboard.hxx>
#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

///
/// @class Keyboard_Handler esve/ui/base/Keyboard_Handler.hxx
/// @brief Receive handle_keyboard_*() messages.
///
/// @see Keyboard_Emitter 
///

class Keyboard_Handler
    : virtual public kernel::Handler
{
private:
    typedef kernel::Handler super ;

    Keyboard_Handler( const Keyboard_Handler & ) ;
    Keyboard_Handler & operator=( const Keyboard_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Keyboard_Handler() ;
    ~Keyboard_Handler() ;

protected:
    /// @typedef Keyboard
    /// @brief .
    typedef ui::base::Keyboard Keyboard ;

    /// @typedef Key
    /// @brief .
    typedef ui::base::Keyboard::Key Key ;

    /// A key was pushed.
    virtual bool handle_key_push( Key, const Keyboard & ) = 0 ;

    /// A key was released.
    virtual bool handle_key_release( Key, const Keyboard & ) = 0 ;

    /// The current state of keyboard keys.
    const Keyboard & keyboard() const ;
} ;

}}} // namespace esve::ui::base

#endif

