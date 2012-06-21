
#include <esve/viewers/dim4/Canned_Viewer.hxx>
#include <esve/components/dim4/Simple_Rotation_Handler.hxx>
#include <esve/engine/dim4/impl/Frame.hxx>
#include <esve/engine/dim4/Transform.hxx>
#include <esve/engine/dim4/Geom.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/message/Draw_Sender.hxx>

namespace esve { namespace viewers { namespace dim4 {

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

            case 'c':
                m.rotation_handler.mapping(
                    m.rotation_handler.mapping()
                    ==
                    components::dim4::Simple_Rotation_Handler::LONGLAT
                    ?
                    components::dim4::Simple_Rotation_Handler::HOPF
                    :
                    components::dim4::Simple_Rotation_Handler::LONGLAT) ;
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

    engine::dim4::Transform home_transform ;
    engine::dim4::impl::Frame root_frame ;
    engine::dim4::impl::Frame scaling_frame ;
    engine::dim4::impl::Frame inversion_frame ;
    engine::dim4::impl::Frame rotation_frame ;
    components::dim4::Simple_Rotation_Handler rotation_handler ;
    Reset_Handler reset_handler ;

    Private() ;
    ~Private() ;
} ;

Canned_Viewer::Private::
Private()
    : home_transform(),
      root_frame(),
      scaling_frame(),
      inversion_frame(),
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
    super::peek_kernel().add_update_receiver(m->root_frame) ;

    m->root_frame.add(m->scaling_frame) ;
    m->scaling_frame.add(m->inversion_frame) ;
    m->inversion_frame.add(m->rotation_frame) ;

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
add_geom( engine::dim4::Geom & a )
{
    super::peek_draw_sender().add(a) ;
    super::peek_compute_sender().add(a) ;
    m->rotation_frame.add(a) ;
}

void
Canned_Viewer::
remove_geom( engine::dim4::Geom & a )
{
    super::peek_draw_sender().remove(a) ;
    super::peek_compute_sender().remove(a) ;
    m->rotation_frame.remove(a) ;
}

void
Canned_Viewer::
scaling( real gamma )
{
    m->scaling_frame.peek_transform().a(quat(gamma)) ;
}

real
Canned_Viewer::
scaling() const
{
    return realpart(m->scaling_frame.peek_transform().a()) ;
}

void
Canned_Viewer::
inversion( real gamma )
{
    m->inversion_frame.peek_transform().b(quat(-gamma)) ;
    m->inversion_frame.peek_transform().c(quat(gamma)) ;
}

real
Canned_Viewer::
inversion() const
{
    return realpart(m->inversion_frame.peek_transform().c()) ;
}

const engine::dim4::Transform &
Canned_Viewer::
home_transform() const
{
    return m->home_transform ;
}

void
Canned_Viewer::
home_transform( const engine::dim4::Transform & t )
{
    m->home_transform = t ;
}

const engine::dim4::Transform &
Canned_Viewer::
rotation() const
{
    return m->rotation_frame.peek_transform() ;
}

void
Canned_Viewer::
rotation( const quat & a,
          const quat & d )
{
    m->rotation_frame.peek_transform().assign(
        engine::dim4::Transform(
            a/abs(a),
            quat(0),
            quat(0),
            d/abs(d))) ;
}

void
Canned_Viewer::
stop_motion()
{
    m->rotation_handler.stop() ;
}

bool
Canned_Viewer::
slide() const
{
    return m->rotation_handler.slide() ;
}

void
Canned_Viewer::
slide( bool a )
{
    m->rotation_handler.slide(a) ;
}

}}} // namespace esve::viewers::dim4
