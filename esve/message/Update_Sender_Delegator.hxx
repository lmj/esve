
#ifndef esve_message_Update_Sender_Delegator_hxx
#define esve_message_Update_Sender_Delegator_hxx

#include <esve/message/Update_Sender.hxx>
#include <memory>

namespace esve { namespace message {

///
/// @class Update_Sender_Delegator esve/message/Update_Sender_Delegator.hxx
/// @brief Delegator for the update() message sender.
///
/// (Convenience class.)
///

class Update_Sender_Delegator
    : virtual public Update_Sender
{
public:
    void add( Update_Receiver & ) = 0 ;
    void remove( Update_Receiver & ) = 0 ;
    void remove_all() = 0 ;

    ~Update_Sender_Delegator() = 0 ;

protected:
    Update_Sender_Delegator( Update_Sender & ) ;

    void send_update() = 0 ;
    void send_update( double dt ) = 0 ;

private:
    Update_Sender_Delegator( const Update_Sender_Delegator & ) ;
    Update_Sender_Delegator & operator=( const Update_Sender_Delegator & ) ;

    Update_Sender & m ;
} ;

}} // namespace esve::message

#endif

