
#include <esve/ui/base/Keyboard.hxx>
#include <esve/ui/base/Keyboard_Emitter.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <bitset>

namespace esve { namespace ui { namespace base {

namespace {

struct Keyboard_Handle_Args : public message::Handle_Args
{
    enum ID
    {
        PUSH,
        RELEASE,
        CLEAR
    } ;

    ID id ;
    Keyboard::Key key ;

    Keyboard_Handle_Args( ID id_,
                          Keyboard::Key key_ )
        : id(id_),
          key(key_) { }

    Keyboard_Handle_Args( const Keyboard_Handle_Args & a )
        : Handle_Args(),
          id(a.id),
          key(a.key) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Keyboard_Handle_Args(id,
                                         key)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        switch( id )
        {
        case PUSH:
            esve_report(PUSH) ;
            break ;
        case RELEASE:
            esve_report(RELEASE) ;
            break ;
        case CLEAR:
            esve_report(CLEAR) ;
            break ;
        }
        esve_report(char(key)) ;
    }
#endif
} ;

} // anon namespace

////////////////////////////////////////////////////////////////

Keyboard::
Keyboard()
{
}

Keyboard::
~Keyboard()
{
}

////////////////////////////////////////////////////////////////

namespace {

class Keyboard_impl
    : public Keyboard
{
public:
    Keyboard_impl()
        : m_pushed() { }

    bool pushed( Key a ) const
    {
        return m_pushed[a] ;
    }

    void pushed( Key a, bool value )
    {
        m_pushed[a] = value ;
    }

private:
    std::bitset<NUM_KEYS> m_pushed ;
} ;

} // anon namespace

////////////////////////////////////////////////////////////////

struct Keyboard_Handler::Private
    : public message::impl::Handle_Receiver
{
    Keyboard_Handler & outside ;
    Keyboard_impl keyboard ;

    Private( Keyboard_Handler & outside_ )
        : outside(outside_),
          keyboard() { }

    bool handle( const message::Handle_Args & ) ;
} ;

Keyboard_Handler::
Keyboard_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

Keyboard_Handler::
~Keyboard_Handler()
{
}

const Keyboard &
Keyboard_Handler::
keyboard() const
{
    return m->keyboard ;
}

bool
Keyboard_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const Keyboard_Handle_Args* key_args =
        dynamic_cast<const Keyboard_Handle_Args*>(&generic_args) )
    {
        Keyboard_Handle_Args args = *key_args ;

        switch( args.id )
        {
        case Keyboard_Handle_Args::PUSH:
            if( keyboard.pushed(args.key) )
            {
                // do nothing
            }
            else
            {
                keyboard.pushed(args.key, true) ;
                handled = outside.handle_key_push(args.key, keyboard) ;
            }
            break ;

        case Keyboard_Handle_Args::RELEASE:
            if( keyboard.pushed(args.key) )
            {
                keyboard.pushed(args.key, false) ;
                handled = outside.handle_key_release(args.key,
                                                   keyboard) ;
            }
            else
            {
                // do nothing
            }
            break ;

        case Keyboard_Handle_Args::CLEAR:
            {
                for( Keyboard::Key key = Keyboard::Key(0) ;
                     key != Keyboard::NUM_KEYS ;
                     key = Keyboard::Key(key + 1) )
                {
                    if( keyboard.pushed(key) )
                    {
                        keyboard.pushed(key, false) ;
                        handled |=
                            outside.handle_key_release(key, keyboard) ;
                    }
                }
            }
            break ;
        }
    }

    return handled ;
}

////////////////////////////////////////////////////////////////

struct Keyboard_Emitter::Private
    : public message::impl::Handle_Sender
{
    using Handle_Sender::send_handle ;
} ;

Keyboard_Emitter::
Keyboard_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

Keyboard_Emitter::
~Keyboard_Emitter()
{
}

bool
Keyboard_Emitter::
emit_key_push( Keyboard::Key key )
{
    return
        m->send_handle(Keyboard_Handle_Args(
            Keyboard_Handle_Args::PUSH,
            key)) ;
}

bool
Keyboard_Emitter::
emit_key_release( Keyboard::Key key )
{
    return
        m->send_handle(Keyboard_Handle_Args(
            Keyboard_Handle_Args::RELEASE,
            key)) ;
}

bool
Keyboard_Emitter::
emit_key_release_all()
{
    return
        m->send_handle(Keyboard_Handle_Args(
            Keyboard_Handle_Args::CLEAR,
            Keyboard::Key())) ;
}

}}} // namespace esve::ui::base

