
#ifndef esve_message_Draw_Receiver_hxx
#define esve_message_Draw_Receiver_hxx

namespace esve { namespace message {

namespace impl { class Draw_Receiver ; }

///
/// @class Draw_Receiver esve/message/Draw_Receiver.hxx
/// @brief draw() message receiver.
///
/// The draw tree.
///
/// The operating system is the original source of the draw() message;
/// the user should never call draw() explicitly.
///
/// @see Draw_Sender Draw_Node
///


class Draw_Receiver
{
public:
    virtual ~Draw_Receiver() = 0 ;

    // mandatory implementation
    virtual impl::Draw_Receiver & draw_receiver() = 0 ;

protected:
    Draw_Receiver() ;

    /// Receive the draw() message.
    virtual void draw() = 0 ;

    // Allow subclasses to call draw().
    static void call_draw( Draw_Receiver & ) ;

    /// Receive the draw_initialize() message.
    virtual void draw_initialize() ;

    // Allow subclasses to call draw_initialize().
    static void call_draw_initialize( Draw_Receiver & ) ;

private:
    Draw_Receiver( const Draw_Receiver & ) ;
    Draw_Receiver & operator=( const Draw_Receiver & ) ;
} ;

}} // namespace esve::message

#endif

