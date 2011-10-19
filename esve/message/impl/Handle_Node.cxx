
#include <esve/message/impl/Handle_Node.hxx>

namespace esve { namespace message { namespace impl {

Handle_Node::
Handle_Node()
    : Active_State(),
      Handle_Receiver(),
      Handle_Sender()
{
}

Handle_Node::
~Handle_Node()
{
}

bool
Handle_Node::
handle( const Handle_Args & args )
{
    bool handled = false ;
    
    if( active() )
    {
        // hook!
        handled = send_handle(args) ;
    }

    return handled ;
}

}}} // namespace esve::message::impl
