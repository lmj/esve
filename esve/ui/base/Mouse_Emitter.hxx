
#ifndef esve_ui_base_Mouse_Emitter_hxx
#define esve_ui_base_Mouse_Emitter_hxx

#include <esve/ui/base/Mouse.hxx>
#include <esve/kernel/Emitter.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

///
/// @class Mouse_Emitter esve/ui/base/Mouse_Emitter.hxx
/// @brief Send handle_mouse_*() messages.
///
/// @see Mouse_Handler 
///

class Mouse_Emitter
    : virtual public kernel::Emitter
{
public:
    ~Mouse_Emitter() ;

    /// @brief You have somehow figured out that the mouse moved; send
    /// that information.
    virtual bool emit_mouse_move( const Mouse::Position & position ) ;

    /// @brief You have somehow figured out that a mouse button was
    /// pushed; send that information.
    virtual bool emit_mouse_push( Mouse::Button,
                                  const Mouse::Position & position ) ;

    /// @brief You have somehow figured out that a mouse button was
    /// released; send that information.
    virtual bool emit_mouse_release( Mouse::Button,
                                     const Mouse::Position & position ) ;

protected:
    Mouse_Emitter() ;

private:
    Mouse_Emitter( const Mouse_Emitter & ) ;
    Mouse_Emitter & operator=( const Mouse_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::base

#endif

