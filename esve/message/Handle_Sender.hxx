
#ifndef esve_message_Handle_Sender_hxx
#define esve_message_Handle_Sender_hxx

namespace esve { namespace message {

class Handle_Args ;
class Handle_Receiver ;

///
/// @class Handle_Sender esve/message/Handle_Sender.hxx
/// @brief handle() message sender.
///
/// The handle tree.
///
/// At the root of every handle tree is a Handle_Sender, which passes the
/// handle() message to its Handle_Receivers.
///
/// The operating system is the original source of the handle() message;
/// the user should never call send_handle().
///
/// @see Handle_Receiver Handle_Node
///

class Handle_Sender
{
public:
    ///@{
    /// @brief Child handle() receivers.
    virtual void add( Handle_Receiver & ) = 0 ;
    virtual void remove( Handle_Receiver & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    virtual ~Handle_Sender() = 0 ;

protected:
    Handle_Sender() ;

    /// Send the handle() message to all children.
    virtual bool send_handle( const Handle_Args & ) = 0 ;

    // Allow subclasses to call send_handle() on aggregates.
    static bool call_send_handle( Handle_Sender &,
                                  const Handle_Args &  ) ;

private:
    Handle_Sender( const Handle_Sender & ) ;
    Handle_Sender & operator=( const Handle_Sender & ) ;
} ;

}} // namespace esve::message

#endif

