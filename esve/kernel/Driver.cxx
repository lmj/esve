
#include <esve/kernel/Driver_Emitter.hxx>
#include <esve/kernel/Driver_Handler.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>

namespace esve { namespace kernel {

namespace {

struct Driver_Handle_Args : public message::Handle_Args
{
    enum ID
    {
        START,
        CHECK_FINISHED,
        FINISH
    } ;

    ID id ;

    Driver_Handle_Args( ID id_ )
        : id(id_) { }

    Driver_Handle_Args( const Driver_Handle_Args & a )
        : message::Handle_Args(),
          id(a.id) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Driver_Handle_Args(id)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        switch( id )
        {
        case START:
            esve_report(START) ;
            break ;
        case CHECK_FINISHED:
            esve_report(CHECK_FINISHED) ;
            break ;
        case FINISH:
            esve_report(FINISH) ;
            break ;
        }
    }
#endif
} ;

} // anon namespace

///////////////////////////////////////////////////////////////

struct Driver_Handler::Private
    : public message::impl::Handle_Receiver
{
    Driver_Handler & outside ;
    bool driver_started ;

    Private( Driver_Handler & outside_ )
        : outside(outside_),
          driver_started(false) { }

    bool handle( const message::Handle_Args & ) ;
} ;

Driver_Handler::
Driver_Handler()
    : super(),
      m(new Private(*this))
{
    add_decoder(*m) ;
}

Driver_Handler::
~Driver_Handler()
{
}

bool
Driver_Handler::
driver_started() const
{
    return m->driver_started ;
}

bool
Driver_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Driver_Handle_Args* wake_state_args =
        dynamic_cast<const Driver_Handle_Args*>(&generic_args) )
    {
        switch( wake_state_args->id )
        {
        case Driver_Handle_Args::START:
            {
                driver_started = true ;
                handled = outside.handle_driver_start() ;
            }
            break ;

        case Driver_Handle_Args::CHECK_FINISHED:
            {
                handled = outside.handle_driver_check_finished() ;
            }
            break ;

        case Driver_Handle_Args::FINISH:
            {
                handled = outside.handle_driver_finish() ;
                driver_started = false ;
            }
            break ;
        }
    }

    return handled ;
}

///////////////////////////////////////////////////////////////

struct Driver_Emitter::Private
    : public message::impl::Handle_Sender
{
    using Handle_Sender::send_handle ;
} ;

Driver_Emitter::
Driver_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

Driver_Emitter::
~Driver_Emitter()
{
}

bool
Driver_Emitter::
emit_driver_start()
{
    return
        m->send_handle(
            Driver_Handle_Args(Driver_Handle_Args::START)) ;
}

bool
Driver_Emitter::
emit_driver_check_finished()
{
    return
        m->send_handle(Driver_Handle_Args(
            Driver_Handle_Args::CHECK_FINISHED)) ;
}

bool
Driver_Emitter::
emit_driver_finish()
{
    return
        m->send_handle(
            Driver_Handle_Args(Driver_Handle_Args::FINISH)) ;
}

}} // namespace esve::kernel
