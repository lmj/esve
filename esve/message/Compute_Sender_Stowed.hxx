
#ifndef esve_message_Compute_Sender_Stowed_hxx
#define esve_message_Compute_Sender_Stowed_hxx

namespace esve { namespace message {

class Compute_Sender ;

///
/// @class Compute_Sender_Stowed esve/message/Compute_Sender_Stowed.hxx
/// @brief Stowed compute() message sender.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Compute_Sender
///

class Compute_Sender_Stowed
{
public:
    /// Peek at the compute() message sender.
    virtual message::Compute_Sender & peek_compute_sender() = 0 ;

    virtual ~Compute_Sender_Stowed() = 0 ;

protected:
    Compute_Sender_Stowed() ;

private:
    Compute_Sender_Stowed( const Compute_Sender_Stowed & ) ;
    Compute_Sender_Stowed & operator=( const Compute_Sender_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

