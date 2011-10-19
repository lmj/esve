
#ifndef esve_message_Handle_Receiver_hxx
#define esve_message_Handle_Receiver_hxx

namespace esve { namespace message {

namespace impl { class Handle_Receiver ; }

class Handle_Args ;

///
/// @class Handle_Receiver esve/message/Handle_Receiver.hxx
/// @brief handle() message receiver.
///
/// The handle tree.
///
/// The operating system is the original source of the handle() message;
/// the user should never call handle() explicitly.
///
/// @see Handle_Sender Handle_Node
///


class Handle_Receiver
{
public:
    virtual ~Handle_Receiver() = 0 ;

    // mandatory implementation
    virtual impl::Handle_Receiver & handle_receiver() = 0 ;

protected:
    Handle_Receiver() ;

    /// Receive the handle() message.
    virtual bool handle( const Handle_Args & ) = 0 ;

    // Allow subclasses to call handle().
    static bool call_handle( Handle_Receiver &,
                             const Handle_Args & ) ;

private:
    Handle_Receiver( const Handle_Receiver & ) ;
    Handle_Receiver & operator=( const Handle_Receiver & ) ;
} ;

}} // namespace esve::message

#endif

