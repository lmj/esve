
#ifndef esve_message_Compute_Node_hxx
#define esve_message_Compute_Node_hxx

#include <esve/message/Compute_Receiver.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/message/Active_State.hxx>

namespace esve { namespace message {

///
/// @class Compute_Node esve/message/Compute_Node.hxx
/// @brief Relay the compute() message.
///
/// The compute tree.
///
/// The default behavior of a Compute_Node is to relay the compute() message
/// to all children (if active()).
///
/// @see Compute_Sender Compute_Receiver
///

class Compute_Node
    : virtual public Active_State,
      virtual public Compute_Receiver,
      virtual public Compute_Sender
{
public:
    ~Compute_Node() = 0 ;

protected:
    Compute_Node() ;

private:
    Compute_Node( const Compute_Node & ) ;
    Compute_Node & operator=( const Compute_Node & ) ;
} ;

}} // namespace esve::message

#endif

