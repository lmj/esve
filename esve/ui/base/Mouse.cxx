
#include <esve/ui/base/Mouse_Emitter.hxx>
#include <esve/ui/base/Mouse_Handler.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <bitset>

namespace esve { namespace ui { namespace base {

/////////////////////////////////////////////////////////
//
// Mouse_Handle_Args
//
/////////////////////////////////////////////////////////

namespace {

struct Mouse_Handle_Args : public message::Handle_Args
{
    enum ID
    {
        MOVE,
        PUSH,
        RELEASE
    } ;

    ID id ;
    Mouse::Button button ;
    Mouse::Position position ;

    Mouse_Handle_Args( ID id_,
                       Mouse::Button button_,
                       Mouse::Position position_ )
        : id(id_),
          button(button_),
          position(position_) { }

    Mouse_Handle_Args( const Mouse_Handle_Args & a )
        : Handle_Args(),
          id(a.id),
          button(a.button),
          position(a.position) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Mouse_Handle_Args(id,
                                      button,
                                      position)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        switch( id )
        {
        case MOVE:
            esve_report(MOVE) ;
            break ;
        case PUSH:
            esve_report(PUSH) ;
            break ;
        case RELEASE:
            esve_report(RELEASE) ;
            break ;
        }
        esve_report(button) ;
        esve_report(position.x) ;
        esve_report(position.y) ;
    }
#endif
} ;

} // anon namespace

/////////////////////////////////////////////////////////
//
// Mouse
//
/////////////////////////////////////////////////////////

Mouse::
Mouse()
{
}

Mouse::
~Mouse()
{
}

/////////////////////////////////////////////////////////
//
// Mouse_impl
//
/////////////////////////////////////////////////////////

namespace {

class Mouse_impl
    : public Mouse
{
public:
    Mouse_impl( const Mouse::Position & position )
        : m_position(position),
          m_pushed() { }

    const Position & position() const
    {
        return m_position ;
    }

    bool pushed( Button a ) const
    {
        return m_pushed[a] ;
    }

    void position( const Position & a )
    {
        m_position = a ;
    }
    void pushed( Button a, bool value )
    {
        m_pushed[a] = value ;
    }

private:
    Position m_position ;
    std::bitset<NUM_BUTTONS> m_pushed ;
} ;

} // anon namespace

/////////////////////////////////////////////////////////
//
// Mouse_Emitter
//
/////////////////////////////////////////////////////////

struct Mouse_Emitter::Private
    : public message::impl::Handle_Sender
{
    using Handle_Sender::send_handle ;
} ;

Mouse_Emitter::
Mouse_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

Mouse_Emitter::
~Mouse_Emitter()
{
}

bool
Mouse_Emitter::
emit_mouse_move( const Mouse::Position & position )
{
    return
        m->send_handle(Mouse_Handle_Args(
            Mouse_Handle_Args::MOVE,
            Mouse::Button(),
            position)) ;
}

bool
Mouse_Emitter::
emit_mouse_push( Mouse::Button button,
                 const Mouse::Position & position )
{
    return
        m->send_handle(Mouse_Handle_Args(
            Mouse_Handle_Args::PUSH,
            button,
            position)) ;
}

bool
Mouse_Emitter::
emit_mouse_release( Mouse::Button button,
                    const Mouse::Position & position )
{
    return
        m->send_handle(Mouse_Handle_Args(
            Mouse_Handle_Args::RELEASE,
            button,
            position)) ;
}

/////////////////////////////////////////////////////////
//
// Mouse_Handler
//
/////////////////////////////////////////////////////////

struct Mouse_Handler::Private
    : public message::impl::Handle_Receiver
{

    Mouse_Handler & outside ;
    Mouse_impl mouse ;

    Private( Mouse_Handler & outside_,
             const Mouse::Position & position )
        : outside(outside_),
          mouse(position) { }

    bool handle( const message::Handle_Args & ) ;
} ;

Mouse_Handler::
Mouse_Handler()
    : super(),
      m(new Private(*this, Mouse::Position(0, 0)))
{
    add_decoder(*m) ;
}

Mouse_Handler::
~Mouse_Handler()
{
}

const Mouse &
Mouse_Handler::
mouse() const
{
    return m->mouse ;
}

bool
Mouse_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Mouse_Handle_Args* mouse_args =
        dynamic_cast<const Mouse_Handle_Args*>(&generic_args) )
    {
        Mouse_Handle_Args args = *mouse_args ;

        mouse.position(args.position) ;

        switch( args.id )
        {
        case Mouse_Handle_Args::MOVE:
            {
                handled = outside.handle_mouse_move(mouse) ;
            }
            break ;

        case Mouse_Handle_Args::PUSH:
            if( mouse.pushed(args.button) )
            {
                // do nothing
            }
            else
            {
                mouse.pushed(args.button, true) ;
                handled = outside.handle_mouse_push(args.button,
                                                    mouse) ;
            }
            break ;

        case Mouse_Handle_Args::RELEASE:
            if( mouse.pushed(args.button) )
            {
                mouse.pushed(args.button, false) ;
                handled = outside.handle_mouse_release(args.button,
                                                       mouse) ;
            }
            else
            {
                // do nothing
            }
            break ;
        }
    }

    return handled ;
}

}}} // namespace esve::ui::base

