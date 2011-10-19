
#include <esve/ui/extra/Valuator.hxx>
#include <esve/ui/extra/Valuator_Emitter.hxx>
#include <esve/ui/extra/Valuator_Handler.hxx>
#include <esve/ui/extra/Valuator_Creator.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <cassert>
#include <vector>
#include <algorithm>

namespace esve { namespace ui { namespace extra {

namespace {

struct Valuator_Handle_Args : public message::Handle_Args
{
    const Valuator & valuator ;

    Valuator_Handle_Args( const Valuator & valuator_ )
        : Handle_Args(),
          valuator(valuator_) { }

    Valuator_Handle_Args( const Valuator_Handle_Args & a )
        : Handle_Args(),
          valuator(a.valuator) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Valuator_Handle_Args(valuator)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(&valuator) ;
        esve_report(valuator.value()) ;
    }
#endif
} ;

} // anon namespace

///////////////////////////////////////////////////////////////

Valuator::
Valuator()
{
}

Valuator::
~Valuator()
{
}

///////////////////////////////////////////////////////////////

Valuator_Creator::
Valuator_Creator()
{
}

Valuator_Creator::
~Valuator_Creator()
{
}

///////////////////////////////////////////////////////////////

Valuator_Emitter::
Valuator_Emitter()
{
}

Valuator_Emitter::
~Valuator_Emitter()
{
}

bool
Valuator_Emitter::
emit_valuator( const Valuator & valuator )
{
    return emit_widget(valuator, Valuator_Handle_Args(valuator)) ;
}

///////////////////////////////////////////////////////////////

struct Valuator_Handler::Private
    : public message::impl::Handle_Receiver
{
    Valuator_Handler & outside ;
    
    Private( Valuator_Handler & outside_ )
        : message::Handle_Receiver(),
          outside(outside_) { }
    
    bool handle( const message::Handle_Args & ) ;
} ;

Valuator_Handler::
Valuator_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

Valuator_Handler::
~Valuator_Handler()
{
}

bool
Valuator_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Valuator_Handle_Args* valuator_args =
        dynamic_cast<const Valuator_Handle_Args*>(&generic_args) )
    {
        handled = outside.handle_valuator(valuator_args->valuator) ;
    }

    return handled ;
}

}}} // namespace esve::ui::extra
