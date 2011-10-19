
#ifndef esve_components_dim3_Motion_Frame_hxx
#define esve_components_dim3_Motion_Frame_hxx

#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace components { namespace dim3 {

///
/// @class Motion_Frame esve/components/dim3/Motion_Frame.hxx
/// @brief A Moving frame.
///

class Motion_Frame
    : public components::dimn::Motion_Handler,
      public engine::dim3::impl::Frame
{
public:
    Motion_Frame() ;

    /// @brief Angular velocity in radians per second.  The basis is
    /// stored by reference.
    void rotate_velocity( types::real dtheta_dt,
                          const types::pure & axis,
                          const engine::dim3::Transform & basis =
                          engine::dim3::Transform::IDENTITY ) ;

    /// Velocity in units per second. The basis is stored by reference.
    void translate_velocity( const types::pure & dtranslate_dt,
                             const engine::dim3::Transform & basis =
                             engine::dim3::Transform::IDENTITY ) ;

    ~Motion_Frame() ;

protected:
    bool handle_check_awake( bool currently_awake ) ;

    void update() ;
    void update( double dt ) ;

private:
    Motion_Frame( const Motion_Frame & ) ;
    Motion_Frame & operator=( const Motion_Frame & ) ;

    types::pure m_dtranslate_dt ;
    types::real m_dtheta_dt ;
    types::pure m_axis ;
    const engine::dim3::Transform* m_translate_basis ;
    const engine::dim3::Transform* m_rotate_basis ;
} ;

}}} // namespace esve::components::dim3

#endif

