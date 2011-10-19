
#include <esve/message/Draw_Receiver.hxx>

namespace esve { namespace message {

Draw_Receiver::
Draw_Receiver()
{
}

Draw_Receiver::
~Draw_Receiver()
{
}

void
Draw_Receiver::
draw_initialize()
{
}

void
Draw_Receiver::
call_draw( Draw_Receiver & a )
{
    a.draw() ;
}

void
Draw_Receiver::
call_draw_initialize( Draw_Receiver & a )
{
    a.draw_initialize() ;
}

}} // namespace esve::message
