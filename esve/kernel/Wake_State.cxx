
#include <esve/kernel/Wake_State_Emitter.hxx>
#include <esve/kernel/Wake_State_Handler.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>

namespace esve { namespace kernel {

namespace {

struct Wake_State_Handle_Args : public message::Handle_Args
{
    enum ID
    {
        CHECK_AWAKE,
        WAKE,
        SLEEP
    } ;

    ID id ;

    Wake_State_Handle_Args( ID id_ )
        : id(id_) { }

    Wake_State_Handle_Args( const Wake_State_Handle_Args & a )
        : Handle_Args(),
          id(a.id) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Wake_State_Handle_Args(id)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        switch( id )
        {
        case CHECK_AWAKE:
            esve_report(CHECK_AWAKE) ;
            break ;
        case WAKE:
            esve_report(WAKE) ;
            break ;
        case SLEEP:
            esve_report(SLEEP) ;
            break ;
        }
    }
#endif
} ;

} // anon namespace

//////////////////////////////////////////////////////////

struct Wake_State_Handler::Private
    : public message::impl::Handle_Receiver
{
    Wake_State_Handler & outside ;
    bool awake ;

    Private( Wake_State_Handler & outside_ )
        : outside(outside_),
          awake(false) { }

    bool handle( const message::Handle_Args & ) ;
} ;

Wake_State_Handler::
Wake_State_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

Wake_State_Handler::
~Wake_State_Handler()
{
}

bool
Wake_State_Handler::
awake() const
{
    return m->awake ;
}

bool
Wake_State_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Wake_State_Handle_Args* wake_state_args =
        dynamic_cast<const Wake_State_Handle_Args*>(&generic_args) )
    {
        switch( wake_state_args->id )
        {
        case Wake_State_Handle_Args::CHECK_AWAKE:
            {
                handled = outside.handle_check_awake(awake) ;
            }
            break ;

        case Wake_State_Handle_Args::WAKE:
            if( awake )
            {
                // do nothing
            }
            else
            {
                awake = true ;
                handled = outside.handle_wake() ;
            }
            break ;

        case Wake_State_Handle_Args::SLEEP:
            if( awake )
            {
                awake = false ;
                handled = outside.handle_sleep() ;
            }
            else
            {
                // do nothing
            }
            break ;
        }
    }

    return handled ;
}

////////////////////////////////////////////////////////////

struct Wake_State_Emitter::Private
    : public message::impl::Handle_Sender
{
    using Handle_Sender::send_handle ;
} ;

Wake_State_Emitter::
Wake_State_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

Wake_State_Emitter::
~Wake_State_Emitter()
{
}

bool
Wake_State_Emitter::
emit_check_awake()
{
    return
        m->send_handle(
            Wake_State_Handle_Args(Wake_State_Handle_Args::CHECK_AWAKE)) ;
}

bool
Wake_State_Emitter::
emit_sleep()
{
    return
        m->send_handle(
            Wake_State_Handle_Args(Wake_State_Handle_Args::SLEEP)) ;
}

bool
Wake_State_Emitter::
emit_wake()
{
    return
        m->send_handle(
            Wake_State_Handle_Args(Wake_State_Handle_Args::WAKE)) ;
}

}} // namespace esve::kernel
