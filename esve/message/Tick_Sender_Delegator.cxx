
#include <esve/message/Tick_Sender_Delegator.hxx>

namespace esve { namespace message {

Tick_Sender_Delegator::
Tick_Sender_Delegator( Tick_Sender & base )
    : m(base)
{
}

Tick_Sender_Delegator::
~Tick_Sender_Delegator()
{
}

void
Tick_Sender_Delegator::
add( Tick_Receiver & a )
{
    m.add(a) ;
}

void
Tick_Sender_Delegator::
remove( Tick_Receiver & a )
{
    m.remove(a) ;
}

void
Tick_Sender_Delegator::
remove_all()
{
    m.remove_all() ;
}

void
Tick_Sender_Delegator::
send_tick()
{
    call_send_tick(m) ;
}

}} // namespace esve::message
