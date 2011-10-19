
#include <esve/components/dim3/Keyboard_Rotation_Handler.hxx>
#include <esve/engine/dim3/Transform.hxx>

namespace esve { namespace components { namespace dim3 {

using types::pure ;

Keyboard_Rotation_Handler::
Keyboard_Rotation_Handler( engine::dim3::Transform & transform )
    : m_transform(transform),
      m_angular_velocity(0.1)
{
}

Keyboard_Rotation_Handler::
~Keyboard_Rotation_Handler()
{
}

bool
Keyboard_Rotation_Handler::
handle_key_push( Key, const Keyboard & )
{
    return false ;
}

bool
Keyboard_Rotation_Handler::
handle_key_release( Key, const Keyboard & )
{
    return false ;
}

bool
Keyboard_Rotation_Handler::
handle_check_awake( bool )
{
    return
        keyboard().pushed(Key('a')) ||
        keyboard().pushed(Key('s')) ||
        keyboard().pushed(Key('d')) ||
        keyboard().pushed(Key('w')) ;
}

void
Keyboard_Rotation_Handler::
update( double dt )
{
    if( keyboard().pushed(Key('s')) )
    {
        m_transform.rotate(m_angular_velocity*dt,
                           pure(1, 0, 0)) ;
    }
    if( keyboard().pushed(Key('w')) )
    {
        m_transform.rotate(-m_angular_velocity*dt,
                           pure(1, 0, 0)) ;
    }
    if( keyboard().pushed(Key('d')) )
    {
        m_transform.rotate(m_angular_velocity*dt,
                           pure(0, 1, 0)) ;
    }
    if( keyboard().pushed(Key('a')) )
    {
        m_transform.rotate(-m_angular_velocity*dt,
                           pure(0, 1, 0)) ;
    }
}

void
Keyboard_Rotation_Handler::
update()
{
    // async update. nothing to do.
}

}}} // namespace esve::components::dim3
