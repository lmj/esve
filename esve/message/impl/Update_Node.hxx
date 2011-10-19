
#ifndef esve_message_impl_Update_Node_hxx
#define esve_message_impl_Update_Node_hxx

#include <esve/message/impl/Update_Receiver.hxx>
#include <esve/message/impl/Update_Sender.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <esve/message/Update_Node.hxx>

namespace esve { namespace message { namespace impl {

///
/// @class Update_Node esve/message/impl/Update_Node.hxx
/// @brief Node for relaying the update() message.
///

class Update_Node
    : virtual public message::Update_Node,
      virtual public impl::Active_State,
      virtual public impl::Update_Receiver,
      virtual public impl::Update_Sender
{
public:
    Update_Node() ;

    ~Update_Node() ;

protected:
    void update() ;
    void update( double dt ) ;

private:
    Update_Node( const Update_Node & ) ;
    Update_Node & operator=( const Update_Node & ) ;
} ;

}}} // namespace esve::message::impl

#endif

