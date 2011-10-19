
#include <esve/message/Handle_Receiver.hxx>

namespace esve { namespace message {

Handle_Receiver::
Handle_Receiver()
{
}

Handle_Receiver::
~Handle_Receiver()
{
}

bool
Handle_Receiver::
call_handle( Handle_Receiver & a, const Handle_Args & args )
{
    return a.handle(args) ;
}

}} // namespace esve::message
