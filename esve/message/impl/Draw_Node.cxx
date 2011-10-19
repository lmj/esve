
#include <esve/message/impl/Draw_Node.hxx>

namespace esve { namespace message { namespace impl {

Draw_Node::
Draw_Node()
    : Active_State(),
      Draw_Receiver(),
      Draw_Sender()
{
}

Draw_Node::
~Draw_Node()
{
}

void
Draw_Node::
draw()
{
    if( active() )
    {
        // hook!
        send_draw() ;
    }
}

void
Draw_Node::
draw_initialize()
{
    if( active() )
    {
        // hook!
        send_draw_initialize() ;
    }
}

}}} // namespace esve::message::impl
