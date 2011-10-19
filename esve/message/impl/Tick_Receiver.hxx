
#ifndef esve_message_impl_Tick_Receiver_hxx
#define esve_message_impl_Tick_Receiver_hxx

#include <esve/message/Tick_Receiver.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Tick_Receiver esve/message/impl/Tick_Receiver.hxx
/// @brief Implements Tick_Receiver.
///

class Tick_Receiver
    : virtual public message::Tick_Receiver
{
public:
    Tick_Receiver() ;

    impl::Tick_Receiver & tick_receiver() ;

protected:
    ~Tick_Receiver() ;

private:
    Tick_Receiver( const Tick_Receiver & ) ;
    Tick_Receiver & operator=( const Tick_Receiver & ) ;

    // Coupled implementation with Tick_Sender (mutual linking).
    friend class Tick_Sender ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

