
#ifndef esve_message_Draw_Receiver_Stowed_hxx
#define esve_message_Draw_Receiver_Stowed_hxx

namespace esve { namespace message {

class Draw_Receiver ;

///
/// @class Draw_Receiver_Stowed esve/message/Draw_Receiver_Stowed.hxx
/// @brief Stowed draw() message receiver.
///
/// The draw tree.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Draw_Receiver
///

class Draw_Receiver_Stowed
{
public:
    /// Peek at the draw() message receiver.
    virtual message::Draw_Receiver & peek_draw_receiver() = 0 ;

    virtual ~Draw_Receiver_Stowed() = 0 ;

protected:
    Draw_Receiver_Stowed() ;

private:
    Draw_Receiver_Stowed( const Draw_Receiver_Stowed & ) ;
    Draw_Receiver_Stowed & operator=( const Draw_Receiver_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

