
#include <esve/message/impl/Update_Sender.hxx>
#include <esve/message/impl/Update_Receiver.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/util/MP_Tree.hxx>
#include <cassert>

namespace esve { namespace message { namespace impl {

struct Update_Receiver::Private
    : public util::MP_Tree_Child<Update_Sender*, Update_Receiver*>
{
    typedef
    util::MP_Tree_Child<Update_Sender*, Update_Receiver*>
    super ;

    Update_Receiver & outside ;

    Private( Update_Receiver & outside_ )
        : super(&outside_),
          outside(outside_) { }

    static void call_update( message::Update_Receiver & a )
    {
        Update_Receiver::call_update(a) ;
    }

    static void call_update( message::Update_Receiver & a,
                             double dt )
    {
        Update_Receiver::call_update(a, dt) ;
    }
} ;

struct Update_Sender::Private
    : public util::MP_Tree_Parent<Update_Sender*, Update_Receiver*>
{
    typedef
    util::MP_Tree_Parent<Update_Sender*, Update_Receiver*>
    super ;

    Private( Update_Sender & a )
        : super(&a) { }

    static void call_send_update( message::Update_Sender & a )
    {
        Update_Sender::call_send_update(a) ;
    }

    static void call_send_update( message::Update_Sender & a,
                                  double dt )
    {
        Update_Sender::call_send_update(a) ;
    }
} ;

///////////////////////////////////////////////////////////

Update_Receiver::
Update_Receiver()
    : message::Update_Receiver(),
      m(new Private(*this))
{
}

Update_Receiver::
~Update_Receiver()
{
}

impl::Update_Receiver &
Update_Receiver::
update_receiver()
{
    return *this ;
}

///////////////////////////////////////////////////////////

Update_Sender::
Update_Sender()
    : message::Update_Sender(),
      m(new Private(*this))
{
}

Update_Sender::
~Update_Sender()
{
}

///////////////////////////////////////////////////////////

void
Update_Sender::
send_update()
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("update", *this, *i) ;
#endif
        Update_Receiver::Private::call_update(*i) ;
    }
}

void
Update_Sender::
send_update( double dt )
{
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)
        diagnostic::header("update", *this, *i) ;
        esve_report(dt) ;
#endif
        Update_Receiver::Private::call_update(*i, dt) ;
    }
}

void
Update_Sender::
add( message::Update_Receiver & a )
{
    m->add_child(a.update_receiver().m.get()) ;
}

void
Update_Sender::
remove( message::Update_Receiver & a )
{
    m->remove_child(a.update_receiver().m.get()) ;
}

void
Update_Sender::
remove_all()
{
    m->remove_children() ;
}

}}} // namespace esve::message::impl
