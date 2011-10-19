
#include <esve/kernel/Async_Update_Server.hxx>
#include <esve/message/Active_State.hxx>
#include <esve/message/Update_Sender.hxx>

namespace esve { namespace kernel {

Async_Update_Server::
Async_Update_Server()
{
}

Async_Update_Server::
~Async_Update_Server()
{
}

bool
Async_Update_Server::
dispatch_encoded( const message::Handle_Args & args )
{
    bool handled = false ;

    handled = Kernel_Node::dispatch_encoded(args) ;

    if( handled )
    {
        message::impl::Update_Node::send_update() ;
    }

    return handled ;
}

}} // namespace esve::kernel
