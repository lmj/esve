
#ifndef esve_message_Tick_Node_hxx
#define esve_message_Tick_Node_hxx

#include <esve/message/Tick_Receiver.hxx>
#include <esve/message/Tick_Sender.hxx>
#include <esve/message/Active_State.hxx>

namespace esve { namespace message {

///
/// @class Tick_Node esve/message/Tick_Node.hxx
/// @brief Relay the tick() message.
///
/// The tick tree.
///
/// The default behavior of a Tick_Node is to relay the tick() message
/// to all children (if active()).
///
/// @see Tick_Sender Tick_Receiver
///

class Tick_Node
    : virtual public Active_State,
      virtual public Tick_Receiver,
      virtual public Tick_Sender
{
public:
    ~Tick_Node() = 0 ;

protected:
    Tick_Node() ;

private:
    Tick_Node( const Tick_Node & ) ;
    Tick_Node & operator=( const Tick_Node & ) ;
} ;

}} // namespace esve::message

#endif

