
#include <esve/kernel/Main_Driver.hxx>
#include <esve/message/impl/Tick_Sender.hxx>
#include <FL/Fl.H>
#include <list>

namespace {

typedef void (*Startup_Hook)() ;
typedef std::list<Startup_Hook> Startup_Hooks ;
Startup_Hooks g_startup_hooks ;

} // anon namespace

namespace esve { namespace kernel {

void private__add_startup_hook( Startup_Hook hook )
{
    g_startup_hooks.push_back(hook) ;
}

void private__remove_startup_hook( Startup_Hook hook )
{
    g_startup_hooks.remove(hook) ;
}

struct Main_Driver::Private
{
    struct Own_Tick_Sender : public message::impl::Tick_Sender
    {
        using message::impl::Tick_Sender::call_send_tick ;
    } ;

    struct Sentry
    {
        Main_Driver::Private & m ;
        
        Sentry( Main_Driver::Private & m_ )
            : m(m_)
        {
            m.outside.emit_driver_start() ;
        }

        ~Sentry()
        {
            m.outside.emit_driver_finish() ;
        }
    } ;

    kernel::Main_Driver & outside ;
    Own_Tick_Sender tick_sender ;

    Private( kernel::Main_Driver & outside_ )
        : outside(outside_),
          tick_sender() { }
} ;

Main_Driver::
Main_Driver()
    : m(new Private(*this))
{
}

Main_Driver::
~Main_Driver()
{
}

int
Main_Driver::
takeover()
{
    for( Startup_Hooks::iterator i = g_startup_hooks.begin() ;
         i != g_startup_hooks.end() ;
         ++i )
    {
        (*i)() ;
    }
    
    Private::Sentry sentry(*m) ;

    for(;;)
    {
        if( emit_driver_check_finished() )
        {
            return 0 ;
        }

        if( emit_check_awake() )
        {
            while( Fl::check() )
            {
                if( emit_driver_check_finished() )
                {
                    return 0 ;
                }

                Private::Own_Tick_Sender::call_send_tick(peek_tick_sender()) ;

                if( !emit_check_awake() )
                {
                    break ;
                }
            }
        }
        else
        {
            while( Fl::wait() )
            {
                if( emit_driver_check_finished() )
                {
                    return 0 ;
                }

                if( emit_check_awake() )
                {
                    break ;
                }
            }
        }
    }

    return 0 ;
}

message::Tick_Sender &
Main_Driver::
peek_tick_sender()
{
    return m->tick_sender ;
}

}} // namespace esve::kernel

