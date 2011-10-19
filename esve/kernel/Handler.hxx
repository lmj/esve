
#ifndef esve_kernel_Handler_hxx
#define esve_kernel_Handler_hxx

#include <memory>

namespace esve { namespace message { class Handle_Receiver ; } }

namespace esve { namespace kernel {

///
/// @class Handler esve/kernel/Handler.hxx
/// @brief Receive handle_*() messages.
///
/// Emitter and Handler are on a higher level of meaning than
/// message::Handle_Sender and message::Handle_Receiver.  Emitter and
/// Handler present a facade in which it seems as though whole
/// messages like handle_mouse_move() are being sent and received,
/// when actually it is the raw handle() message being encoded by an
/// Emitter and then decoded by a Handler (for example
/// ui::base::Mouse_Emitter and ui::base::Mouse_Handler).
///

class Handler
{
public:
    virtual ~Handler() ;

protected:
    Handler() ;
    
    //
    // After creating a Handle_Receiver which decodes data from a
    // Handle_Args instance, call this function to receive data from
    // the common decoder node.
    //
    // You almost certainly want to call this in the constructor.
    //
    void add_decoder( message::Handle_Receiver & ) ;

private:
    Handler( const Handler & ) ;
    Handler & operator=( const Handler & ) ;

    // Coupled implementation with Handler (mutual linking)
    friend class Emitter ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif
