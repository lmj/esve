
#ifndef esve_message_Handle_Sender_Stowed_hxx
#define esve_message_Handle_Sender_Stowed_hxx

namespace esve { namespace message {

class Handle_Sender ;

///
/// @class Handle_Sender_Stowed esve/message/Handle_Sender_Stowed.hxx
/// @brief Stowed handle() message sender.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Handle_Sender
///

class Handle_Sender_Stowed
{
public:
    /// Peek at the handle() message sender.
    virtual message::Handle_Sender & peek_handle_sender() = 0 ;

    virtual ~Handle_Sender_Stowed() = 0 ;

protected:
    Handle_Sender_Stowed() ;

private:
    Handle_Sender_Stowed( const Handle_Sender_Stowed & ) ;
    Handle_Sender_Stowed & operator=( const Handle_Sender_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

