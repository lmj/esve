
#include <esve/kernel/Caching_Node.hxx>
#include <esve/message/Handle_Node_Cache.hxx>

namespace esve { namespace kernel {

struct Caching_Node::Private
{
    message::Handle_Node_Cache cache ;

    Private( bool caching )
        : cache(caching) { }
} ;

Caching_Node::
Caching_Node( bool caching )
    : m(new Private(caching))
{
    add_decoder(m->cache) ;
    add_encoder(m->cache) ;
}

Caching_Node::
~Caching_Node()
{
}

bool
Caching_Node::
active() const
{
    return m->cache.active() ;
}

void
Caching_Node::
active( bool a )
{
    m->cache.active(a) ;
}

void
Caching_Node::
start_caching()
{
    m->cache.start_caching() ;
}

bool
Caching_Node::
stop_caching()
{
    return m->cache.stop_caching() ;
}

void
Caching_Node::
discard_cache()
{
    m->cache.discard_cache() ;
}

bool
Caching_Node::
caching() const
{
    return m->cache.caching() ;
}

}} // namespace esve::kernel
