
#ifndef esve_message_impl_Compute_Sender_hxx
#define esve_message_impl_Compute_Sender_hxx

#include <esve/message/Compute_Sender.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Compute_Sender esve/message/impl/Compute_Sender.hxx
/// @brief Implements message::Compute_Sender.
///

class Compute_Sender
    : virtual public message::Compute_Sender
{
public:
    void add( message::Compute_Receiver & ) ;
    void remove( message::Compute_Receiver & ) ;
    void remove_all() ;

    ~Compute_Sender() ;

protected:
    Compute_Sender() ;

    void send_compute() ;

private:
    Compute_Sender( const Compute_Sender & ) ;
    Compute_Sender & operator=( const Compute_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

