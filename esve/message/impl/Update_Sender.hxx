
#ifndef esve_message_impl_Update_Sender_hxx
#define esve_message_impl_Update_Sender_hxx

#include <esve/message/Update_Sender.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Update_Sender esve/message/impl/Update_Sender.hxx
/// @brief Implements message::Update_Sender.
///

class Update_Sender
    : virtual public message::Update_Sender
{
public:
    void add( message::Update_Receiver & ) ;
    void remove( message::Update_Receiver & ) ;
    void remove_all() ;

    ~Update_Sender() ;

protected:
    Update_Sender() ;

    void send_update() ;
    void send_update( double dt ) ;

private:
    Update_Sender( const Update_Sender & ) ;
    Update_Sender & operator=( const Update_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

