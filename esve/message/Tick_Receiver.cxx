
#include <esve/message/Tick_Receiver.hxx>

namespace esve { namespace message {

Tick_Receiver::
Tick_Receiver()
{
}

Tick_Receiver::
~Tick_Receiver()
{
}

void
Tick_Receiver::
call_tick( Tick_Receiver & a )
{
    a.tick() ;
}

}} // namespace esve::message
