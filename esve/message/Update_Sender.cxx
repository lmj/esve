
#include <esve/message/Update_Sender.hxx>

namespace esve { namespace message {

Update_Sender::
Update_Sender()
{
}

Update_Sender::
~Update_Sender()
{
}

void
Update_Sender::
call_send_update( Update_Sender & a )
{
    a.send_update() ;
}

void
Update_Sender::
call_send_update( Update_Sender & a, double dt )
{
    a.send_update(dt) ;
}

}} // namespace esve::message
