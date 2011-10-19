
#include <esve/components/dim4/Rotation_Handler.hxx>
#include <esve/math/constants.hxx>

namespace esve { namespace components { namespace dim4 {

using types::real ;
using types::pure ;

const real SQRT1_2 = math::constants::SQRT1_2 ;

struct Rotation_Handler::Private
{
    struct Motion_Data
    {
        // method to associate mouse drags with rotations
        Mapping mapping ;

        // rotations are aligned with (1,u)
        pure u ;

        // first differential angle
        real dalpha_dt ;

        // second differential angle
        real dbeta_dt ;

        Motion_Data() ;
    } ;

    Motion_Data motion_data[Supermouse::NUM_BUTTONS] ;

    Private() ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Rotation_Handler::Private::
Private()
{
    motion_data[Supermouse::LEFT].mapping = ROTATE_K_TOWARD_U ;
    motion_data[Supermouse::MIDDLE].mapping = DO_NOTHING ;
    motion_data[Supermouse::RIGHT].mapping = ROTATE_1_TOWARD_U ;
}

Rotation_Handler::Private::
Motion_Data::
Motion_Data()
    : mapping(DO_NOTHING),
      u(0, 0, 1),
      dalpha_dt(0),
      dbeta_dt(0)
{
}

Rotation_Handler::
Rotation_Handler( engine::dim4::Transform & transform )
    : super(transform),
      m(new Private())
{
}

Rotation_Handler::
~Rotation_Handler()
{
}

void
Rotation_Handler::
mapping( Button button, Mapping mapping )
{
    m->motion_data[button].mapping = mapping ;
}

Rotation_Handler::Mapping
Rotation_Handler::mapping( Button button ) const
{
    return m->motion_data[button].mapping ;
}

void
Rotation_Handler::
stop_motion( Button button )
{
    m->motion_data[button].dalpha_dt = 0 ;
    m->motion_data[button].dbeta_dt = 0 ;
}

bool
Rotation_Handler::
has_motion( Button button )
{
    return
        m->motion_data[button].dalpha_dt != 0
        ||
        m->motion_data[button].dbeta_dt != 0 ;
}

engine::dim4::Transform
Rotation_Handler::
differential_motion( Button button, real dt )
{
    engine::dim4::Transform action ;

    action.rotate(m->motion_data[button].dalpha_dt*dt,
                  m->motion_data[button].dbeta_dt*dt,
                  m->motion_data[button].u) ;

    return action ;
}

void
Rotation_Handler::
create_motion( Button button, const pure & du_dt )
{
    const real dx_dt = du_dt.x() ;
    const real dy_dt = du_dt.y() ;
    const real length = abs(du_dt) ;

    Private::Motion_Data & motion = m->motion_data[button] ;

    switch( motion.mapping )
    {
    case ROTATE_K_TOWARD_U:
        motion.u = pure(-dy_dt, dx_dt, 0)/length ;
        motion.dalpha_dt = 0 ;
        motion.dbeta_dt = length ;
        break ;

    case ROTATE_K_TOWARD_U_PERP:
        motion.u = pure(-dy_dt, dx_dt, 0)/length ;
        motion.dalpha_dt = length ;
        motion.dbeta_dt = 0 ;
        break ;

    case ROTATE_1_TOWARD_U:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = length ;
        motion.dbeta_dt = 0 ;
        break ;

    case ROTATE_1_TOWARD_U_PERP:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = 0 ;
        motion.dbeta_dt = length ;
        break ;

    case DOUBLE_ROTATE_1IJK:
        motion.u = pure(1, 0, 0) ;
        motion.dalpha_dt = dx_dt ;
        motion.dbeta_dt = dy_dt ;
        break ;

    case DOUBLE_ROTATE_1JKI:
        motion.u = pure(0, 1, 0) ;
        motion.dalpha_dt = dx_dt ;
        motion.dbeta_dt = dy_dt ;
        break ;

    case DOUBLE_ROTATE_1KIJ:
        motion.u = pure(0, 0, 1) ;
        motion.dalpha_dt = dx_dt ;
        motion.dbeta_dt = dy_dt ;
        break ;

    case DOUBLE_ROTATE_IJ1K:
        motion.u = pure(0, 0, 1) ;
        motion.dalpha_dt = dy_dt ;
        motion.dbeta_dt = dx_dt ;
        break ;

    case LEFT_HOPF_ROTATION:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = length*SQRT1_2 ;
        motion.dbeta_dt = length*SQRT1_2 ;
        break ;

    case NEG_LEFT_HOPF_ROTATION:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = -length*SQRT1_2 ;
        motion.dbeta_dt = -length*SQRT1_2 ;
        break ;

    case RIGHT_HOPF_ROTATION:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = -length*SQRT1_2 ;
        motion.dbeta_dt = length*SQRT1_2 ;
        break ;

    case NEG_RIGHT_HOPF_ROTATION:
        motion.u = pure(dx_dt, dy_dt, 0)/length ;
        motion.dalpha_dt = length*SQRT1_2 ;
        motion.dbeta_dt = -length*SQRT1_2 ;
        break ;

    case DO_NOTHING:
        motion.u = pure(1, 0, 0) ;
        motion.dalpha_dt = 0 ;
        motion.dbeta_dt = 0 ;
        break ;
    }

    //
    // units
    //
    // incoming du_dt is in pixels per second.
    //

    motion.dalpha_dt *= RADIANS_PER_PIXEL ;
    motion.dbeta_dt *= RADIANS_PER_PIXEL ;

    //
    // dalpha_dt and dbeta_dt are now in radians per second
    //
}

}}} // namespace esve::components::dim4
