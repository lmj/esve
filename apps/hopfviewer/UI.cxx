
#include "UI_Emitter.hxx"
#include "UI_Handler.hxx"
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>

using esve::message::impl::Handle_Sender ;
using esve::message::impl::Handle_Receiver ;
using esve::message::Handle_Args ;

namespace {

enum Args_ID
{
    WIDGET,
    AUTOQUAD_STRIPS_TO_SQUARES,
    AUTOQUAD_SQUARES_TO_STRIPS,
    AUTOQUAD_ACTIVATED,
    AUTOQUAD_DEACTIVATED
} ;

struct UI_Handle_Args
    : public Handle_Args
{
    Args_ID id ;
    UI_Emitter::Widget widget ;

    UI_Handle_Args( Args_ID id_,
                    UI_Emitter::Widget widget_ )
        : Handle_Args(),
          id(id_),
          widget(widget_) { }

    UI_Handle_Args( const UI_Handle_Args & a )
        : Handle_Args(),
          id(a.id),
          widget(a.widget) { }

    std::auto_ptr<Handle_Args> clone() const
    {
        return
            std::auto_ptr<Handle_Args>(
                new UI_Handle_Args(id, widget)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(id) ;
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
    return
        m->send_handle(UI_Handle_Args(WIDGET, a)) ;
}

bool
UI_Emitter::
emit_autoquad_strips_to_squares()
{
    return
        m->send_handle(UI_Handle_Args(AUTOQUAD_STRIPS_TO_SQUARES, Widget())) ;
}

bool
UI_Emitter::
emit_autoquad_squares_to_strips()
{
    return
        m->send_handle(UI_Handle_Args(AUTOQUAD_SQUARES_TO_STRIPS, Widget())) ;
}

bool
UI_Emitter::
emit_autoquad_activated()
{
    return
        m->send_handle(UI_Handle_Args(AUTOQUAD_ACTIVATED, Widget())) ;
}

bool
UI_Emitter::
emit_autoquad_deactivated()
{
    return
        m->send_handle(UI_Handle_Args(AUTOQUAD_DEACTIVATED, Widget())) ;
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
    if( const UI_Handle_Args* ui_args =
        dynamic_cast<const UI_Handle_Args*>(&generic_args) )
    {
        switch( ui_args->id )
        {
        case WIDGET:
            return outside.handle_widget(ui_args->widget) ;
        case AUTOQUAD_STRIPS_TO_SQUARES:
            return outside.handle_autoquad_strips_to_squares() ;
        case AUTOQUAD_SQUARES_TO_STRIPS:
            return outside.handle_autoquad_squares_to_strips() ;
        case AUTOQUAD_ACTIVATED:
            return outside.handle_autoquad_activated() ;
        case AUTOQUAD_DEACTIVATED:
            return outside.handle_autoquad_deactivated() ;
        }
    }

    return false ;
}

