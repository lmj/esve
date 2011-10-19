
#ifndef esve_message_Tick_Sender_Delegator_hxx
#define esve_message_Tick_Sender_Delegator_hxx

#include <esve/message/Tick_Sender.hxx>
#include <memory>

namespace esve { namespace message {

///
/// @class Tick_Sender_Delegator esve/message/Tick_Sender_Delegator.hxx
/// @brief Delegator for the tick() message sender.
///
/// (Convenience class.)
///

class Tick_Sender_Delegator
    : virtual public Tick_Sender
{
public:
    void add( Tick_Receiver & ) = 0 ;
    void remove( Tick_Receiver & ) = 0 ;
    void remove_all() = 0 ;

    ~Tick_Sender_Delegator() = 0 ;

protected:
    Tick_Sender_Delegator( Tick_Sender & ) ;

    void send_tick() = 0 ;

private:
    Tick_Sender_Delegator( const Tick_Sender_Delegator & ) ;
    Tick_Sender_Delegator & operator=( const Tick_Sender_Delegator & ) ;

    Tick_Sender & m ;
} ;

}} // namespace esve::message

#endif

