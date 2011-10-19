
#ifndef esve_message_Draw_Node_hxx
#define esve_message_Draw_Node_hxx

#include <esve/message/Draw_Receiver.hxx>
#include <esve/message/Draw_Sender.hxx>
#include <esve/message/Active_State.hxx>

namespace esve { namespace message {

///
/// @class Draw_Node esve/message/Draw_Node.hxx
/// @brief Relay the draw() message.
///
/// The draw tree.
///
/// The default behavior of a Draw_Node is to relay the draw() message
/// to all children (if active()).
///
/// @see Draw_Sender Draw_Receiver
///

class Draw_Node
    : virtual public Active_State,
      virtual public Draw_Receiver,
      virtual public Draw_Sender
{
public:
    ~Draw_Node() = 0 ;

protected:
    Draw_Node() ;

private:
    Draw_Node( const Draw_Node & ) ;
    Draw_Node & operator=( const Draw_Node & ) ;
} ;

}} // namespace esve::message

#endif

