
#ifndef esve_message_Compute_Sender_hxx
#define esve_message_Compute_Sender_hxx

namespace esve { namespace message {

class Compute_Receiver ;

///
/// @class Compute_Sender esve/message/Compute_Sender.hxx
/// @brief compute() message sender.
///
/// The compute tree.
///
/// At the root of every compute tree is a Compute_Sender, which passes the
/// compute() message to its Compute_Receivers.
///
/// The operating system is the original source of the compute() message;
/// the user should never call send_compute().
///
/// @see Compute_Receiver Compute_Node
///

class Compute_Sender
{
public:
    ///@{
    /// @brief Child compute() receivers.
    virtual void add( Compute_Receiver & ) = 0 ;
    virtual void remove( Compute_Receiver & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    virtual ~Compute_Sender() = 0 ;

protected:
    Compute_Sender() ;

    /// Send the compute() message to all children.
    virtual void send_compute() = 0 ;

    // Allow subclasses to call send_compute() on aggregates.
    static void call_send_compute( Compute_Sender & ) ;

private:
    Compute_Sender( const Compute_Sender & ) ;
    Compute_Sender & operator=( const Compute_Sender & ) ;
} ;

}} // namespace esve::message

#endif

