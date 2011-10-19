
#ifndef esve_components_dim3_Oriented_Rotation_Handler_hxx
#define esve_components_dim3_Oriented_Rotation_Handler_hxx

#include <esve/components/dimn/Differential_Motion_Handler.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace components { namespace dim3 {

///
/// @class Oriented_Rotation_Handler esve/components/dim3/Oriented_Rotation_Handler.hxx
/// @brief Rotations around a frame's z-axis.
///

class Oriented_Rotation_Handler
    : public components::dimn::Differential_Motion_Handler
             <
                 engine::dim3::Transform
             >
{
private:
    typedef
    components::dimn::Differential_Motion_Handler
             <
                 engine::dim3::Transform
             >
    super ;

    Oriented_Rotation_Handler( const Oriented_Rotation_Handler & ) ;
    Oriented_Rotation_Handler &
    operator=( const Oriented_Rotation_Handler & ) ;

    // axis differential angle
    types::real m_dtheta_dt ;

    // elevation differential angle
    types::real m_dphi_dt ;

    // record whether we are upside down when the mouse push occurs
    types::real m_sign ;

public:
    /// Constructor.  Give the transform on which this handler operates.
    explicit Oriented_Rotation_Handler( engine::dim3::Transform & ) ;

    ~Oriented_Rotation_Handler() ;

protected:
    ///@{
    /// @brief Base class hook.
    void create_motion( Button, const types::pure & du_dt ) ;
    engine::dim3::Transform
    differential_motion( Button button, types::real dt ) ;
    void stop_motion( Button ) ;
    bool has_motion( Button ) ;
    ///@}

    // base override
    bool handle_supermouse_push( Button, const Supermouse & ) ;
} ;

}}} // namespace esve::components::dim3

#endif

