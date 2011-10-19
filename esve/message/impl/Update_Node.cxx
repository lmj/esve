
#include <esve/message/impl/Update_Node.hxx>

namespace esve { namespace message { namespace impl {

Update_Node::
Update_Node()
    : Active_State(),
      Update_Receiver(),
      Update_Sender()
{
}

Update_Node::
~Update_Node()
{
}

void
Update_Node::
update()
{
    if( active() )
    {
        // hook!
        send_update() ;
    }
}

void
Update_Node::
update( double dt )
{
    if( active() )
    {
        // hook!
        send_update(dt) ;
    }
}

}}} // namespace esve::message::impl
