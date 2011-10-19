
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/util/MP_Tree.hxx>
#include <cassert>

namespace esve { namespace message { namespace impl {

struct Handle_Receiver::Private
    : public util::MP_Tree_Child<Handle_Sender*, Handle_Receiver*>
{
    typedef
    util::MP_Tree_Child<Handle_Sender*, Handle_Receiver*>
    super ;

    Handle_Receiver & outside ;

    Private( Handle_Receiver & outside_ )
        : super(&outside_),
          outside(outside_) { }

    static bool call_handle( message::Handle_Receiver & a,
                             const Handle_Args & args )
    {
        return Handle_Receiver::call_handle(a, args) ;
    }
} ;

struct Handle_Sender::Private
    : public util::MP_Tree_Parent<Handle_Sender*, Handle_Receiver*>
{
    typedef
    util::MP_Tree_Parent<Handle_Sender*, Handle_Receiver*>
    super ;

    Private( Handle_Sender & a )
        : super(&a) { }

    static bool call_send_handle( message::Handle_Sender & a,
                                  const Handle_Args & args )
    {
        return Handle_Sender::call_send_handle(a, args) ;
    }
} ;

///////////////////////////////////////////////////////////

Handle_Receiver::
Handle_Receiver()
    : message::Handle_Receiver(),
      m(new Private(*this))
{
}

Handle_Receiver::
~Handle_Receiver()
{
}

impl::Handle_Receiver &
Handle_Receiver::
handle_receiver()
{
    return *this ;
}

///////////////////////////////////////////////////////////

Handle_Sender::
Handle_Sender()
    : message::Handle_Sender(),
      m(new Private(*this))
{
}

Handle_Sender::
~Handle_Sender()
{
}

///////////////////////////////////////////////////////////

bool
Handle_Sender::
send_handle( const Handle_Args & args )
{
    bool handled = false ;

    for( Private::children_iterator i =
             m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
#if defined(ESVE_DIAGNOSTIC)

        diagnostic::header("handle", *this, *i) ;

#if defined(ESVE_DEMANGLE)
        int status = 0 ;
        diagnostic::pair("args",
                         abi::__cxa_demangle(typeid(args).name(),
                                             0,
                                             0,
                                             &status)) ;
#else
        diagnostic::pair("args",
                         typeid(args).name()) ;

#endif // defined(ESVE_DEMANGLE)

        args.diagnostic() ;

#endif // defined(ESVE_DIAGNOSTIC)

        handled |= Handle_Receiver::Private::call_handle(*i, args) ;
    }

    return handled ;
}
  
void
Handle_Sender::
add( message::Handle_Receiver & a )
{
    m->add_child(a.handle_receiver().m.get()) ;
}

void
Handle_Sender::
remove( message::Handle_Receiver & a )
{
    m->remove_child(a.handle_receiver().m.get()) ;
}

void
Handle_Sender::
remove_all()
{
    m->remove_children() ;
}

}}} // namespace esve::message::impl
