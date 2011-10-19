
#include "UI_Emitter.hxx"
#include "UI_Handler.hxx"
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>

using esve::message::impl::Handle_Receiver ;
using esve::message::impl::Handle_Sender ;
using esve::message::Handle_Args ;

namespace {

struct UI_Handle_Args : public Handle_Args
{
    UI_Emitter::Widget widget ;

    UI_Handle_Args( UI_Emitter::Widget widget_ )
        : Handle_Args(),
          widget(widget_) { }

    UI_Handle_Args( const UI_Handle_Args & a )
        : Handle_Args(),
          widget(a.widget) { }

    std::auto_ptr<Handle_Args> clone() const
    {
        return
            std::auto_ptr<Handle_Args>(
                new UI_Handle_Args(widget)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(widget) ;
    }
#endif
} ;

} // anon namespace

struct UI_Emitter::Private
    : public Handle_Sender
{
    using Handle_Sender::send_handle ;
} ;

UI_Emitter::
UI_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

UI_Emitter::
~UI_Emitter()
{
}

bool
UI_Emitter::
emit_widget( Widget a )
{
    return m->send_handle(UI_Handle_Args(a)) ;
}

struct UI_Handler::Private
    : public Handle_Receiver
{
    UI_Handler & outside ;

    Private( UI_Handler & outside_ )
        : outside(outside_) { }
    
    bool handle( const Handle_Args & ) ;
} ;

UI_Handler::
UI_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

UI_Handler::
~UI_Handler()
{
}

bool
UI_Handler::Private::
handle( const Handle_Args & generic_args )
{
    bool handled = false ;

    if( const UI_Handle_Args* ui_args =
        dynamic_cast<const UI_Handle_Args*>(&generic_args) )
    {
        handled = outside.handle_widget(ui_args->widget) ;
    }

    return handled ;
}

