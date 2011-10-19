
#ifndef esve_components_dimn_Supermouse_Handler_hxx
#define esve_components_dimn_Supermouse_Handler_hxx

#include <esve/components/dimn/Supermouse.hxx>
#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace components { namespace dimn {

///
/// @class Supermouse_Handler esve/components/dimn/Supermouse_Handler.hxx
/// @brief Receive handle_supermouse_*() messages.
///
/// @see Supermouse_Emitter 
///

class Supermouse_Handler
    : virtual public kernel::Handler
{
public:
    ~Supermouse_Handler() ;

protected:
    Supermouse_Handler() ;

    /// @typedef Supermouse
    /// @brief .
    typedef components::dimn::Supermouse Supermouse ;

    /// @typedef Button
    /// @brief .
    typedef components::dimn::Supermouse::Button Button ;

    /// The supermouse moved.
    virtual bool handle_supermouse_move( const Supermouse & ) = 0 ;

    /// A supermouse button was pushed.
    virtual bool handle_supermouse_push( Button, const Supermouse & ) = 0 ;

    /// A supermouse button was released.
    virtual bool handle_supermouse_release( Button, const Supermouse & ) = 0 ;

    /// The current state of the supermouse.
    const Supermouse & supermouse() const ;

private:
    Supermouse_Handler( const Supermouse_Handler & ) ;
    Supermouse_Handler & operator=( const Supermouse_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::components::dimn

#endif
