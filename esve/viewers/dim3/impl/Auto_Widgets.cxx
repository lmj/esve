
#include <esve/viewers/dim3/impl/Auto_Widgets.hxx>
#include <esve/viewers/dimn/Scaling.hxx>
#include <esve/components/dimn/Valuator_Creator.hxx>
#include <esve/components/dimn/Valuator_Handler.hxx>

namespace esve { namespace viewers { namespace dim3 { namespace impl {

using types::real ;

typedef components::dimn::Valuator<real> Valuator ;
typedef components::dimn::Valuator_Creator<real> Valuator_Creator ;
typedef components::dimn::Valuator_Handler<real> Valuator_Handler ;

struct Auto_Widgets::Private
{
    Valuator_Creator & ui ;
    dimn::Scaling & scaling_frame ;

    Valuator* scaling_valuator ;

    Private( Valuator_Creator & ui_,
             dimn::Scaling & scaling_frame_ )
        : ui(ui_),
          scaling_frame(scaling_frame_),
          scaling_valuator(0) { }

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Auto_Widgets::
Auto_Widgets( Valuator_Creator & ui,
              dimn::Scaling & scaling_frame )
    : viewers::dim3::Auto_Widgets(),
      m(new Private(ui, scaling_frame))
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

bool
Auto_Widgets::
handle_valuator( const Valuator & valuator )
{
    bool handled = false ;

    if( &valuator == m->scaling_valuator )
    {
        m->scaling_frame.scaling(real(valuator.value())) ;
        handled = true ;
    }

    return handled ;
}

}}}} // namespace esve::viewers::dim3::impl
