
#ifndef esve_message_Update_Sender_hxx
#define esve_message_Update_Sender_hxx

namespace esve { namespace message {

class Update_Receiver ;

///
/// @class Update_Sender esve/message/Update_Sender.hxx
/// @brief update() message sender.
///
/// The update tree.
///
/// At the root of every update tree is a Update_Sender, which passes the
/// update() message to its Update_Receivers.
///
/// The operating system is the original source of the update() message;
/// the user should never call send_update().
///
/// @see Update_Receiver Update_Node
///

class Update_Sender
{
public:
    ///@{
    /// @brief Child update() receivers.
    virtual void add( Update_Receiver & ) = 0 ;
    virtual void remove( Update_Receiver & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    virtual ~Update_Sender() = 0 ;

protected:
    Update_Sender() ;

    /// Send the update() message to all children.
    virtual void send_update() = 0 ;

    /// Send the update() message to all children.
    virtual void send_update( double dt ) = 0 ;

    // Allow subclasses to call send_update() on aggregates.
    static void call_send_update( Update_Sender & ) ;
    static void call_send_update( Update_Sender &, double dt ) ;

private:
    Update_Sender( const Update_Sender & ) ;
    Update_Sender & operator=( const Update_Sender & ) ;
} ;

}} // namespace esve::message

#endif

