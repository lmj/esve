
#include <esve/message/impl/Compute_Node.hxx>

namespace esve { namespace message { namespace impl {

Compute_Node::
Compute_Node()
    : Active_State(),
      Compute_Receiver(),
      Compute_Sender()
{
}

Compute_Node::
~Compute_Node()
{
}

void
Compute_Node::
compute()
{
    if( active() )
    {
        // hook!
        send_compute() ;
    }
}

}}} // namespace esve::message::impl
