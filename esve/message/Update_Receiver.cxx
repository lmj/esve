
#include <esve/message/Update_Receiver.hxx>

namespace esve { namespace message {

Update_Receiver::
Update_Receiver()
{
}

Update_Receiver::
~Update_Receiver()
{
}

void
Update_Receiver::
call_update( Update_Receiver & a )
{
    a.update() ;
}

void
Update_Receiver::
call_update( Update_Receiver & a, double dt )
{
    a.update(dt) ;
}

}} // namespace esve::message
