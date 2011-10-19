
#ifndef esve_message_impl_Tick_Node_hxx
#define esve_message_impl_Tick_Node_hxx

#include <esve/message/impl/Tick_Receiver.hxx>
#include <esve/message/impl/Tick_Sender.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <esve/message/Tick_Node.hxx>

namespace esve { namespace message { namespace impl {

///
/// @class Tick_Node esve/message/impl/Tick_Node.hxx
/// @brief Node for relaying the tick() message.
///

class Tick_Node
    : virtual public message::Tick_Node,
      virtual public impl::Active_State,
      virtual public impl::Tick_Receiver,
      virtual public impl::Tick_Sender
{
public:
    Tick_Node() ;

    ~Tick_Node() ;

protected:
    void tick() ;

private:
    Tick_Node( const Tick_Node & ) ;
    Tick_Node & operator=( const Tick_Node & ) ;
} ;

}}} // namespace esve::message::impl

#endif

