
#include <esve/message/Handle_Node_Cache.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/util/auto_ptr_list.hxx>

namespace esve { namespace message {

struct Handle_Node_Cache::Private
{
    typedef
    util::auto_ptr_list<Handle_Args>
    Cache ;

    bool caching ;

    Cache cache ;

    Private( bool caching_ )
        : caching(caching_),
          cache() { }
} ;

Handle_Node_Cache::
Handle_Node_Cache( bool caching )
    : m(new Private(caching))
{
}

Handle_Node_Cache::
~Handle_Node_Cache()
{
    stop_caching() ;
}

void
Handle_Node_Cache::
start_caching()
{
    m->caching = true ;
}

bool
Handle_Node_Cache::
stop_caching()
{
    bool handled = false ;

    m->caching = false ;

    while( m->cache.size() != 0 )
    {
        handled |= message::impl::Handle_Sender::
            send_handle(*m->cache.release_front()) ;
    }

    return handled ;
}

bool
Handle_Node_Cache::
caching() const
{
    return m->caching ;
}

void
Handle_Node_Cache::
discard_cache()
{
    m->cache.clear() ;
}

bool
Handle_Node_Cache::
send_handle( const message::Handle_Args & args )
{
    bool handled = false ;

    if( m->caching )
    {
        m->cache.push_back(args.clone()) ;
    }
    else
    {
        handled = super::send_handle(args) ;
    }

    return handled ;
}

}} // namespace esve::message
