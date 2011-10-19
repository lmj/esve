
#ifndef esve_kernel_Driver_Handler_hxx
#define esve_kernel_Driver_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Driver_Handler esve/kernel/Driver_Handler.hxx
/// @brief Receive handle_driver_*() messages.
///
/// @see Driver_Emitter
///

class Driver_Handler
    : virtual public Handler
{
private:
    typedef Handler super ;

    Driver_Handler( const Driver_Handler & ) ;
    Driver_Handler & operator=( const Driver_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Driver_Handler() ;
    ~Driver_Handler() ;

protected:
    /// We have just entered a driving loop.
    virtual bool handle_driver_start() = 0 ;

    /// Do you want the driving loop to end?
    virtual bool handle_driver_check_finished() = 0 ;

    /// We are about to exit the driving loop.
    virtual bool handle_driver_finish() = 0 ;

    /// Are we inside a driving loop?
    bool driver_started() const ;
} ;

}} // namespace esve::kernel

#endif

