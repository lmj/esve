
#include <esve/message/Compute_Receiver.hxx>

namespace esve { namespace message {

Compute_Receiver::
Compute_Receiver()
{
}

Compute_Receiver::
~Compute_Receiver()
{
}

void
Compute_Receiver::
call_compute( Compute_Receiver & a )
{
    a.compute() ;
}

}} // namespace esve::message
