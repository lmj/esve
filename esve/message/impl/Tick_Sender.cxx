
#include <esve/message/impl/Tick_Sender.hxx>
#include <esve/message/impl/Tick_Receiver.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/util/MP_Tree.hxx>
#include <cassert>

namespace esve { namespace message { namespace impl {

struct Tick_Receiver::Private
    : public util::MP_Tree_Child<Tick_Sender*, Tick_Receiver*>
{
    typedef
    util::MP_Tree_Child<Tick_Sender*, Tick_Receiver*>
    super ;

    Tick_Receiver & outside ;

    Private( Tick_Receiver & outside_ )
        : super(&outside_),
          outside(outside_) { }

    static void call_tick( message::Tick_Receiver & a )
    {
        Tick_Receiver::call_tick(a) ;
    }
} ;

struct Tick_Sender::Private
    : public util::MP_Tree_Parent<Tick_Sender*, Tick_Receiver*>
{
    typedef
    util::MP_Tree_Parent<Tick_Sender*, Tick_Receiver*>
    super ;

    Private( Tick_Sender & a )
        : super(&a) { }

    static void call_send_tick( message::Tick_Sender & a )
    {
        Tick_Sender::call_send_tick(a) ;
    }
} ;

///////////////////////////////////////////////////////////

Tick_Receiver::
Tick_Receiver()
    : message::Tick_Receiver(),
      m(new Private(*this))
{
}

Tick_Receiver::
~Tick_Receiver()
{
}

impl::Tick_Receiver &
Tick_Receiver::
tick_receiver()
{
    return *this ;
}

///////////////////////////////////////////////////////////

Tick_Sender::
Tick_Sender()
    : message::Tick_Sender(),
      m(new Private(*this))
{
}

Tick_Sender::
~Tick_Sender()
{
}

///////////////////////////////////////////////////////////

void
Tick_Sender::
send_tick()
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("tick", *this, *i) ;
#endif
        Tick_Receiver::Private::call_tick(*i) ;
    }
}

void
Tick_Sender::
add( message::Tick_Receiver & a )
{
    m->add_child(a.tick_receiver().m.get()) ;
}

void
Tick_Sender::
remove( message::Tick_Receiver & a )
{
    m->remove_child(a.tick_receiver().m.get()) ;
}

void
Tick_Sender::
remove_all()
{
    m->remove_children() ;
}

}}} // namespace esve::message::impl
