
#ifndef esve_kernel_Sync_Update_Sender_hxx
#define esve_kernel_Sync_Update_Sender_hxx

#include <esve/message/impl/Tick_Receiver.hxx>
#include <esve/message/impl/Update_Sender.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Sync_Update_Sender esve/kernel/Sync_Update_Sender.hxx
/// @brief The update tree.
///

class Sync_Update_Sender
    : virtual public message::impl::Tick_Receiver,
      public message::impl::Update_Sender
{
public:
    Sync_Update_Sender() ;

    /// Reset the dt interval to zero.  Useful after waking up.
    void reset() ;

    ~Sync_Update_Sender() ;

protected:
    void tick() ;

private:
    Sync_Update_Sender( const Sync_Update_Sender & ) ;
    Sync_Update_Sender & operator=( const Sync_Update_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

