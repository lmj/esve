
#include <esve/message/Draw_Sender.hxx>

namespace esve { namespace message {

Draw_Sender::
Draw_Sender()
{
}

Draw_Sender::
~Draw_Sender()
{
}

void
Draw_Sender::
call_send_draw( Draw_Sender & a )
{
    a.send_draw() ;
}

void
Draw_Sender::
call_send_draw_initialize( Draw_Sender & a )
{
    a.send_draw_initialize() ;
}

}} // namespace esve::message
