
#ifndef esve_components_dimn_Supermouse_Motion_Handler_hxx
#define esve_components_dimn_Supermouse_Motion_Handler_hxx

#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/components/dimn/Inertial_Motion_Handler.hxx>
#include <esve/components/dimn/Supermouse_Handler.hxx>
#include <esve/types/pure.hxx>
#include <memory>

namespace esve { namespace components { namespace dimn {

///
/// @class Supermouse_Motion_Handler esve/components/dimn/Supermouse_Motion_Handler.hxx
/// @brief Common base class for motion input.
///
/// The purpose of this class is to make consistent measure of input
/// velocity and acceleration, accounting for boundary conditions on
/// button drags.
///

class Supermouse_Motion_Handler
    : virtual public Inertial_Motion_Handler,
      public components::dimn::Motion_Handler,
      public Supermouse_Handler
{
public:
    types::real sensitivity() const ;
    void sensitivity( types::real ) ;

    ~Supermouse_Motion_Handler() ;

protected:
    // rotation units
    static const types::real RADIANS_PER_PIXEL ;

    // in milliradians per pixel
    static const types::real DEFAULT_SENSITIVITY ;

    // Upon button release, if less than this amount of time has
    // passed (in seconds) since the last drag, then start motion.
    static const types::real MOTION_TRIGGER_TIME ;

    Supermouse_Motion_Handler() ;

    /// Position.
    const types::pure & u() const ;

    /// Velocity, units per second.
    const types::pure & du_dt() const ;

    /// Acceleration, units per second^2.
    const types::pure & d2u_dt2() const ;

    /// Drag velocity with this button, units per second.
    const types::pure & du_dt( Button b ) const ;

    /// Drag acceleration with this button, units per second^2.
    const types::pure & d2u_dt2( Button b ) const ;

    bool handle_supermouse_move( const Supermouse & ) ;
    bool handle_supermouse_push( Button,
                                 const Supermouse & ) ;
    bool handle_supermouse_release( Button,
                                    const Supermouse & ) ;

    void update() ;
    void update( double dt ) ;

private:
    Supermouse_Motion_Handler( const Supermouse_Motion_Handler & ) ;
    Supermouse_Motion_Handler &
    operator=( const Supermouse_Motion_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::components::dimn

#endif
