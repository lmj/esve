
#ifndef esve_ui_extra_Toggle_hxx
#define esve_ui_extra_Toggle_hxx

#include <esve/ui/extra/Widget.hxx>

namespace esve { namespace ui { namespace extra {

///
/// @class Toggle esve/ui/extra/Toggle.hxx
/// @brief A user-interface widget representing a boolean value.
///
/// Keep in mind that modifying the value in code has a side-effect:
/// it will send a handle_*() message as if the user changed it.
///
/// Setting the value within handle() itself is OK; the recursion is
/// detected and consequently ignored.
///
/// This side-effect of emitting handle() in response to changing the
/// value may seem surprising at first, but in the end it is the right
/// thing.  One should not depend upon the kindness of programmers to
/// manually call update() every time they change something in code.
///
/// The facilities of Caching_Server and Caching_Emitter solve the
/// issue of handle() being emitted before an object is fully
/// constructed.  As of this writing, all front-ends use Simple_Kernel
/// which caches handle() messages during startup/construction phase.
///

class Toggle
    : public Widget
{
public:
    /// Query the current value.
    virtual bool value() const = 0 ;

    ///
    /// @brief Assign a new value.
    /// @return *this
    ///
    virtual Toggle & value( bool ) = 0 ;

protected:
    Toggle() ;

    // creator owns it
    ~Toggle() = 0 ;

private:
    Toggle( const Toggle & ) ;
    Toggle & operator=( const Toggle & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

