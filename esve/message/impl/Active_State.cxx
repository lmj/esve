
#include <esve/message/impl/Active_State.hxx>

namespace esve { namespace message { namespace impl {

struct Active_State::Private
{
    bool active ;

    Private()
        : active(true) { }
} ;

Active_State::
Active_State()
    : m(new Private())
{
}

Active_State::
~Active_State()
{
}

void
Active_State::
active( bool a )
{
    m->active = a ;
}

bool
Active_State::
active() const
{
    return m->active ;
}

}}} // namespace esve::message::impl
