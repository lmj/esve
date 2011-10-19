
#ifndef esve_components_dim3_Keyboard_Rotation_Handler_hxx
#define esve_components_dim3_Keyboard_Rotation_Handler_hxx

#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/types/real.hxx>

namespace esve { namespace engine { namespace dim3 { class Transform ; } } }

namespace esve { namespace components { namespace dim3 {

///
/// @class Keyboard_Rotation_Handler esve/components/dim3/Keyboard_Rotation_Handler.hxx
/// @brief Rotate a frame with the a,s,d,w keys.
///

class Keyboard_Rotation_Handler
    : public components::dimn::Motion_Handler,
      public ui::base::Keyboard_Handler
{
public:
    /// Constructor.  Give the transform to be rotated.
    explicit
    Keyboard_Rotation_Handler( engine::dim3::Transform & ) ;

    ///@{
    ///
    /// @brief Angular velocity in radians per sec.
    ///
    types::real angular_velocity() const
    {
        return m_angular_velocity ;
    }

    void angular_velocity( types::real a )
    {
        m_angular_velocity = a ;
    }
    ///@}

    ~Keyboard_Rotation_Handler() ;

protected:
    void update() ;
    void update( double dt ) ;

    bool handle_check_awake( bool currently_awake ) ;
    bool handle_key_push( Key, const Keyboard & ) ;
    bool handle_key_release( Key, const Keyboard & ) ;

private:
    typedef kernel::Wake_State_Handler m_Wake_State_Handler_Base ;
    typedef ui::base::Keyboard_Handler m_Keyboard_Handler_Base ;

    Keyboard_Rotation_Handler( const Keyboard_Rotation_Handler & ) ;
    Keyboard_Rotation_Handler &
    operator=( const Keyboard_Rotation_Handler & ) ;

    engine::dim3::Transform & m_transform ;
    types::real m_angular_velocity ;
} ;

}}} // namespace esve::components::dim3

#endif

