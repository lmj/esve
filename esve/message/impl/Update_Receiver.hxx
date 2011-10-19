
#ifndef esve_message_impl_Update_Receiver_hxx
#define esve_message_impl_Update_Receiver_hxx

#include <esve/message/Update_Receiver.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Update_Receiver esve/message/impl/Update_Receiver.hxx
/// @brief Implements Update_Receiver.
///

class Update_Receiver
    : virtual public message::Update_Receiver
{
public:
    Update_Receiver() ;

    impl::Update_Receiver & update_receiver() ;

protected:
    ~Update_Receiver() ;

private:
    Update_Receiver( const Update_Receiver & ) ;
    Update_Receiver & operator=( const Update_Receiver & ) ;

    // Coupled implementation with Update_Sender (mutual linking).
    friend class Update_Sender ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

