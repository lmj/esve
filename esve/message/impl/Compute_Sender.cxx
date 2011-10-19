
#include <esve/message/impl/Compute_Sender.hxx>
#include <esve/message/impl/Compute_Receiver.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/util/MP_Tree.hxx>
#include <cassert>

namespace esve { namespace message { namespace impl {

struct Compute_Receiver::Private
    : public util::MP_Tree_Child<Compute_Sender*, Compute_Receiver*>
{
    typedef
    util::MP_Tree_Child<Compute_Sender*, Compute_Receiver*>
    super ;

    Compute_Receiver & outside ;

    Private( Compute_Receiver & outside_ )
        : super(&outside_),
          outside(outside_) { }

    static void call_compute( message::Compute_Receiver & a )
    {
        Compute_Receiver::call_compute(a) ;
    }
} ;

struct Compute_Sender::Private
    : public util::MP_Tree_Parent<Compute_Sender*, Compute_Receiver*>
{
    typedef
    util::MP_Tree_Parent<Compute_Sender*, Compute_Receiver*>
    super ;

    Private( Compute_Sender & a )
        : super(&a) { }

    static void call_send_compute( message::Compute_Sender & a )
    {
        Compute_Sender::call_send_compute(a) ;
    }
} ;

///////////////////////////////////////////////////////////

Compute_Receiver::
Compute_Receiver()
    : message::Compute_Receiver(),
      m(new Private(*this))
{
}

Compute_Receiver::
~Compute_Receiver()
{
}

impl::Compute_Receiver &
Compute_Receiver::
compute_receiver()
{
    return *this ;
}

///////////////////////////////////////////////////////////

Compute_Sender::
Compute_Sender()
    : message::Compute_Sender(),
      m(new Private(*this))
{
}

Compute_Sender::
~Compute_Sender()
{
}

///////////////////////////////////////////////////////////

void
Compute_Sender::
send_compute()
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("compute", *this, *i) ;
#endif
        Compute_Receiver::Private::call_compute(*i) ;
    }
}

void
Compute_Sender::
add( message::Compute_Receiver & a )
{
    m->add_child(a.compute_receiver().m.get()) ;
}

void
Compute_Sender::
remove( message::Compute_Receiver & a )
{
    m->remove_child(a.compute_receiver().m.get()) ;
}

void
Compute_Sender::
remove_all()
{
    m->remove_children() ;
}

}}} // namespace esve::message::impl
