
#include <esve/message/Handle_Sender.hxx>

namespace esve { namespace message {

Handle_Sender::
Handle_Sender()
{
}

Handle_Sender::
~Handle_Sender()
{
}

bool
Handle_Sender::
call_send_handle( Handle_Sender & a, const Handle_Args & args )
{
    return a.send_handle(args) ;
}

}} // namespace esve::message
