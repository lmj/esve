
#ifndef esve_message_impl_Active_State_hxx
#define esve_message_impl_Active_State_hxx

#include <esve/message/Active_State.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Active_State esve/message/impl/Active_State.hxx
/// @brief Implements message::Active_State.
///

class Active_State
    : virtual public message::Active_State
{
public:
    Active_State() ;

    bool active() const ;
    void active( bool ) ;

    ~Active_State() ;

private:
    Active_State( const Active_State & ) ;
    Active_State & operator=( const Active_State & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

