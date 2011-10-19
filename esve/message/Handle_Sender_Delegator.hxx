
#ifndef esve_message_Handle_Sender_Delegator_hxx
#define esve_message_Handle_Sender_Delegator_hxx

#include <esve/message/Handle_Sender.hxx>
#include <memory>

namespace esve { namespace message {

///
/// @class Handle_Sender_Delegator esve/message/Handle_Sender_Delegator.hxx
/// @brief Delegator for the handle() message sender.
///
/// (Convenience class.)
///

class Handle_Sender_Delegator
    : virtual public Handle_Sender
{
public:
    void add( Handle_Receiver & ) = 0 ;
    void remove( Handle_Receiver & ) = 0 ;
    void remove_all() = 0 ;

    ~Handle_Sender_Delegator() = 0 ;

protected:
    Handle_Sender_Delegator( Handle_Sender & ) ;

    bool send_handle( const Handle_Args & ) = 0 ;

private:
    Handle_Sender_Delegator( const Handle_Sender_Delegator & ) ;
    Handle_Sender_Delegator & operator=( const Handle_Sender_Delegator & ) ;

    Handle_Sender & m ;
} ;

}} // namespace esve::message

#endif

