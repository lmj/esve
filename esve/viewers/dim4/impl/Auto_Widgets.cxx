
#include <esve/viewers/dim4/impl/Auto_Widgets.hxx>
#include <esve/viewers/dim4/Inversion.hxx>
#include <esve/viewers/dimn/Scaling.hxx>
#include <esve/components/dimn/Valuator_Creator.hxx>
#include <limits>

namespace esve { namespace viewers { namespace dim4 { namespace impl {

using types::real ;
using viewers::dimn::Scaling ;

typedef components::dimn::Valuator<real> Valuator ;
typedef components::dimn::Valuator_Creator<real> Valuator_Creator ;
typedef components::dimn::Valuator_Handler<real> Valuator_Handler ;

struct Auto_Widgets::Private
{
    Valuator_Creator & ui ;
    Scaling & scaling_frame ;
    Inversion & inversion_frame ;

    Valuator* scaling_valuator ;
    Valuator* inversion_valuator ;

    Private( Valuator_Creator & ui_,
             Scaling & scaling_frame_,
             Inversion & inversion_frame_ )
        : ui(ui_),
          scaling_frame(scaling_frame_),
          inversion_frame(inversion_frame_),
          scaling_valuator(0),
          inversion_valuator(0) { }

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Auto_Widgets::
Auto_Widgets( Valuator_Creator & ui,
              Scaling & scaling_frame,
              Inversion & inversion_frame )
    : Valuator_Handler(),
      m(new Private(ui,
                    scaling_frame,
                    inversion_frame))
{
}

Auto_Widgets::
~Auto_Widgets()
{
}

Valuator &
Auto_Widgets::
create_scaling_valuator( const std::string & label )
{
    if( m->scaling_valuator == 0 )
    {
        m->scaling_valuator =
            &m->ui.create_valuator(1.0, label).step(0.005) ;
    }

    return *m->scaling_valuator ;
}

Valuator &
Auto_Widgets::
create_inversion_valuator( const std::string & label )
{
    if( m->inversion_valuator == 0 )
    {
        const real max = std::numeric_limits<real>::max() ;

        m->inversion_valuator =
            &m->ui.create_valuator(1.0, label).step(0.005).range(0, max) ;
    }

    return *m->inversion_valuator ;
}

bool
Auto_Widgets::
handle_valuator( const Valuator & valuator )
{
    bool handled = false ;

    if( &valuator == m->scaling_valuator )
    {
        m->scaling_frame.scaling(valuator.value()) ;
        handled = true ;
    }
    else if( &valuator == m->inversion_valuator )
    {
        m->inversion_frame.inversion(valuator.value()) ;
        handled = true ;
    }

    return handled ;
}

}}}} // namespace esve::viewers::dim4::impl
