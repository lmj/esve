
#ifndef esve_message_impl_Compute_Receiver_hxx
#define esve_message_impl_Compute_Receiver_hxx

#include <esve/message/Compute_Receiver.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Compute_Receiver esve/message/impl/Compute_Receiver.hxx
/// @brief Implements Compute_Receiver.
///

class Compute_Receiver
    : virtual public message::Compute_Receiver
{
public:
    Compute_Receiver() ;

    impl::Compute_Receiver & compute_receiver() ;

protected:
    ~Compute_Receiver() ;

private:
    Compute_Receiver( const Compute_Receiver & ) ;
    Compute_Receiver & operator=( const Compute_Receiver & ) ;

    // Coupled implementation with Compute_Sender (mutual linking).
    friend class Compute_Sender ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

