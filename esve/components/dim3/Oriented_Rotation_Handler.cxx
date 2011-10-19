
#include <esve/components/dim3/Oriented_Rotation_Handler.hxx>
#include <esve/engine/dim3/transform_util.hxx>

namespace esve { namespace components { namespace dim3 {

using types::real ;
using types::pure ;

Oriented_Rotation_Handler::
Oriented_Rotation_Handler( engine::dim3::Transform & transform )
    : super(transform),
      m_dtheta_dt(0),
      m_dphi_dt(0),
      m_sign(1)
{
}

Oriented_Rotation_Handler::
~Oriented_Rotation_Handler()
{
}

void
Oriented_Rotation_Handler::
stop_motion( Button )
{
    m_dtheta_dt = 0 ;
    m_dphi_dt = 0 ;
}

bool
Oriented_Rotation_Handler::
has_motion( Button button )
{
    if( button == Supermouse::LEFT )
    {
        return
            m_dtheta_dt != 0
            ||
            m_dphi_dt != 0 ;
    }

    return false ;
}

engine::dim3::Transform
Oriented_Rotation_Handler::
differential_motion( Button button, real dt )
{
    engine::dim3::Transform action ;

    if( button == Supermouse::LEFT )
    {
        action.rotate(m_sign*m_dtheta_dt*dt,
                      pure(0, 0, 1),
                      active_transform()) ;
        action.rotate(m_dphi_dt*dt,
                      pure(1, 0, 0)) ;
    }

    return action ;
}

void
Oriented_Rotation_Handler::
create_motion( Button button, const pure & du_dt )
{
    if( button == Supermouse::LEFT )
    {
        m_dtheta_dt = du_dt.x()*RADIANS_PER_PIXEL  ;

        // positive vertical input corresponds to rotation around
        // x-axis with negative angle.
        m_dphi_dt = -du_dt.y()*RADIANS_PER_PIXEL  ;
    }
}

bool
Oriented_Rotation_Handler::
handle_supermouse_push( Button button, const Supermouse & state )
{
    // switch spin direction if upside down

    m_sign = real(1) ;

    const engine::dim3::Transform
        transform0(active_transform().rotation()) ;

    const pure u0 = pure(0, 0, 1) ;
    const pure tu0 =
        engine::dim3::transform_util::apply_transform(transform0, u0) ;

    if( cross(u0, tu0).x() > 0 )
    {
        m_sign = real(-1) ;
    }

    return super::handle_supermouse_push(button, state) ;
}

}}} // namespace esve::components::dim3
