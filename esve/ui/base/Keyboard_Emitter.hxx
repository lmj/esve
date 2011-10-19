
#ifndef esve_ui_base_Keyboard_Emitter_hxx
#define esve_ui_base_Keyboard_Emitter_hxx

#include <esve/ui/base/Keyboard.hxx>
#include <esve/kernel/Emitter.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

///
/// @class Keyboard_Emitter esve/ui/base/Keyboard_Emitter.hxx
/// @brief Send handle_keyboard_*() messages.
///
/// @see Keyboard_Handler 
///

class Keyboard_Emitter
    : virtual public kernel::Emitter
{
public:
    ~Keyboard_Emitter() ;

protected:
    Keyboard_Emitter() ;

    /// @brief You have somehow figured out that a key was pushed;
    /// send that information.
    virtual bool emit_key_push( Keyboard::Key ) ;

    /// @brief You have somehow figured out that a key was released;
    /// send that information.
    virtual bool emit_key_release( Keyboard::Key ) ;

    /// @brief You have somehow figured out that all keys should be
    /// released (as far as the application is concerned); send that
    /// information.
    virtual bool emit_key_release_all() ;

private:
    Keyboard_Emitter( const Keyboard_Emitter & ) ;
    Keyboard_Emitter & operator=( const Keyboard_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::base

#endif

