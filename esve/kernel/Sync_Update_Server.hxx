
#ifndef esve_kernel_Sync_Update_Server_hxx
#define esve_kernel_Sync_Update_Server_hxx

#include <esve/kernel/Wake_State_Handler.hxx>
#include <esve/kernel/Sync_Update_Sender.hxx>

namespace esve { namespace kernel {

///
/// @class Sync_Update_Server esve/kernel/Sync_Update_Server.hxx
/// @brief Provide synchronous updates across wake/sleep cycles.
///
/// A Sync_Update_Server is both a Wake_State_Handler and a
/// Sync_Update_Sender.
///
/// When a Sync_Update_Server receives handle_wake(), it calls
/// Sync_Update_Sender::reset() on itself.  In this manner a
/// consistent time-delta is provided to children.
///
/// A Sync_Update_Server will not send synchronized update()s unless
/// it is awake().
///

class Sync_Update_Server
    : public Wake_State_Handler,
      public Sync_Update_Sender
{
public:
    Sync_Update_Server() ;

    ~Sync_Update_Server() ;

protected:
    bool handle_check_awake( bool currently_awake ) ;
    bool handle_wake() ;
    bool handle_sleep() ;

    void tick() ;

private:
    Sync_Update_Server( const Sync_Update_Server & ) ;
    Sync_Update_Server & operator=( const Sync_Update_Server & ) ;
} ;

}} // namespace esve::kernel

#endif

