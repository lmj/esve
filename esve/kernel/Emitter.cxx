
#include <esve/kernel/Emitter.hxx>
#include <esve/kernel/Handler.hxx>
#include <esve/message/impl/Handle_Node.hxx>
#include <vector>
#include <cassert>

namespace esve { namespace kernel {

struct Emitter::Private
{
    // named for nicer rtti logs
    struct From_Encoders
        : public message::impl::Handle_Node
    {
    } ;

    From_Encoders from_encoders ;

    Private()
        : from_encoders() { }
} ;

struct Handler::Private
{
    // named for nicer rtti logs
    struct To_Decoders
        : public message::impl::Handle_Node
    {
    } ;

    To_Decoders to_decoders ;

    Private()
        : to_decoders() { }
} ;

/////////////////////////////////////////////////////////////

Emitter::
Emitter()
    : m(new Private())
{
}

Emitter::
~Emitter()
{
}

void
Emitter::
add_encoder( message::Handle_Sender & a )
{
    a.add(m->from_encoders) ;
}

void
Emitter::
add_handler( Handler & a )
{
    m->from_encoders.add(a.m->to_decoders) ;
}

void
Emitter::
remove_handler( Handler & a )
{
    m->from_encoders.remove(a.m->to_decoders) ;
}

void
Emitter::
remove_all_handlers()
{
    m->from_encoders.remove_all() ;
}

//////////////////////////////////////////////////////////////////

Handler::
Handler()
    : m(new Private())
{
}

Handler::
~Handler()
{
}

void
Handler::
add_decoder( message::Handle_Receiver & a )
{
    m->to_decoders.add(a) ;
}

}} // namespace esve::kernel
