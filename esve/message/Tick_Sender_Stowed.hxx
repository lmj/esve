
#ifndef esve_message_Tick_Sender_Stowed_hxx
#define esve_message_Tick_Sender_Stowed_hxx

namespace esve { namespace message {

class Tick_Sender ;

///
/// @class Tick_Sender_Stowed esve/message/Tick_Sender_Stowed.hxx
/// @brief Stowed tick() message sender.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Tick_Sender
///

class Tick_Sender_Stowed
{
public:
    /// Peek at the tick() message sender.
    virtual message::Tick_Sender & peek_tick_sender() = 0 ;

    virtual ~Tick_Sender_Stowed() = 0 ;

protected:
    Tick_Sender_Stowed() ;

private:
    Tick_Sender_Stowed( const Tick_Sender_Stowed & ) ;
    Tick_Sender_Stowed & operator=( const Tick_Sender_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

