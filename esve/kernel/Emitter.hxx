
#ifndef esve_kernel_Emitter_hxx
#define esve_kernel_Emitter_hxx

#include <memory>

namespace esve { namespace message { class Handle_Sender ; } }

namespace esve { namespace kernel {

class Handler ;

///
/// @class Emitter esve/kernel/Emitter.hxx
/// @brief Send handle_*() messages.
///
/// Emitter and Handler are on a higher level of meaning than
/// message::Handle_Sender and message::Handle_Receiver.  Emitter and
/// Handler present a facade in which it seems as though whole
/// messages like handle_mouse_move() are being sent and received,
/// when actually it is the raw handle() message being encoded by an
/// Emitter and then decoded by a Handler (for example
/// ui::base::Mouse_Emitter and ui::base::Mouse_Handler).
///

class Emitter
{
public:
    ///@{
    /// @brief Child handlers.
    virtual void add_handler( Handler & ) ;
    virtual void remove_handler( Handler & ) ;
    virtual void remove_all_handlers() ;
    ///@}

    virtual ~Emitter() ;

    //
    // After creating a Handle_Sender which encodes data into a
    // Handle_Args instance, call this function to point it at the
    // common encoder node.
    //
    // You almost certainly want to call this in the constructor.
    //
    void add_encoder( message::Handle_Sender & ) ;

protected:
    Emitter() ;
    
private:
    Emitter( const Emitter & ) ;
    Emitter & operator=( const Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif
