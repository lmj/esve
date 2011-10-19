
#ifndef esve_kernel_Main_Driver_hxx
#define esve_kernel_Main_Driver_hxx

#include <esve/kernel/Wake_State_Emitter.hxx>
#include <esve/kernel/Driver_Emitter.hxx>
#include <esve/message/Tick_Sender_Stowed.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Main_Driver esve/kernel/Main_Driver.hxx
/// @brief Top-level main loop.
///

class Main_Driver
    : virtual public message::Tick_Sender_Stowed,
      public Wake_State_Emitter,
      public Driver_Emitter
{
public:
    Main_Driver() ;

    /// Enter the main loop.
    virtual int takeover() ;

    ~Main_Driver() ;

    message::Tick_Sender & peek_tick_sender() ;

private:
    Main_Driver( const Main_Driver & ) ;
    Main_Driver & operator=( const Main_Driver & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

