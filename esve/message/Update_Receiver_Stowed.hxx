
#ifndef esve_message_Update_Receiver_Stowed_hxx
#define esve_message_Update_Receiver_Stowed_hxx

namespace esve { namespace message {

class Update_Receiver ;

///
/// @class Update_Receiver_Stowed esve/message/Update_Receiver_Stowed.hxx
/// @brief Stowed update() message receiver.
///
/// The update tree.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Update_Receiver
///

class Update_Receiver_Stowed
{
public:
    /// Peek at the update() message receiver.
    virtual message::Update_Receiver & peek_update_receiver() = 0 ;

    virtual ~Update_Receiver_Stowed() = 0 ;

protected:
    Update_Receiver_Stowed() ;

private:
    Update_Receiver_Stowed( const Update_Receiver_Stowed & ) ;
    Update_Receiver_Stowed & operator=( const Update_Receiver_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

