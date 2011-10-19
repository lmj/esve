
#include <esve/kernel/Sync_Update_Sender.hxx>
#include <esve/message/Update_Sender.hxx>
#include <esve/util/crosstime.hxx>

namespace esve { namespace kernel {

using util::crosstime::crosstime_t ;
using util::crosstime::CROSSTIME_CLOCKS_PER_SEC ;
using util::crosstime::crosstime ;

struct Sync_Update_Sender::Private
{
    struct Sentry
    {
        const crosstime_t current_clocks ;
        Sync_Update_Sender::Private & m ;

        Sentry( crosstime_t current_clocks_,
              Sync_Update_Sender::Private & m_ )
            : current_clocks(current_clocks_),
              m(m_) { }

        ~Sentry()
        {
            m.previous_clocks = current_clocks ;
        }
    } ;
    
    bool initialized ;
    crosstime_t previous_clocks ;
    crosstime_t starting_clocks ;
    double dt ;
    double current_time ;

    Private()
        : initialized(false),
          previous_clocks(0),
          starting_clocks(crosstime()),
          dt(0),
          current_time(0) { }
} ;

Sync_Update_Sender::
Sync_Update_Sender()
    : m(new Private())
{
}

Sync_Update_Sender::
~Sync_Update_Sender()
{
}

void
Sync_Update_Sender::
reset()
{
    m->initialized = false ;
}

void
Sync_Update_Sender::
tick()
{
    // begin a synchronization round.

    const crosstime_t current_clocks = crosstime() ;

    if( !m->initialized )
    {
        m->previous_clocks = current_clocks ;
        m->initialized = true ;
    }

    m->current_time =
        double(current_clocks - m->starting_clocks)
        /
        CROSSTIME_CLOCKS_PER_SEC ;

    m->dt =
        double(current_clocks - m->previous_clocks)
        /
        CROSSTIME_CLOCKS_PER_SEC ;

    {
        Private::Sentry sentry(current_clocks, *m) ;
        Update_Sender::send_update(m->dt) ;
    }
}

}} // namespace esve::kernel
