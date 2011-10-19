
#include <esve/components/dim3/Rotation_Handler.hxx>

namespace esve { namespace components { namespace dim3 {

using types::real ;
using types::pure ;

Rotation_Handler::
m_Motion_Data::
m_Motion_Data()
    : u(0, 0, 1),
      dtheta_dt(0)
{
}

Rotation_Handler::
Rotation_Handler( engine::dim3::Transform & transform )
    : super(transform)
{
}

Rotation_Handler::
~Rotation_Handler()
{
}

void
Rotation_Handler::
stop_motion( Button button )
{
    m_motion_data[button].dtheta_dt = 0 ;
}

bool
Rotation_Handler::
has_motion( Button button )
{
    return m_motion_data[button].dtheta_dt != 0 ;
}

engine::dim3::Transform
Rotation_Handler::
differential_motion( Button button, real dt )
{
    engine::dim3::Transform action ;

    action.rotate(m_motion_data[button].dtheta_dt*dt,
                  m_motion_data[button].u) ;

    return action ;
}

void
Rotation_Handler::
create_motion( Button button, const pure & du_dt )
{
    const real length = abs(du_dt) ;

    // axis is perpendicular to mouse drag
    m_motion_data[button].u = pure(-du_dt.y(), du_dt.x(), 0)/length ;

    m_motion_data[button].dtheta_dt = length ;

    //
    // units
    //
    // incoming du_dt is in pixels per second.
    //

    m_motion_data[button].dtheta_dt *= RADIANS_PER_PIXEL ;

    //
    // dtheta_dt is now in radians per second
    //
}

}}} // namespace esve::components::dim3
