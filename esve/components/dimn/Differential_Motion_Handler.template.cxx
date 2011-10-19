
#include <esve/components/dimn/Differential_Motion_Handler.hxx>

namespace esve { namespace components { namespace dimn {

template< typename Transform >
Differential_Motion_Handler<Transform>::
m_Button_Data::m_Button_Data()
    : basis(&Transform::IDENTITY),
      motion_basis(),
      frame(),
      go(false)
{
}

template< typename Transform >
Differential_Motion_Handler<Transform>::
Differential_Motion_Handler( Transform & transform )
    : super(),
      m_transform(&transform),
      m_root(),
      m_dt_since_drag(),
      m_reset_frames(true)
{
}

template< typename Transform >
Differential_Motion_Handler<Transform>::
~Differential_Motion_Handler()
{
}

template< typename Transform >
void
Differential_Motion_Handler<Transform>::
basis( Button b, const Transform & basis )
{
    m_button[b].basis = &basis ;
}

template< typename Transform >
const Transform &
Differential_Motion_Handler<Transform>::
basis( Button b ) const
{
    return *m_button[b].basis ;
}

template< typename Transform >
void
Differential_Motion_Handler<Transform>::
active_transform( Transform & f )
{
    m_transform = &f ;
    m_reset_frames = true ;
}

// updates are done through a timing loop, therefore do not signal an
// args-driven update for push and release, i.e., return false

template< typename Transform >
bool
Differential_Motion_Handler<Transform>::
handle_supermouse_push( Button b, const Supermouse & supermouse )
{
    super::handle_supermouse_push(b, supermouse) ;

    m_button[b].go = false ;

    // hook!
    stop_motion(b) ;

    m_button[b].motion_basis = *m_transform ;
    m_button[b].motion_basis.invert() ;
    m_button[b].motion_basis.right_act(*m_button[b].basis) ;

    m_reset_frames = true ;

    return false ;
}

template< typename Transform >
bool
Differential_Motion_Handler<Transform>::
handle_supermouse_release( Button b, const Supermouse & supermouse )
{
    super::handle_supermouse_release(b, supermouse) ;

    if( m_dt_since_drag < MOTION_TRIGGER_TIME )
    {
        // hook!
        if( has_motion(b) )
        {
            m_button[b].go = true ;
        }
    }

    return false ;
}

template< typename Transform >
bool
Differential_Motion_Handler<Transform>::
handle_check_awake( bool )
{
    bool handled = false ;

    for( unsigned int i = 0 ;
         i != Supermouse::NUM_BUTTONS ;
         ++i )
    {
        if( m_button[i].go
            ||
            supermouse().pushed(Button(i)) )
        {
            handled = true ;
            break ;
        }
    }

    return handled ;
}

template< typename Transform >
void
Differential_Motion_Handler<Transform>::
update( double dt )
{
    super::update(dt) ;

    if( dt == 0 )
    {
        return ;
    }

    if( m_reset_frames )
    {
        m_root = *m_transform ;
        for( unsigned int i = 0 ; i != Supermouse::NUM_BUTTONS ; ++i )
        {
            m_button[i].frame.identity() ;
        }
        m_reset_frames = false ;
    }

    {
        unsigned int i = 0 ;
        for( ; i != Supermouse::NUM_BUTTONS ; ++i )
        {
            if( du_dt(Button(i)) != types::real(0) )
            {
                break ;
            }
        }

        if( i == Supermouse::NUM_BUTTONS )
        {
            // all button velocities were zero
            m_dt_since_drag += dt ;
        }
        else
        {
            m_dt_since_drag = 0 ;
        }
    }

    for( unsigned int i = 0 ; i != Supermouse::NUM_BUTTONS ; ++i )
    {
        if( du_dt(Button(i)) != types::real(0)
            &&
            sensitivity() != types::real(0) )
        {
            // hook!
            create_motion(Button(i),
                          types::real(sensitivity())*du_dt(Button(i))) ;
        }

        if( m_button[i].go || du_dt(Button(i)) != types::real(0) )
        {
            m_button[i].frame.act(differential_motion(Button(i), dt),
                                  m_button[i].motion_basis) ;

            // hook!
            normalize(m_button[i].frame) ;
        }
    }

    {
        Transform result = m_root ;

        for( unsigned int i = 0 ; i != Supermouse::NUM_BUTTONS ; ++i )
        {
            result.right_act(m_button[i].frame) ;
        }

        // hook!
        normalize(result) ;

        m_transform->assign(result) ;
    }
}

template< typename Transform >
void
Differential_Motion_Handler<Transform>::
stop()
{
    for( unsigned int i = 0 ; i != Supermouse::NUM_BUTTONS ; ++i )
    {
        m_button[i].go = false ;

        // hook!
        stop_motion(Button(i)) ;
    }

    m_reset_frames = true ;
}

template< typename Transform >
void
Differential_Motion_Handler<Transform>::
normalize( Transform & transform )
{
    transform.normalize() ;
}

}}} // namespace esve::components::dimn
