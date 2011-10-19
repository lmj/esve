
#ifndef esve_message_impl_Handle_Receiver_hxx
#define esve_message_impl_Handle_Receiver_hxx

#include <esve/message/Handle_Receiver.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Handle_Receiver esve/message/impl/Handle_Receiver.hxx
/// @brief Implements Handle_Receiver.
///

class Handle_Receiver
    : virtual public message::Handle_Receiver
{
public:
    Handle_Receiver() ;

    impl::Handle_Receiver & handle_receiver() ;

protected:
    ~Handle_Receiver() ;

private:
    Handle_Receiver( const Handle_Receiver & ) ;
    Handle_Receiver & operator=( const Handle_Receiver & ) ;

    // Coupled implementation with Handle_Sender (mutual linking).
    friend class Handle_Sender ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

