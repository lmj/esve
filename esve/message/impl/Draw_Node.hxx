
#ifndef esve_message_impl_Draw_Node_hxx
#define esve_message_impl_Draw_Node_hxx

#include <esve/message/impl/Draw_Receiver.hxx>
#include <esve/message/impl/Draw_Sender.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <esve/message/Draw_Node.hxx>

namespace esve { namespace message { namespace impl {

///
/// @class Draw_Node esve/message/impl/Draw_Node.hxx
/// @brief Node for relaying the draw() message.
///

class Draw_Node
    : virtual public message::Draw_Node,
      virtual public impl::Active_State,
      virtual public impl::Draw_Receiver,
      virtual public impl::Draw_Sender
{
public:
    Draw_Node() ;

    ~Draw_Node() ;

protected:
    void draw() ;
    void draw_initialize() ;

private:
    Draw_Node( const Draw_Node & ) ;
    Draw_Node & operator=( const Draw_Node & ) ;
} ;

}}} // namespace esve::message::impl

#endif

