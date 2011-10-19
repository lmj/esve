
#ifndef esve_message_Draw_Sender_Stowed_hxx
#define esve_message_Draw_Sender_Stowed_hxx

namespace esve { namespace message {

class Draw_Sender ;

///
/// @class Draw_Sender_Stowed esve/message/Draw_Sender_Stowed.hxx
/// @brief Stowed draw() message sender.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Draw_Sender
///

class Draw_Sender_Stowed
{
public:
    /// Peek at the draw() message sender.
    virtual message::Draw_Sender & peek_draw_sender() = 0 ;

    virtual ~Draw_Sender_Stowed() = 0 ;

protected:
    Draw_Sender_Stowed() ;

private:
    Draw_Sender_Stowed( const Draw_Sender_Stowed & ) ;
    Draw_Sender_Stowed & operator=( const Draw_Sender_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

