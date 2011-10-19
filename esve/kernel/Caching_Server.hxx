
#ifndef esve_kernel_Caching_Server_hxx
#define esve_kernel_Caching_Server_hxx

#include <esve/kernel/Caching_Node.hxx>
#include <esve/kernel/Driver_Handler.hxx>

namespace esve { namespace kernel {

///
/// @class Caching_Server esve/kernel/Caching_Server.hxx
/// @brief Cache handle_*() messages during startup.
///
/// Caching stops when handle_driver_start() is received.
///

class Caching_Server
    : public Caching_Node,
      public Driver_Handler
{
public:
    Caching_Server() ;
    ~Caching_Server() ;

protected:
    bool handle_driver_start() ;
    bool handle_driver_check_finished() ;
    bool handle_driver_finish() ;

private:
    Caching_Server( const Caching_Server & ) ;
    Caching_Server & operator=( const Caching_Server & ) ;
} ;

}} // namespace esve::kernel

#endif

