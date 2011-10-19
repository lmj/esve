
#include <esve/components/dim4/Motion_Frame.hxx>

namespace esve { namespace components { namespace dim4 {

using types::real ;
using types::quat ;

Motion_Frame::
Motion_Frame()
    : components::dimn::Motion_Handler(),
      Frame(),
      m_dtranslate_dt(0, 0, 0, 0),
      m_dinvertate_dt(0, 0, 0, 0),
      m_dscalate_dt(0),
      m_dalpha_dt(0),
      m_dbeta_dt(0),
      m_plane_vector0(1, 0, 0, 0),
      m_plane_vector1(0, 1, 0, 0),
      m_translate_basis(&engine::dim4::Transform::IDENTITY),
      m_invertate_basis(&engine::dim4::Transform::IDENTITY),
      m_scalate_basis(&engine::dim4::Transform::IDENTITY),
      m_rotate_basis(&engine::dim4::Transform::IDENTITY)
{
}

Motion_Frame::
~Motion_Frame()
{
}

void
Motion_Frame::
rotate_velocity( real dalpha_dt,
                 real dbeta_dt,
                 const quat & plane_vector0,
                 const quat & plane_vector1,
                 const engine::dim4::Transform & basis )
{
    m_dalpha_dt = dalpha_dt ;
    m_dbeta_dt = dbeta_dt ;
    m_plane_vector0 = plane_vector0 ;
    m_plane_vector1 = plane_vector1 ;
    m_rotate_basis = &basis ;
}

void
Motion_Frame::
translate_velocity( const quat & dtranslate_dt,
                    const engine::dim4::Transform & basis )
{
    m_dtranslate_dt = dtranslate_dt ;
    m_translate_basis = &basis ;
}

void
Motion_Frame::
invertate_velocity( const quat & dinvertate_dt,
                    const engine::dim4::Transform & basis )
{
    m_dinvertate_dt = dinvertate_dt ;
    m_invertate_basis = &basis ;
}

void
Motion_Frame::
scalate_velocity( real dscalate_dt,
                  const engine::dim4::Transform & basis )
{
    m_dscalate_dt = dscalate_dt ;
    m_scalate_basis = &basis ;
}

bool
Motion_Frame::
handle_check_awake( bool )
{
    return
        m_dtranslate_dt != quat(0, 0, 0, 0) ||
        m_dinvertate_dt != quat(0, 0, 0, 0) ||
        m_dscalate_dt != 0 ||
        m_dalpha_dt != 0 ||
        m_dbeta_dt != 0 ;
}

void
Motion_Frame::
update( double dt )
{
    Frame::update(dt) ;

    if( dt != 0 )
    {
        if( m_dalpha_dt != 0 && m_dbeta_dt != 0 )
        {
            peek_transform().rotate(m_dalpha_dt*dt,
                                    m_dbeta_dt*dt,
                                    m_plane_vector0,
                                    m_plane_vector1,
                                    *m_rotate_basis) ;
        }
        if( m_dtranslate_dt != quat(0) )
        {
            peek_transform().translate(m_dtranslate_dt*real(dt),
                                       *m_translate_basis) ;
        }
        if( m_dinvertate_dt != quat(0) )
        {
            peek_transform().invertate(m_dinvertate_dt*real(dt),
                                       *m_invertate_basis) ;
        }
        if( m_dscalate_dt != 0 )
        {
            peek_transform().scalate(m_dscalate_dt*dt,
                                     *m_scalate_basis) ;
        }
    }
}

void
Motion_Frame::
update()
{
    Frame::update() ;
}

}}} // namespace esve::components::dim4
