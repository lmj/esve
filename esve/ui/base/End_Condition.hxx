
#ifndef esve_ui_base_End_Condition_hxx
#define esve_ui_base_End_Condition_hxx

#include <esve/kernel/Driver_Handler.hxx>

namespace esve { namespace ui { namespace base {

///
/// @class End_Condition esve/ui/base/End_Condition.hxx
/// @brief End the driving state under some platform-specific condition.
///
/// Returns true from handle_driver_check_finished() when the
/// platform-specific condition is met (for instance, Control-Q, or
/// all the Displays being closed).
///

class End_Condition
    : public kernel::Driver_Handler
{
public:
    End_Condition() ;
    ~End_Condition() ;

protected:
    bool handle_driver_start() ;
    bool handle_driver_check_finished() ;
    bool handle_driver_finish() ;

private:
    End_Condition( const End_Condition & ) ;
    End_Condition & operator=( const End_Condition & ) ;
} ;

}}} // namespace esve::ui::base

#endif

