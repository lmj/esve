
#ifndef esve_message_impl_Compute_Node_hxx
#define esve_message_impl_Compute_Node_hxx

#include <esve/message/impl/Compute_Receiver.hxx>
#include <esve/message/impl/Compute_Sender.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <esve/message/Compute_Node.hxx>

namespace esve { namespace message { namespace impl {

///
/// @class Compute_Node esve/message/impl/Compute_Node.hxx
/// @brief Node for relaying the compute() message.
///

class Compute_Node
    : virtual public message::Compute_Node,
      virtual public impl::Active_State,
      virtual public impl::Compute_Receiver,
      virtual public impl::Compute_Sender
{
public:
    Compute_Node() ;

    ~Compute_Node() ;

protected:
    void compute() ;

private:
    Compute_Node( const Compute_Node & ) ;
    Compute_Node & operator=( const Compute_Node & ) ;
} ;

}}} // namespace esve::message::impl

#endif

