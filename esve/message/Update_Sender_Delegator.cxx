
#include <esve/message/Update_Sender_Delegator.hxx>

namespace esve { namespace message {

Update_Sender_Delegator::
Update_Sender_Delegator( Update_Sender & base )
    : m(base)
{
}

Update_Sender_Delegator::
~Update_Sender_Delegator()
{
}

void
Update_Sender_Delegator::
add( Update_Receiver & a )
{
    m.add(a) ;
}

void
Update_Sender_Delegator::
remove( Update_Receiver & a )
{
    m.remove(a) ;
}

void
Update_Sender_Delegator::
remove_all()
{
    m.remove_all() ;
}

void
Update_Sender_Delegator::
send_update()
{
    call_send_update(m) ;
}

void
Update_Sender_Delegator::
send_update( double dt )
{
    call_send_update(m, dt) ;
}

}} // namespace esve::message
