
#include <esve/kernel/Sync_Update_Server.hxx>

namespace esve { namespace kernel {

Sync_Update_Server::
Sync_Update_Server()
    : Wake_State_Handler(),
      Sync_Update_Sender()
{
}

Sync_Update_Server::
~Sync_Update_Server()
{
}

bool
Sync_Update_Server::
handle_check_awake( bool )
{
    return false ;
}

bool
Sync_Update_Server::
handle_wake()
{
    Sync_Update_Sender::reset() ;
    return true ;
}

bool
Sync_Update_Server::
handle_sleep()
{
    return false ;
}

void
Sync_Update_Server::
tick()
{
    if( awake() )
    {
        Sync_Update_Sender::tick() ;
    }
}

}} // namespace esve::kernel
