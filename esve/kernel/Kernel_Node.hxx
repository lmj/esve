
#ifndef esve_kernel_Kernel_Node_hxx
#define esve_kernel_Kernel_Node_hxx

#include <esve/kernel/Emitter.hxx>
#include <esve/kernel/Handler.hxx>
#include <esve/message/impl/Active_State.hxx>
#include <memory>

namespace esve { namespace message { class Handle_Args ; } }

namespace esve { namespace kernel {

///
/// @class Kernel_Node esve/kernel/Kernel_Node.hxx
/// @brief Relay handle_*() messages.
///
/// This is a higher-level form of message::Handle_Node.  See Emitter
/// and Handler.
///

class Kernel_Node
    : virtual public Emitter,
      virtual public Handler,
      virtual public message::impl::Active_State
{
public:
    Kernel_Node() ;
    ~Kernel_Node() ;

protected:
    // in case someone wants to listen
    virtual bool dispatch_encoded( const message::Handle_Args & ) ;

private:
    Kernel_Node( const Kernel_Node & ) ;
    Kernel_Node & operator=( const Kernel_Node & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

