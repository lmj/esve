
#ifndef esve_message_impl_Handle_Sender_hxx
#define esve_message_impl_Handle_Sender_hxx

#include <esve/message/Handle_Sender.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Handle_Sender esve/message/impl/Handle_Sender.hxx
/// @brief Implements message::Handle_Sender.
///

class Handle_Sender
    : virtual public message::Handle_Sender
{
public:
    void add( message::Handle_Receiver & ) ;
    void remove( message::Handle_Receiver & ) ;
    void remove_all() ;

    ~Handle_Sender() ;

protected:
    Handle_Sender() ;

    bool send_handle( const Handle_Args & ) ;

private:
    Handle_Sender( const Handle_Sender & ) ;
    Handle_Sender & operator=( const Handle_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

