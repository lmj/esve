
#ifndef esve_components_dimn_Motion_Handler_hxx
#define esve_components_dimn_Motion_Handler_hxx

#include <esve/kernel/Wake_State_Handler.hxx>
#include <esve/message/impl/Update_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Motion_Handler esve/components/dimn/Motion_Handler.hxx
/// @brief Base class for motion handlers (convenience).
///
/// Since it is common to want synchronous time-delta updates along
/// with the ability to wake up, this class is provided for
/// convenience.
///
/// Your handler must connected in a manner to receive both
/// synchronized updates and wake-state messages.
///

class Motion_Handler
    : virtual public message::impl::Update_Receiver,
      public kernel::Wake_State_Handler
{
public:
    Motion_Handler() ;
    ~Motion_Handler() ;

protected:
    // You probably don't need these.  Default implementations of
    // 'return false'.
    bool handle_wake() ;
    bool handle_sleep() ;

    // update() and handle_check_awake() are left for you to define.

private:
    Motion_Handler( const Motion_Handler & ) ;
    Motion_Handler & operator=( const Motion_Handler & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

