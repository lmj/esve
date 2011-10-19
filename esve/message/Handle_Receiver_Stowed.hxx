
#ifndef esve_message_Handle_Receiver_Stowed_hxx
#define esve_message_Handle_Receiver_Stowed_hxx

namespace esve { namespace message {

class Handle_Receiver ;

///
/// @class Handle_Receiver_Stowed esve/message/Handle_Receiver_Stowed.hxx
/// @brief Stowed handle() message receiver.
///
/// The handle tree.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Handle_Receiver
///

class Handle_Receiver_Stowed
{
public:
    /// Peek at the handle() message receiver.
    virtual message::Handle_Receiver & peek_handle_receiver() = 0 ;

    virtual ~Handle_Receiver_Stowed() = 0 ;

protected:
    Handle_Receiver_Stowed() ;

private:
    Handle_Receiver_Stowed( const Handle_Receiver_Stowed & ) ;
    Handle_Receiver_Stowed & operator=( const Handle_Receiver_Stowed & ) ;
} ;

}} // namespace esve::message

#endif

