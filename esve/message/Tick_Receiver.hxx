
#ifndef esve_message_Tick_Receiver_hxx
#define esve_message_Tick_Receiver_hxx

namespace esve { namespace message {

namespace impl { class Tick_Receiver ; }

///
/// @class Tick_Receiver esve/message/Tick_Receiver.hxx
/// @brief tick() message receiver.
///
/// The tick tree.
///
/// The operating system is the original source of the tick() message;
/// the user should never call tick() explicitly.
///
/// @see Tick_Sender Tick_Node
///


class Tick_Receiver
{
public:
    virtual ~Tick_Receiver() = 0 ;

    // mandatory implementation
    virtual impl::Tick_Receiver & tick_receiver() = 0 ;

protected:
    Tick_Receiver() ;

    /// Receive the tick() message.
    virtual void tick() = 0 ;

    // Allow subclasses to call tick().
    static void call_tick( Tick_Receiver & ) ;

private:
    Tick_Receiver( const Tick_Receiver & ) ;
    Tick_Receiver & operator=( const Tick_Receiver & ) ;
} ;

}} // namespace esve::message

#endif

