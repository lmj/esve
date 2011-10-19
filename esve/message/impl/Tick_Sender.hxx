
#ifndef esve_message_impl_Tick_Sender_hxx
#define esve_message_impl_Tick_Sender_hxx

#include <esve/message/Tick_Sender.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Tick_Sender esve/message/impl/Tick_Sender.hxx
/// @brief Implements message::Tick_Sender.
///

class Tick_Sender
    : virtual public message::Tick_Sender
{
public:
    void add( message::Tick_Receiver & ) ;
    void remove( message::Tick_Receiver & ) ;
    void remove_all() ;

    ~Tick_Sender() ;

protected:
    Tick_Sender() ;

    void send_tick() ;

private:
    Tick_Sender( const Tick_Sender & ) ;
    Tick_Sender & operator=( const Tick_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

