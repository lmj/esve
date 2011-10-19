
#ifndef esve_message_Compute_Sender_Delegator_hxx
#define esve_message_Compute_Sender_Delegator_hxx

#include <esve/message/Compute_Sender.hxx>
#include <memory>

namespace esve { namespace message {

///
/// @class Compute_Sender_Delegator esve/message/Compute_Sender_Delegator.hxx
/// @brief Delegator for the compute() message sender.
///
/// (Convenience class.)
///

class Compute_Sender_Delegator
    : virtual public Compute_Sender
{
public:
    void add( Compute_Receiver & ) = 0 ;
    void remove( Compute_Receiver & ) = 0 ;
    void remove_all() = 0 ;

    ~Compute_Sender_Delegator() = 0 ;

protected:
    Compute_Sender_Delegator( Compute_Sender & ) ;

    void send_compute() = 0 ;

private:
    Compute_Sender_Delegator( const Compute_Sender_Delegator & ) ;
    Compute_Sender_Delegator & operator=( const Compute_Sender_Delegator & ) ;

    Compute_Sender & m ;
} ;

}} // namespace esve::message

#endif

