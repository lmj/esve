
#ifndef esve_components_dim3_Rotation_Handler_hxx
#define esve_components_dim3_Rotation_Handler_hxx

#include <esve/components/dimn/Differential_Motion_Handler.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace components { namespace dim3 {

///
/// @class Rotation_Handler esve/components/dim3/Rotation_Handler.hxx
/// @brief Rotations via the "glass ball" model.
///

class Rotation_Handler
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

    struct m_Motion_Data
    {
        // axis
        types::pure u ;

        // differential angle
        types::real dtheta_dt ;

        m_Motion_Data() ;
    } ;

    Rotation_Handler( const Rotation_Handler & ) ;
    Rotation_Handler & operator=( const Rotation_Handler & ) ;

    m_Motion_Data m_motion_data[Supermouse::NUM_BUTTONS] ;

public:
    /// Constructor.  Give the transform on which this handler operates.
    explicit Rotation_Handler( engine::dim3::Transform & ) ;

    ~Rotation_Handler() ;

protected:
    ///@{
    /// @brief Base class hook.
    void create_motion( Button, const types::pure & du_dt ) ;
    engine::dim3::Transform
    differential_motion( Button button, types::real dt ) ;
    void stop_motion( Button ) ;
    bool has_motion( Button ) ;
    ///@}
} ;

}}} // namespace esve::components::dim3

#endif

