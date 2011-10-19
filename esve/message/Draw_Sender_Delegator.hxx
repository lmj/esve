
#ifndef esve_message_Draw_Sender_Delegator_hxx
#define esve_message_Draw_Sender_Delegator_hxx

#include <esve/message/Draw_Sender.hxx>
#include <memory>

namespace esve { namespace message {

///
/// @class Draw_Sender_Delegator esve/message/Draw_Sender_Delegator.hxx
/// @brief Delegator for the draw() message sender.
///
/// (Convenience class.)
///

class Draw_Sender_Delegator
    : virtual public Draw_Sender
{
public:
    void add( Draw_Receiver & ) = 0 ;
    void remove( Draw_Receiver & ) = 0 ;
    void remove_all() = 0 ;

    ~Draw_Sender_Delegator() = 0 ;

protected:
    Draw_Sender_Delegator( Draw_Sender & ) ;

    void send_draw() = 0 ;
    void send_draw_initialize() = 0 ;

private:
    Draw_Sender_Delegator( const Draw_Sender_Delegator & ) ;
    Draw_Sender_Delegator & operator=( const Draw_Sender_Delegator & ) ;

    Draw_Sender & m ;
} ;

}} // namespace esve::message

#endif

