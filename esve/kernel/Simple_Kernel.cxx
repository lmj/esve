
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/kernel/Simple_Kernel_impl.hxx>
#include <esve/message/Update_Sender.hxx>

namespace esve { namespace kernel {

Simple_Kernel::
Simple_Kernel()
    : m(new Simple_Kernel_impl())
{
}

Simple_Kernel::
~Simple_Kernel()
{
}

int
Simple_Kernel::
takeover()
{
    return m->main_driver.takeover() ;
}

void
Simple_Kernel::
add_emitter( kernel::Emitter & a )
{
    a.add_handler(m->cached_emitter_node) ;
}

void
Simple_Kernel::
remove_emitter( kernel::Emitter & a )
{
    a.remove_handler(m->cached_emitter_node) ;
}


void
Simple_Kernel::
add_uncached_emitter( kernel::Emitter & a )
{
    a.add_handler(m->uncached_emitter_node) ;
}

void
Simple_Kernel::
remove_uncached_emitter( kernel::Emitter & a )
{
    a.remove_handler(m->uncached_emitter_node) ;
}


void
Simple_Kernel::
add_handler( kernel::Handler & a )
{
    m->handler_node.add_handler(a) ;
}

void
Simple_Kernel::
remove_handler( kernel::Handler & a )
{
    m->handler_node.remove_handler(a) ;
}

void
Simple_Kernel::
remove_all_handlers()
{
    m->handler_node.remove_all_handlers() ;
}


void
Simple_Kernel::
add_update_receiver( message::Update_Receiver & a )
{
    m->update_node.add(a) ;
}

void
Simple_Kernel::
remove_update_receiver( message::Update_Receiver & a )
{
    m->update_node.remove(a) ;
}

void
Simple_Kernel::
remove_all_update_receivers()
{
    m->update_node.remove_all() ;
}

void
Simple_Kernel::
add_driver_handler( kernel::Handler & a )
{
    m->main_driver.add_handler(a) ;
}

void
Simple_Kernel::
remove_driver_handler( kernel::Handler & a )
{
    m->main_driver.remove_handler(a) ;
}

message::Tick_Sender &
Simple_Kernel::
peek_tick_sender()
{
    return m->main_driver.peek_tick_sender() ;
}

}} // namespace esve::kernel
