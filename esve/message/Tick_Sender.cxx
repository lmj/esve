
#include <esve/message/Tick_Sender.hxx>

namespace esve { namespace message {

Tick_Sender::
Tick_Sender()
{
}

Tick_Sender::
~Tick_Sender()
{
}

void
Tick_Sender::
call_send_tick( Tick_Sender & a )
{
    a.send_tick() ;
}

}} // namespace esve::message
