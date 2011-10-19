
#include <esve/message/Compute_Sender_Delegator.hxx>

namespace esve { namespace message {

Compute_Sender_Delegator::
Compute_Sender_Delegator( Compute_Sender & base )
    : m(base)
{
}

Compute_Sender_Delegator::
~Compute_Sender_Delegator()
{
}

void
Compute_Sender_Delegator::
add( Compute_Receiver & a )
{
    m.add(a) ;
}

void
Compute_Sender_Delegator::
remove( Compute_Receiver & a )
{
    m.remove(a) ;
}

void
Compute_Sender_Delegator::
remove_all()
{
    m.remove_all() ;
}

void
Compute_Sender_Delegator::
send_compute()
{
    call_send_compute(m) ;
}

}} // namespace esve::message
