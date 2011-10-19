
#include <esve/message/Compute_Sender.hxx>

namespace esve { namespace message {

Compute_Sender::
Compute_Sender()
{
}

Compute_Sender::
~Compute_Sender()
{
}

void
Compute_Sender::
call_send_compute( Compute_Sender & a )
{
    a.send_compute() ;
}

}} // namespace esve::message
