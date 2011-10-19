
#ifndef esve_message_Tick_Receiver_Stowed_hxx
#define esve_message_Tick_Receiver_Stowed_hxx

namespace esve { namespace message {

class Tick_Receiver ;

///
/// @class Tick_Receiver_Stowed esve/message/Tick_Receiver_Stowed.hxx
/// @brief Stowed tick() message receiver.
///
/// The tick tree.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Tick_Receiver
///

class Tick_Receiver_Stowed
{
public:
    /// Peek at the tick() message receiver.
    virtual message::Tick_Receiver & peek_tick_receiver() = 0 ;

    virtual ~Tick_Receiver_Stowed() = 0 ;

protected:
    Tick_Receiver_Stowed() ;

private:
    Tick_Receiver_Stowed( const Tick_Receiver_Stowed & ) ;
    Tick_Receiver_Stowed & operator=( const Tick_Receiver_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

