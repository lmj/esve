
#ifndef esve_message_Update_Sender_Stowed_hxx
#define esve_message_Update_Sender_Stowed_hxx

namespace esve { namespace message {

class Update_Sender ;

///
/// @class Update_Sender_Stowed esve/message/Update_Sender_Stowed.hxx
/// @brief Stowed update() message sender.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Update_Sender
///

class Update_Sender_Stowed
{
public:
    /// Peek at the update() message sender.
    virtual message::Update_Sender & peek_update_sender() = 0 ;

    virtual ~Update_Sender_Stowed() = 0 ;

protected:
    Update_Sender_Stowed() ;

private:
    Update_Sender_Stowed( const Update_Sender_Stowed & ) ;
    Update_Sender_Stowed & operator=( const Update_Sender_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

