
#include <esve/kernel/Wake_State_Server.hxx>

namespace esve { namespace kernel {

struct Wake_State_Server::Private
{
    bool awake ;

    Private( bool awake_ )
        : awake(awake_) { }
} ;

Wake_State_Server::
Wake_State_Server()
    : m(new Private(false))
{
}

Wake_State_Server::
~Wake_State_Server()
{
}

bool
Wake_State_Server::
handle_check_awake( bool )
{
    //
    // We are actually sending handle_check_awake() twice: once here
    // and once via the message::Handle_Node::send_handle() relay.
    //
    // This could be corrected by exposing check_awake's message::Handle_Args
    // then intercepting it in send_handle(), but in the end it
    // doesn't really matter.
    //

    bool handled = false ;

    if( active() )
    {
        const bool want_to_be_awake =
            Wake_State_Emitter::emit_check_awake() ;

        if( want_to_be_awake && !m->awake )
        {
            m->awake = true ;
            Wake_State_Emitter::emit_wake() ;
        }
        else if( !want_to_be_awake && m->awake )
        {
            m->awake = false ;
            Wake_State_Emitter::emit_sleep() ;
        }
    }

    return handled ;
}

bool
Wake_State_Server::
handle_wake()
{
    return false ;
}

bool
Wake_State_Server::
handle_sleep()
{
    return false ;
}

}} // namespace esve::kernel
