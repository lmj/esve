
#include <esve/components/dim4/Simple_Rotation_Handler.hxx>
#include <esve/components/dim4/Rotation_Handler.hxx>
#include <esve/kernel/Emitter.hxx>
#include <esve/message/impl/Handle_Node.hxx>
#include <cassert>

namespace esve { namespace components { namespace dim4 {

using types::real ;

//          
//          
//             to_decoders   (located in Handler virtual base)
//                  |
//                  |
//                  | handle()  (raw handle)
//                  |
//                 \|/
//                  * 
//             Handle_Node
//                  |
//                  |
//                  | handle()  (raw handle)
//                  |
//                 \|/
//                  * 
//        Own_Emitter::from_encoders
//                  |
//                  |
//                  | handle()  (raw handle)
//                  |
//                 \|/
//                  * 
//             Own_Emitter
//                  |
//                  |
//                  | handle_*()
//                  |
//                 \|/
//                  * 
//           Rotation_Handler
//
//

struct Simple_Rotation_Handler::Private
{
    struct Own_Emitter
        : public kernel::Emitter
    {
        using Emitter::add_encoder ;
    } ;

    message::impl::Handle_Node handle_node ;
    Own_Emitter emitter ;
    Rotation_Handler rotation_handler ;

    Simple_Rotation_Handler::Mapping simple_mapping ;
    bool slide ;

    Private( engine::dim4::Transform & ) ;
    ~Private() ;
} ;

Simple_Rotation_Handler::Private::
Private( engine::dim4::Transform & transform )
    : handle_node(),
      emitter(),
      rotation_handler(transform),
      simple_mapping(Simple_Rotation_Handler::LONGLAT),
      slide(false)
{
}

Simple_Rotation_Handler::Private::
~Private()
{
}

Simple_Rotation_Handler::
Simple_Rotation_Handler( engine::dim4::Transform & transform )
    : m(new Private(transform))
{
    add_decoder(m->handle_node) ;
    m->emitter.add_encoder(m->handle_node) ;
    m->emitter.add_handler(m->rotation_handler) ;

    mapping(m->simple_mapping) ;
}

Simple_Rotation_Handler::
~Simple_Rotation_Handler()
{
}

void
Simple_Rotation_Handler::
mapping( Mapping mapping )
{
    m->simple_mapping = mapping ;

    if( m->simple_mapping == LONGLAT )
    {
        m->rotation_handler.mapping(
            components::dimn::Supermouse::LEFT,
            Rotation_Handler::ROTATE_K_TOWARD_U) ;
        m->rotation_handler.mapping(
            components::dimn::Supermouse::MIDDLE,
            Rotation_Handler::DOUBLE_ROTATE_IJ1K) ;
        m->rotation_handler.mapping(
            components::dimn::Supermouse::RIGHT,
            Rotation_Handler::ROTATE_1_TOWARD_U) ;
    }
    else if( m->simple_mapping == HOPF )
    {
        m->rotation_handler.mapping(
            components::dimn::Supermouse::LEFT,
            Rotation_Handler::LEFT_HOPF_ROTATION) ;
        m->rotation_handler.mapping(
            components::dimn::Supermouse::MIDDLE,
            Rotation_Handler::RIGHT_HOPF_ROTATION) ;
        m->rotation_handler.mapping(
            components::dimn::Supermouse::RIGHT,
            Rotation_Handler::NEG_RIGHT_HOPF_ROTATION) ;
    }

    if( m->slide )
    {
        m->rotation_handler.mapping(
            components::dimn::Supermouse::RIGHT,
            Rotation_Handler::DOUBLE_ROTATE_1IJK) ;
        m->rotation_handler.basis(
            components::dimn::Supermouse::RIGHT,
            m->rotation_handler.active_transform()) ;
    }
    else
    {
        m->rotation_handler.basis(
            components::dimn::Supermouse::RIGHT,
            engine::dim4::Transform::IDENTITY) ;
    }
}

bool
Simple_Rotation_Handler::
slide() const
{
    return m->slide ;
}

void
Simple_Rotation_Handler::
slide( bool a )
{
    m->slide = a ;
    mapping(m->simple_mapping) ;
}

Simple_Rotation_Handler::Mapping
Simple_Rotation_Handler::
mapping() const
{
    return m->simple_mapping ;
}

void
Simple_Rotation_Handler::
active_transform( engine::dim4::Transform & a )
{
    m->rotation_handler.active_transform(a) ;
}

const engine::dim4::Transform &
Simple_Rotation_Handler::
active_transform() const
{
    return m->rotation_handler.active_transform() ;
}

real
Simple_Rotation_Handler::
sensitivity() const
{
    return m->rotation_handler.sensitivity() ;
}

void
Simple_Rotation_Handler::
sensitivity( real a )
{
    m->rotation_handler.sensitivity(a) ;
}

void
Simple_Rotation_Handler::
stop()
{
    m->rotation_handler.stop() ;
}

void
Simple_Rotation_Handler::
update()
{
    m->rotation_handler.update() ;
}

void
Simple_Rotation_Handler::
update( double dt )
{
    m->rotation_handler.update(dt) ;
}

bool
Simple_Rotation_Handler::
handle_check_awake( bool )
{
    // handled by translator
    return false ;
}

}}} // namespace esve::components::dim4
