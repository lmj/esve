
#ifndef esve_message_impl_Handle_Node_hxx
#define esve_message_impl_Handle_Node_hxx

#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <esve/message/Handle_Node.hxx>

namespace esve { namespace message { namespace impl {

///
/// @class Handle_Node esve/message/impl/Handle_Node.hxx
/// @brief Node for relaying the handle() message.
///

class Handle_Node
    : virtual public message::Handle_Node,
      virtual public impl::Active_State,
      virtual public impl::Handle_Receiver,
      virtual public impl::Handle_Sender
{
public:
    Handle_Node() ;

    ~Handle_Node() ;

protected:
    bool handle( const Handle_Args & ) ;

private:
    Handle_Node( const Handle_Node & ) ;
    Handle_Node & operator=( const Handle_Node & ) ;
} ;

}}} // namespace esve::message::impl

#endif

