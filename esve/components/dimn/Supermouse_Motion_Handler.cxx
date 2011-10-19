
#include <esve/components/dimn/Supermouse_Motion_Handler.hxx>

namespace esve { namespace components { namespace dimn {

using types::real ;
using types::pure ;

const real
Supermouse_Motion_Handler::
RADIANS_PER_PIXEL = 1e-3 ;

const real
Supermouse_Motion_Handler::
DEFAULT_SENSITIVITY = 0.75 ;

const real
Supermouse_Motion_Handler::
MOTION_TRIGGER_TIME = 0.08 ;

struct Supermouse_Motion_Handler::Private
{
    struct Button_Data
    {
        pure u ;
        pure previous_u ;

        pure du_dt ;
        pure previous_du_dt ;

        pure d2u_dt2 ;

        Button_Data()
            : u(),
              previous_u(),
              du_dt(),
              previous_du_dt(),
              d2u_dt2() { }
    } ;

    void reset( Supermouse_Motion_Handler::Button ) ;

    // the last button is "no button"
    static const unsigned int NUM_BUTTON_DATA =
    Supermouse::NUM_BUTTONS + 1 ;
    Button_Data button_data[NUM_BUTTON_DATA] ;

    Supermouse_Motion_Handler & outside ;
    real sensitivity ;

    Private( Supermouse_Motion_Handler & outside_ )
        : outside(outside_),
          sensitivity(DEFAULT_SENSITIVITY) { }

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Supermouse_Motion_Handler::
Supermouse_Motion_Handler()
    : m(new Private(*this))
{
}

Supermouse_Motion_Handler::
~Supermouse_Motion_Handler()
{
}

void
Supermouse_Motion_Handler::
update( double dt )
{
    if( dt == 0 )
    {
        return ;
    }

    for( unsigned int i = 0 ;
         i != Private::NUM_BUTTON_DATA ;
         ++i )
    {
        if( i == Supermouse::NUM_BUTTONS
            ||
            supermouse().pushed(Button(i)) )
        {
            Private::Button_Data & data = m->button_data[i] ;

            data.previous_u = data.u ;
            data.u = supermouse().position() ;
            data.previous_du_dt = data.du_dt ;
            data.du_dt = (data.u - data.previous_u)/real(dt) ;
            data.d2u_dt2 = (data.du_dt - data.previous_du_dt)/real(dt) ;
        }
    }
}

void
Supermouse_Motion_Handler::
update()
{
    // async update. nothing to do.
}

const pure &
Supermouse_Motion_Handler::
u() const
{
    return m->button_data[Supermouse::NUM_BUTTONS].u ;
}

const pure &
Supermouse_Motion_Handler::
du_dt() const
{
    return m->button_data[Supermouse::NUM_BUTTONS].du_dt ;
}

const pure &
Supermouse_Motion_Handler::
d2u_dt2() const
{
    return m->button_data[Supermouse::NUM_BUTTONS].d2u_dt2 ;
}

const pure &
Supermouse_Motion_Handler::
du_dt( Button b ) const
{
    return m->button_data[b].du_dt ;
}

const pure &
Supermouse_Motion_Handler::
d2u_dt2( Button b ) const
{
    return m->button_data[b].d2u_dt2 ;
}

real
Supermouse_Motion_Handler::
sensitivity() const
{
    return m->sensitivity ;
}

void
Supermouse_Motion_Handler::
sensitivity( real a )
{
    m->sensitivity = a ;
}

bool
Supermouse_Motion_Handler::
handle_supermouse_move( const Supermouse & )
{
    // do not signal asynchronous updates
    return false ;
}

bool
Supermouse_Motion_Handler::
handle_supermouse_push( Button button, const Supermouse & )
{
    m->reset(button) ;

    // do not signal asynchronous updates
    return false ;
}

bool
Supermouse_Motion_Handler::
handle_supermouse_release( Button button, const Supermouse & )
{
    m->reset(button) ;

    // do not signal asynchronous updates
    return false ;
}

void
Supermouse_Motion_Handler::Private::
reset( Button button )
{
    Button_Data & data = button_data[button] ;

    data.previous_u = outside.supermouse().position() ;
    data.u = outside.supermouse().position() ;
    data.previous_du_dt = pure(0, 0, 0) ;
    data.du_dt = pure(0, 0, 0) ;
    data.d2u_dt2 = pure(0, 0, 0) ;
}

}}} // namespace esve::components::dimn
