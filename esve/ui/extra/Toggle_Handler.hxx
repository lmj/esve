
#ifndef esve_ui_extra_Toggle_Handler_hxx
#define esve_ui_extra_Toggle_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace ui { namespace extra {

class Toggle ;

///
/// @class Toggle_Handler esve/ui/extra/Toggle_Handler.hxx
/// @brief Receive handle_toggle().
///
/// @see Toggle_Emitter 
///

class Toggle_Handler
    : virtual public kernel::Handler
{
public:
    ~Toggle_Handler() = 0 ;

protected:
    Toggle_Handler() ;

    /// @typedef Toggle
    /// @brief .
    typedef ui::extra::Toggle Toggle ;

    /// The toggle has changed.
    virtual bool handle_toggle( const Toggle & ) = 0 ;

private:
    Toggle_Handler( const Toggle_Handler & ) ;
    Toggle_Handler & operator=( const Toggle_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::extra

#endif

