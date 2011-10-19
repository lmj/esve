
#ifndef esve_kernel_Wake_State_Handler_hxx
#define esve_kernel_Wake_State_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Wake_State_Handler esve/kernel/Wake_State_Handler.hxx
/// @brief Receive handle_check_awake(), handle_wake(), handle_sleep().
///
/// @see Wake_State_Emitter
///

class Wake_State_Handler
    : virtual public Handler
{
public:
    Wake_State_Handler() ;
    ~Wake_State_Handler() ;

protected:
    ///
    /// @brief Do you want to be awake?
    ///
    /// If currently awake, a return value of true indicates a desire
    /// to stay awake.  If not currently awake, a return value of true
    /// indicates a desire to wake up.
    ///
    virtual bool handle_check_awake( bool currently_awake ) = 0 ;

    /// The command to wake up.
    virtual bool handle_wake() = 0 ;

    /// The command to sleep.
    virtual bool handle_sleep() = 0 ;

    /// Are we awake?
    bool awake() const ;

private:
    Wake_State_Handler( const Wake_State_Handler & ) ;
    Wake_State_Handler & operator=( const Wake_State_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

