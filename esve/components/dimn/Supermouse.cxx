
#include <esve/components/dimn/Supermouse_Handler.hxx>
#include <esve/components/dimn/Supermouse_Emitter.hxx>
#include <esve/components/dimn/Supermouse.hxx>
#include <esve/ui/base/Mouse_Handler.hxx>
#include <esve/kernel/Emitter.hxx>
#include <esve/message/impl/Handle_Node.hxx>
#include <bitset>
#include <cassert>

namespace esve { namespace components { namespace dimn {

using types::real ;
using types::pure ;

namespace {

class Supermouse_impl
    : public Supermouse
{
public:
    Supermouse_impl( const pure & position )
        : m_position(position),
          m_pushed() { }

    const pure & position() const
    {
        return m_position ;
    }

    bool pushed( Button a ) const
    {
        return m_pushed[a] ;
    }

    void position( pure a )
    {
        m_position = a ;
    }

    void pushed( Button a, bool value )
    {
        m_pushed[a] = value ;
    }

private:
    pure m_position ;
    std::bitset<NUM_BUTTONS> m_pushed ;
} ;

} // anon namespace

//////////////////////////////////////////////////////////////////

Supermouse::
Supermouse()
{
}

Supermouse::
~Supermouse()
{
}

//////////////////////////////////////////////////////////////////

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
//           Own_Mouse_Handler
//                  |
//                  |
//                  | handle_supermouse_*()
//                  |
//                 \|/
//                  * 
//           Supermouse_Handler
//
//

struct Supermouse_Handler::Private
{
    struct Own_Emitter
        : public kernel::Emitter
    {
        Own_Emitter()
            : Emitter() { }

        void add_encoder( message::Handle_Sender & a )
        {
            Emitter::add_encoder(a) ;
        }
    } ;

    struct Own_Mouse_Handler
        : public ui::base::Mouse_Handler
    {
        Supermouse_Handler::Private & m ;
        
        Own_Mouse_Handler( Supermouse_Handler::Private & m_ )
            : m(m_) { }

        bool handle_mouse_move( const Mouse & mouse )
        {
            m.supermouse.position(translate_mouse(mouse.position())) ;

            return m.outside.handle_supermouse_move(m.supermouse) ;
        }
        
        bool handle_mouse_push( Mouse_Handler::Button button,
                                const Mouse & mouse )
        {
            assert(int(button) < int(Supermouse::NUM_BUTTONS)) ;
            
            m.supermouse.position(translate_mouse(mouse.position())) ;

            m.supermouse.pushed(Supermouse::Button(button), true) ;
            
            return
                m.outside.handle_supermouse_push(
                    Supermouse::Button(button),
                    m.supermouse) ;
        }
        
        bool handle_mouse_release( Mouse_Handler::Button button,
                                   const Mouse & mouse )
        {
            assert(int(button) < int(Supermouse::NUM_BUTTONS)) ;
            
            m.supermouse.position(translate_mouse(mouse.position())) ;

            m.supermouse.pushed(Supermouse::Button(button), false) ;
            
            return
                m.outside.handle_supermouse_release(
                    Supermouse::Button(button),
                    m.supermouse) ;
        }
    } ;
    
    Supermouse_Handler & outside ;
    message::impl::Handle_Node handle_node ;
    Own_Emitter emitter ;
    Own_Mouse_Handler mouse_handler ;

    Supermouse_impl supermouse ;

    Private( Supermouse_Handler & outside_ )
        : outside(outside_),
          handle_node(),
          emitter(),
          mouse_handler(*this),
          supermouse(pure()) { }

    static pure translate_mouse( const ui::base::Mouse::Position & position )
    {
        // In mouse coordinates, positive y points down.
        // Change to regular coordinates.

        return pure(real(position.x),
                    -real(position.y),
                    0) ;
    }
} ;

Supermouse_Handler::
Supermouse_Handler()
    : m(new Private(*this))
{
    add_decoder(m->handle_node) ;
    m->emitter.add_encoder(m->handle_node) ;
    m->emitter.add_handler(m->mouse_handler) ;
}

Supermouse_Handler::
~Supermouse_Handler()
{
}

const Supermouse_Handler::Supermouse &
Supermouse_Handler::
supermouse() const
{
    return m->supermouse ;
}

//////////////////////////////////////////////////////////////////

// Supermouse_Emitter is not implemented

}}} // namespace esve::components::dimn
