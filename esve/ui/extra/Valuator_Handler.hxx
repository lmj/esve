
#ifndef esve_ui_extra_Valuator_Handler_hxx
#define esve_ui_extra_Valuator_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace ui { namespace extra {

class Valuator ;

///
/// @class Valuator_Handler esve/ui/extra/Valuator_Handler.hxx
/// @brief Receive handle_valuator().
///
/// @see Valuator_Emitter
///

class Valuator_Handler
    : virtual public kernel::Handler
{
public:
    ~Valuator_Handler() = 0 ;

protected:
    Valuator_Handler() ;

    /// @typedef Valuator
    /// @brief .
    typedef ui::extra::Valuator Valuator ;

    /// Called when the valuator has changed.
    virtual bool handle_valuator( const Valuator & ) = 0 ;

private:
    Valuator_Handler( const Valuator_Handler & ) ;
    Valuator_Handler & operator=( const Valuator_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::extra

#endif

