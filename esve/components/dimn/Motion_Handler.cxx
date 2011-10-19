
#include <esve/components/dimn/Motion_Handler.hxx>

namespace esve { namespace components { namespace dimn {

Motion_Handler::
Motion_Handler()
    : Update_Receiver(),
      Wake_State_Handler()
{
}

Motion_Handler::
~Motion_Handler()
{
}

bool
Motion_Handler::
handle_wake()
{
    return false ;
}

bool
Motion_Handler::
handle_sleep()
{
    return false ;
}

}}} // namespace esve::components::dimn
