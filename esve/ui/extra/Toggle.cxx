
#include <esve/ui/extra/Toggle.hxx>
#include <esve/ui/extra/Toggle_Creator.hxx>
#include <esve/ui/extra/Toggle_Emitter.hxx>
#include <esve/ui/extra/Toggle_Handler.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <algorithm>
#include <cassert>
#include <vector>

namespace esve { namespace ui { namespace extra {

namespace {

struct Toggle_Handle_Args : public message::Handle_Args
{
    const Toggle & toggle ;

    Toggle_Handle_Args( const Toggle & toggle_ )
        : Handle_Args(),
          toggle(toggle_) { }

    Toggle_Handle_Args( const Toggle_Handle_Args & a )
        : Handle_Args(),
          toggle(a.toggle) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Toggle_Handle_Args(toggle)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(&toggle) ;
        esve_report(toggle.value()) ;
    }
#endif
} ;

} // anon namespace

//////////////////////////////////////////////////////////////

Toggle::
Toggle()
{
}

Toggle::
~Toggle()
{
}

//////////////////////////////////////////////////////////////

Toggle_Creator::
Toggle_Creator()
{
}

Toggle_Creator::
~Toggle_Creator()
{
}

//////////////////////////////////////////////////////////////

Toggle_Emitter::
Toggle_Emitter()
{
}

Toggle_Emitter::
~Toggle_Emitter()
{
}

bool
Toggle_Emitter::
emit_toggle( const Toggle & toggle )
{
    return emit_widget(toggle, Toggle_Handle_Args(toggle)) ;
}

//////////////////////////////////////////////////////////////

struct Toggle_Handler::Private
    : public message::impl::Handle_Receiver
{
    Toggle_Handler & outside ;

    Private( Toggle_Handler & outside_ )
        : outside(outside_) { }
    
    bool handle( const message::Handle_Args & ) ;
} ;

Toggle_Handler::
Toggle_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

Toggle_Handler::
~Toggle_Handler()
{
}

bool
Toggle_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Toggle_Handle_Args* valuator_args =
        dynamic_cast<const Toggle_Handle_Args*>(&generic_args) )
    {
        handled = outside.handle_toggle(valuator_args->toggle) ;
    }

    return handled ;
}

}}} // namespace esve::ui::extra
