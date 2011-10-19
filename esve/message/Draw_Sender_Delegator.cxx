
#include <esve/message/Draw_Sender_Delegator.hxx>

namespace esve { namespace message {

Draw_Sender_Delegator::
Draw_Sender_Delegator( Draw_Sender & base )
    : m(base)
{
}

Draw_Sender_Delegator::
~Draw_Sender_Delegator()
{
}

void
Draw_Sender_Delegator::
add( Draw_Receiver & a )
{
    m.add(a) ;
}

void
Draw_Sender_Delegator::
remove( Draw_Receiver & a )
{
    m.remove(a) ;
}

void
Draw_Sender_Delegator::
remove_all()
{
    m.remove_all() ;
}

void
Draw_Sender_Delegator::
send_draw()
{
    call_send_draw(m) ;
}

void
Draw_Sender_Delegator::
send_draw_initialize()
{
    call_send_draw_initialize(m) ;
}

}} // namespace esve::message
