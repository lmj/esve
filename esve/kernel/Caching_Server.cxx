
#include <esve/kernel/Caching_Server.hxx>

namespace esve { namespace kernel {

Caching_Server::
Caching_Server()
    : Caching_Node(true)
{
}

Caching_Server::
~Caching_Server()
{
}

bool
Caching_Server::
handle_driver_start()
{
    return Caching_Node::stop_caching() ;
}

bool
Caching_Server::
handle_driver_check_finished()
{
    return false ;
}

bool
Caching_Server::
handle_driver_finish()
{
    return false ;
}

}} // namespace esve::kernel
