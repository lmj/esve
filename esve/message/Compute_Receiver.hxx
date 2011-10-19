
#ifndef esve_message_Compute_Receiver_hxx
#define esve_message_Compute_Receiver_hxx

namespace esve { namespace message {

namespace impl { class Compute_Receiver ; }

///
/// @class Compute_Receiver esve/message/Compute_Receiver.hxx
/// @brief compute() message receiver.
///
/// The compute tree.
///
/// The operating system is the original source of the compute() message;
/// the user should never call compute() explicitly.
///
/// @see Compute_Sender Compute_Node
///


class Compute_Receiver
{
public:
    virtual ~Compute_Receiver() = 0 ;

    // mandatory implementation
    virtual impl::Compute_Receiver & compute_receiver() = 0 ;

protected:
    Compute_Receiver() ;

    /// Receive the compute() message.
    virtual void compute() = 0 ;

    // Allow subclasses to call compute().
    static void call_compute( Compute_Receiver & ) ;

private:
    Compute_Receiver( const Compute_Receiver & ) ;
    Compute_Receiver & operator=( const Compute_Receiver & ) ;
} ;

}} // namespace esve::message

#endif

