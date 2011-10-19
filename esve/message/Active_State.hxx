
#ifndef esve_message_Active_State_hxx
#define esve_message_Active_State_hxx

namespace esve { namespace message {

///
/// @class Active_State esve/message/Active_State.hxx
/// @brief Active/inactive property of tree nodes.
///
/// When a node is active(), messages are relayed from parents to
/// children.  When active() is false, no messages get through.
///

class Active_State
{
public:
    ///@{
    ///
    /// @brief Whether to pass messages to children.
    ///
    /// When active(), messages are relayed from parents to children.
    /// When active() == false, no messages are relayed.
    ///
    virtual bool active() const = 0 ;
    virtual void active( bool ) = 0 ;
    ///@}

    virtual ~Active_State() = 0 ;

protected:
    Active_State() ;

private:
    Active_State( const Active_State & ) ;
    Active_State & operator=( const Active_State & ) ;
} ;

}} // namespace esve::message

#endif

