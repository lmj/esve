//
// frames which move on each update()
//

#ifndef esve_components_dim4_Motion_Frame_hxx
#define esve_components_dim4_Motion_Frame_hxx

#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/engine/dim4/impl/Frame.hxx>
#include <esve/engine/dim4/Transform.hxx>
#include <esve/types/quat.hxx>

namespace esve { namespace components { namespace dim4 {

///
/// @class Motion_Frame esve/components/dim4/Motion_Frame.hxx
/// @brief A Moving frame.
///

class Motion_Frame
    : public components::dimn::Motion_Handler,
      public engine::dim4::impl::Frame
{
public:
    Motion_Frame() ;

    //
    // see base::dim4::Transform for more info
    //

    /// @brief Angular velocity in radians per second. The basis is
    /// stored by reference.
    void rotate_velocity( types::real dalpha_dt,
                          types::real dbeta_dt,
                          const types::quat & a,
                          const types::quat & b,
                          const engine::dim4::Transform & basis =
                          engine::dim4::Transform::IDENTITY ) ;

    /// Velocity in units per second. The basis is stored by reference.
    void translate_velocity( const types::quat & dtranslate_dt,
                             const engine::dim4::Transform & basis =
                             engine::dim4::Transform::IDENTITY ) ;

    /// Velocity in units per second. The basis is stored by reference.
    void invertate_velocity( const types::quat & dinvertate_dt,
                             const engine::dim4::Transform & basis =
                             engine::dim4::Transform::IDENTITY ) ;

    /// Velocity in units per second. The basis is stored by reference.
    void scalate_velocity( types::real dscalate_dt,
                           const engine::dim4::Transform & basis =
                           engine::dim4::Transform::IDENTITY ) ;

    ~Motion_Frame() ;

protected:
    bool handle_check_awake( bool currently_awake ) ;

    void update() ;
    void update( double dt ) ;

private:
    Motion_Frame( const Motion_Frame & ) ;
    Motion_Frame & operator=( const Motion_Frame & ) ;

    types::quat m_dtranslate_dt ;
    types::quat m_dinvertate_dt ;
    types::real m_dscalate_dt ;
    types::real m_dalpha_dt ;
    types::real m_dbeta_dt ;
    types::quat m_plane_vector0 ;
    types::quat m_plane_vector1 ;

    const engine::dim4::Transform* m_translate_basis ;
    const engine::dim4::Transform* m_invertate_basis ;
    const engine::dim4::Transform* m_scalate_basis ;
    const engine::dim4::Transform* m_rotate_basis ;
} ;

}}} // namespace esve::components::dim4

#endif

