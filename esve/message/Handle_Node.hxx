
#ifndef esve_message_Handle_Node_hxx
#define esve_message_Handle_Node_hxx

#include <esve/message/Handle_Receiver.hxx>
#include <esve/message/Handle_Sender.hxx>
#include <esve/message/Active_State.hxx>

namespace esve { namespace message {

///
/// @class Handle_Node esve/message/Handle_Node.hxx
/// @brief Relay the handle() message.
///
/// The handle tree.
///
/// The default behavior of a Handle_Node is to relay the handle() message
/// to all children (if active()).
///
/// @see Handle_Sender Handle_Receiver
///

class Handle_Node
    : virtual public Active_State,
      virtual public Handle_Receiver,
      virtual public Handle_Sender
{
public:
    ~Handle_Node() = 0 ;

protected:
    Handle_Node() ;

private:
    Handle_Node( const Handle_Node & ) ;
    Handle_Node & operator=( const Handle_Node & ) ;
} ;

}} // namespace esve::message

#endif

