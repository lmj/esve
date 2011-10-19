
#ifndef esve_message_Draw_Sender_hxx
#define esve_message_Draw_Sender_hxx

namespace esve { namespace message {

class Draw_Receiver ;

///
/// @class Draw_Sender esve/message/Draw_Sender.hxx
/// @brief draw() message sender.
///
/// The draw tree.
///
/// At the root of every draw tree is a Draw_Sender, which passes the
/// draw() message to its Draw_Receivers.
///
/// The operating system is the original source of the draw() message;
/// the user should never call send_draw().
///
/// @see Draw_Receiver Draw_Node
///

class Draw_Sender
{
public:
    ///@{
    /// @brief Child draw() receivers.
    virtual void add( Draw_Receiver & ) = 0 ;
    virtual void remove( Draw_Receiver & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    virtual ~Draw_Sender() = 0 ;

protected:
    Draw_Sender() ;

    /// Send the draw() message to all children.
    virtual void send_draw() = 0 ;

    // Allow subclasses to call send_draw() on aggregates.
    static void call_send_draw( Draw_Sender & ) ;

    /// Send the draw_initialize() message to all children.
    virtual void send_draw_initialize() = 0 ;

    // Allow subclasses to call send_draw_initialize() on aggregates.
    static void call_send_draw_initialize( Draw_Sender & ) ;

private:
    Draw_Sender( const Draw_Sender & ) ;
    Draw_Sender & operator=( const Draw_Sender & ) ;
} ;

}} // namespace esve::message

#endif

