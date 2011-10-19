
#include <esve/message/Handle_Sender_Delegator.hxx>

namespace esve { namespace message {

Handle_Sender_Delegator::
Handle_Sender_Delegator( Handle_Sender & base )
    : m(base)
{
}

Handle_Sender_Delegator::
~Handle_Sender_Delegator()
{
}

void
Handle_Sender_Delegator::
add( Handle_Receiver & a )
{
    m.add(a) ;
}

void
Handle_Sender_Delegator::
remove( Handle_Receiver & a )
{
    m.remove(a) ;
}

void
Handle_Sender_Delegator::
remove_all()
{
    m.remove_all() ;
}

bool
Handle_Sender_Delegator::
send_handle( const Handle_Args & args )
{
    return call_send_handle(m, args) ;
}

}} // namespace esve::message
