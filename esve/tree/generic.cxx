 
#include <esve/tree/generic.hxx>
#include <esve/util/MP_Tree.hxx>

#include <iostream>

namespace esve { namespace tree { namespace generic {

///////////////////////////////////////////////////////////

struct Handler::Private
    :
    public util::MP_Tree_Child<Emitter*, Handler*>
{
    typedef
    util::MP_Tree_Child<Emitter*, Handler*>
    super ;

    Private( Handler & a )
        :
        super(&a)
    {
    }
} ;

struct Emitter::Private
    :
    public util::MP_Tree_Parent<Emitter*, Handler*>
{
    typedef
    util::MP_Tree_Parent<Emitter*, Handler*>
    super ;

    Private( Emitter & a )
        :
        super(&a)
    {
    }
} ;

///////////////////////////////////////////////////////////

Handler::
Handler()
    :
    m(new Private(*this))
{
}

Handler::
~Handler()
{
}

void
Handler::
remove_parents()
{
    m->remove_parents() ;
}

///////////////////////////////////////////////////////////

Emitter::
Emitter()
    :
    m(new Private(*this))
{
}

Emitter::
~Emitter()
{
}

bool
Emitter::
emit( void* message )
{
    bool handled = false ;
    
    for( Private::children_iterator i = m->children_begin() ;
         i != m->children_end() ;
         ++i )
    {
        handled |= i->handle(message) ;
    }

    return handled ;
}

void
Emitter::
add_child( Handler & a )
{
    m->add_child(a.m.get()) ;
}

void
Emitter::
remove_child( Handler & a )
{
    m->remove_child(a.m.get()) ;
}

void
Emitter::
remove_children()
{
    m->remove_children() ;
}

}}} // namespace esve::tree::generic

