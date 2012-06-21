
#include <esve/viewers/dim3/Canned_Viewer.hxx>
#include <esve/components/dim3/Rotation_Handler.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Geom.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>

namespace esve { namespace viewers { namespace dim3 {

using types::real ;
using types::quat ;

struct Canned_Viewer::Private
{
    struct Reset_Handler
        : public ui::base::Keyboard_Handler
    {
        Canned_Viewer::Private & m ;

        Reset_Handler( Canned_Viewer::Private & m_ )
            : m(m_) { }

        bool handle_key_push( Key key, const Keyboard & )
        {
            switch( int(key) )
            {
            case 'r':
                m.rotation_frame.peek_transform().assign(m.home_transform) ;
                m.rotation_handler.stop() ;
                return true ;

            default:
                ;
            }

            return false ;
        }

        bool handle_key_release( Key , const Keyboard & )
        {
            return false ;
        }
    } ;

    engine::dim3::Transform home_transform ;
    engine::dim3::impl::Frame scaling_frame ;
    engine::dim3::impl::Frame rotation_frame ;
    components::dim3::Rotation_Handler rotation_handler ;
    Reset_Handler reset_handler ;

    Private() ;
    ~Private() ;
} ;

Canned_Viewer::Private::
Private()
    : home_transform(),
      scaling_frame(),
      rotation_frame(),
      rotation_handler(rotation_frame.peek_transform()),
      reset_handler(*this)
{
}

Canned_Viewer::Private::
~Private()
{
}

Canned_Viewer::
Canned_Viewer( int argc, char** argv )
    : super(argc, argv),
      m(new Private())
{
    super::add_frame(m->scaling_frame) ;
    m->scaling_frame.add(m->rotation_frame) ;

    super::add_handler(m->rotation_handler) ;
    super::add_handler(m->reset_handler) ;

    m->rotation_handler.sensitivity(super::sensitivity()) ;
}

Canned_Viewer::
~Canned_Viewer()
{
}

void
Canned_Viewer::
add_geom( engine::dim3::Geom & a )
{
    super::add_geom(a) ;
    m->rotation_frame.add(a) ;
}

void
Canned_Viewer::
remove_geom( engine::dim3::Geom & a )
{
    super::remove_geom(a) ;
    m->rotation_frame.remove(a) ;
}

void
Canned_Viewer::
scaling( real a )
{
    m->scaling_frame.peek_transform().scaling(a) ;
}

real
Canned_Viewer::
scaling() const
{
    return m->scaling_frame.peek_transform().scaling() ;
}

const engine::dim3::Transform &
Canned_Viewer::
home_transform() const
{
    return m->home_transform ;
}

void
Canned_Viewer::
home_transform( const engine::dim3::Transform & a )
{
    m->home_transform = a ;
}

const engine::dim3::Transform &
Canned_Viewer::
rotation() const
{
    return m->rotation_frame.peek_transform() ;
}

void
Canned_Viewer::
rotation( const quat & a )
{
    m->rotation_frame.peek_transform().assign(
        engine::dim3::Transform(a/abs(a))) ;
}

void
Canned_Viewer::
stop_motion()
{
    m->rotation_handler.stop() ;
}

}}} // namespace esve::viewers::dim3
