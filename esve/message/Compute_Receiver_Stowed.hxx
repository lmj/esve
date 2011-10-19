
#ifndef esve_message_Compute_Receiver_Stowed_hxx
#define esve_message_Compute_Receiver_Stowed_hxx

namespace esve { namespace message {

class Compute_Receiver ;

///
/// @class Compute_Receiver_Stowed esve/message/Compute_Receiver_Stowed.hxx
/// @brief Stowed compute() message receiver.
///
/// The compute tree.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Compute_Receiver
///

class Compute_Receiver_Stowed
{
public:
    /// Peek at the compute() message receiver.
    virtual message::Compute_Receiver & peek_compute_receiver() = 0 ;

    virtual ~Compute_Receiver_Stowed() = 0 ;

protected:
    Compute_Receiver_Stowed() ;

private:
    Compute_Receiver_Stowed( const Compute_Receiver_Stowed & ) ;
    Compute_Receiver_Stowed & operator=( const Compute_Receiver_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

