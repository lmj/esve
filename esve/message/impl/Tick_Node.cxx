
#include <esve/message/impl/Tick_Node.hxx>

namespace esve { namespace message { namespace impl {

Tick_Node::
Tick_Node()
    : Active_State(),
      Tick_Receiver(),
      Tick_Sender()
{
}

Tick_Node::
~Tick_Node()
{
}

void
Tick_Node::
tick()
{
    if( active() )
    {
        // hook!
        send_tick() ;
    }
}

}}} // namespace esve::message::impl
