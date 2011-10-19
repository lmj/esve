
#ifndef esve_kernel_Async_Update_Server_hxx
#define esve_kernel_Async_Update_Server_hxx

#include <esve/message/impl/Update_Node.hxx>
#include <esve/kernel/Kernel_Node.hxx>

namespace esve { namespace kernel {

///
/// @class Async_Update_Server esve/kernel/Async_Update_Server.hxx
/// @brief Sends asynchronous updates in response to handle_*() messages.
///
/// The Async_Update_Server has dual membership as a node in the
/// emitter/handler tree and as a node in the update tree.
///
/// If one of its child handlers returns true then an asynchronous
/// update() message is sent to all its update-children.
///

class Async_Update_Server
    : public Kernel_Node,
      public message::impl::Update_Node
{
public:
    Async_Update_Server() ;
    ~Async_Update_Server() ;

protected:
    // Kernel_Node override
    bool dispatch_encoded( const message::Handle_Args & ) ;

private:
    Async_Update_Server( const Async_Update_Server & ) ;
    Async_Update_Server & operator=( const Async_Update_Server & ) ;
} ;

}} // namespace esve::kernel

#endif

