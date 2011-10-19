
#include <esve/components/dim3/Motion_Frame.hxx>

namespace esve { namespace components { namespace dim3 {

using types::real ;
using types::pure ;

Motion_Frame::
Motion_Frame()
    : components::dimn::Motion_Handler(),
      Frame(),
      m_dtranslate_dt(0, 0, 0),
      m_dtheta_dt(0),
      m_axis(1, 0, 0),
      m_translate_basis(&engine::dim3::Transform::IDENTITY),
      m_rotate_basis(&engine::dim3::Transform::IDENTITY)
{
}

Motion_Frame::
~Motion_Frame()
{
}

void
Motion_Frame::
translate_velocity( const pure & dtranslate_dt,
                    const engine::dim3::Transform & basis )
{
    m_dtranslate_dt = dtranslate_dt ;
    m_translate_basis = &basis ;
}

void
Motion_Frame::
rotate_velocity( real dtheta_dt,
                 const pure & axis,
                 const engine::dim3::Transform & basis )
{
    m_dtheta_dt = dtheta_dt ;
    m_axis = axis ;
    m_rotate_basis = &basis ;
}

bool
Motion_Frame::
handle_check_awake( bool )
{
    return
        m_dtheta_dt != 0 ||
        m_dtranslate_dt != pure(0, 0, 0) ;
}

void
Motion_Frame::
update( double dt )
{
    Frame::update(dt) ;

    if( dt != 0 )
    {
        if( m_dtheta_dt != 0 )
        {
            peek_transform().rotate(m_dtheta_dt*dt, m_axis, *m_rotate_basis) ;
            peek_transform().normalize() ;
        }
        if( m_dtranslate_dt != pure(0, 0, 0) )
        {
            peek_transform().translate(m_dtranslate_dt*real(dt),
                                       *m_translate_basis) ;
        }
    }
}

void
Motion_Frame::
update()
{
    Frame::update() ;
}

}}} // namespace esve::components::dim3
