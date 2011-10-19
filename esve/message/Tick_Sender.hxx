
#ifndef esve_message_Tick_Sender_hxx
#define esve_message_Tick_Sender_hxx

namespace esve { namespace message {

class Tick_Receiver ;

///
/// @class Tick_Sender esve/message/Tick_Sender.hxx
/// @brief tick() message sender.
///
/// The tick tree.
///
/// At the root of every tick tree is a Tick_Sender, which passes the
/// tick() message to its Tick_Receivers.
///
/// The operating system is the original source of the tick() message;
/// the user should never call send_tick().
///
/// @see Tick_Receiver Tick_Node
///

class Tick_Sender
{
public:
    ///@{
    /// @brief Child tick() receivers.
    virtual void add( Tick_Receiver & ) = 0 ;
    virtual void remove( Tick_Receiver & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    virtual ~Tick_Sender() = 0 ;

protected:
    Tick_Sender() ;

    /// Send the tick() message to all children.
    virtual void send_tick() = 0 ;

    // Allow subclasses to call send_tick() on aggregates.
    static void call_send_tick( Tick_Sender & ) ;

private:
    Tick_Sender( const Tick_Sender & ) ;
    Tick_Sender & operator=( const Tick_Sender & ) ;
} ;

}} // namespace esve::message

#endif

