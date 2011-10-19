
#include <esve/message/impl/Draw_Sender.hxx>
#include <esve/message/impl/Draw_Receiver.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/util/MP_Tree.hxx>
#include <cassert>

namespace esve { namespace message { namespace impl {

struct Draw_Receiver::Private
    : public util::MP_Tree_Child<Draw_Sender*, Draw_Receiver*>
{
    typedef
    util::MP_Tree_Child<Draw_Sender*, Draw_Receiver*>
    super ;

    Draw_Receiver & outside ;

    Private( Draw_Receiver & outside_ )
        : super(&outside_),
          outside(outside_) { }

    static void call_draw( message::Draw_Receiver & a )
    {
        Draw_Receiver::call_draw(a) ;
    }

    static void call_draw_initialize( message::Draw_Receiver & a )
    {
        Draw_Receiver::call_draw_initialize(a) ;
    }
} ;

struct Draw_Sender::Private
    : public util::MP_Tree_Parent<Draw_Sender*, Draw_Receiver*>
{
    typedef
    util::MP_Tree_Parent<Draw_Sender*, Draw_Receiver*>
    super ;

    Private( Draw_Sender & a )
        : super(&a) { }

    static void call_send_draw( message::Draw_Sender & a )
    {
        Draw_Sender::call_send_draw(a) ;
    }
} ;

///////////////////////////////////////////////////////////

Draw_Receiver::
Draw_Receiver()
    : message::Draw_Receiver(),
      m(new Private(*this))
{
}

Draw_Receiver::
~Draw_Receiver()
{
}

impl::Draw_Receiver &
Draw_Receiver::
draw_receiver()
{
    return *this ;
}

///////////////////////////////////////////////////////////

Draw_Sender::
Draw_Sender()
    : message::Draw_Sender(),
      m(new Private(*this))
{
}

Draw_Sender::
~Draw_Sender()
{
}

///////////////////////////////////////////////////////////

void
Draw_Sender::
send_draw()
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("draw", *this, *i) ;
#endif
        Draw_Receiver::Private::call_draw(*i) ;
    }
}

void
Draw_Sender::
send_draw_initialize()
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("draw_initialize", *this, *i) ;
#endif
        Draw_Receiver::Private::call_draw_initialize(*i) ;
    }
}

void
Draw_Sender::
add( message::Draw_Receiver & a )
{
    m->add_child(a.draw_receiver().m.get()) ;
}

void
Draw_Sender::
remove( message::Draw_Receiver & a )
{
    m->remove_child(a.draw_receiver().m.get()) ;
}

void
Draw_Sender::
remove_all()
{
    m->remove_children() ;
}

}}} // namespace esve::message::impl
