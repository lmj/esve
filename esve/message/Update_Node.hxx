
#ifndef esve_message_Update_Node_hxx
#define esve_message_Update_Node_hxx

#include <esve/message/Update_Receiver.hxx>
#include <esve/message/Update_Sender.hxx>
#include <esve/message/Active_State.hxx>

namespace esve { namespace message {

///
/// @class Update_Node esve/message/Update_Node.hxx
/// @brief Relay the update() message.
///
/// The update tree.
///
/// The default behavior of a Update_Node is to relay the update() message
/// to all children (if active()).
///
/// @see Update_Sender Update_Receiver
///

class Update_Node
    : virtual public Active_State,
      virtual public Update_Receiver,
      virtual public Update_Sender
{
public:
    ~Update_Node() = 0 ;

protected:
    Update_Node() ;

private:
    Update_Node( const Update_Node & ) ;
    Update_Node & operator=( const Update_Node & ) ;
} ;

}} // namespace esve::message

#endif

