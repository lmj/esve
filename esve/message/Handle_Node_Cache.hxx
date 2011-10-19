
#ifndef esve_message_Handle_Node_Cache_hxx
#define esve_message_Handle_Node_Cache_hxx

#include <esve/message/impl/Handle_Node.hxx>
#include <memory>

namespace esve { namespace message {

class Handle_Node_Cache
    : public message::impl::Handle_Node
{
private:
    typedef message::impl::Handle_Node super ;

    Handle_Node_Cache( const Handle_Node_Cache & ) ;
    Handle_Node_Cache & operator=( const Handle_Node_Cache & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
    
public:
    Handle_Node_Cache( bool caching ) ;

    void start_caching() ;
    bool stop_caching() ;
    void discard_cache() ;
    bool caching() const ;
    bool send_handle( const Handle_Args & ) ;

    ~Handle_Node_Cache() ;
} ;

}} // namespace esve::message

#endif

