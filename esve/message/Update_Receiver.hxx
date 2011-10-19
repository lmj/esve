
#ifndef esve_message_Update_Receiver_hxx
#define esve_message_Update_Receiver_hxx

namespace esve { namespace message {

namespace impl { class Update_Receiver ; }

///
/// @class Update_Receiver esve/message/Update_Receiver.hxx
/// @brief update() message receiver.
///
/// The update tree.
///
/// The operating system is the original source of the update() message;
/// the user should never call update() explicitly.
///
/// @see Update_Sender Update_Node
///


class Update_Receiver
{
public:
    virtual ~Update_Receiver() = 0 ;

    // mandatory implementation
    virtual impl::Update_Receiver & update_receiver() = 0 ;

protected:
    Update_Receiver() ;

    /// Receive the update() message.
    virtual void update() = 0 ;

    /// Receive the update() message.
    virtual void update( double dt ) = 0 ;

    // Allow subclasses to call update().
    static void call_update( Update_Receiver & ) ;
    static void call_update( Update_Receiver &, double dt ) ;

private:
    Update_Receiver( const Update_Receiver & ) ;
    Update_Receiver & operator=( const Update_Receiver & ) ;
} ;

}} // namespace esve::message

#endif

