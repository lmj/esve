
#ifndef esve_kernel_Simple_Kernel_hxx
#define esve_kernel_Simple_Kernel_hxx

#include <esve/message/Tick_Sender_Stowed.hxx>
#include <memory>

namespace esve { namespace message { class Update_Receiver ; } }

namespace esve { namespace kernel {

class Handler ;
class Emitter ;
class Simple_Kernel_impl ;

///
///
/// @class Simple_Kernel esve/kernel/Simple_Kernel.hxx
/// @brief A simple application driver.
///
/// This is a front-end to Simple_Kernel_impl.
///
/// Note that send_tick() cannot be overridden since the underlying
/// Tick_Sender is an aggregate of Simple_Kernel_impl.
///

class Simple_Kernel
    : virtual public message::Tick_Sender_Stowed
{
public:
    Simple_Kernel() ;

    virtual int takeover() ;

    ///@{
    virtual void add_emitter( kernel::Emitter & ) ;
    virtual void remove_emitter( kernel::Emitter & ) ;
    ///@}

    ///@{
    virtual void add_uncached_emitter( kernel::Emitter & ) ;
    virtual void remove_uncached_emitter( kernel::Emitter & ) ;
    ///@}

    ///@{
    virtual void add_handler( kernel::Handler & ) ;
    virtual void remove_handler( kernel::Handler & ) ;
    virtual void remove_all_handlers() ;
    ///@}

    ///@{
    virtual void add_update_receiver( message::Update_Receiver & ) ;
    virtual void remove_update_receiver( message::Update_Receiver & ) ;
    virtual void remove_all_update_receivers() ;
    ///@}

    ///@{
    virtual void add_driver_handler( kernel::Handler & ) ;
    virtual void remove_driver_handler( kernel::Handler & ) ;
    ///@}

    message::Tick_Sender & peek_tick_sender() ;

    ~Simple_Kernel() ;

private:
    Simple_Kernel( const Simple_Kernel & ) ;
    Simple_Kernel & operator=( const Simple_Kernel & ) ;

    const std::auto_ptr<Simple_Kernel_impl> m ;
} ;

}} // namespace esve::kernel

#endif

