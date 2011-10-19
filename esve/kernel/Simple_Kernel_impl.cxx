
#include <esve/kernel/Simple_Kernel_impl.hxx>
#include <esve/message/Update_Sender.hxx>
#include <esve/message/Tick_Sender.hxx>

namespace esve { namespace kernel {

Simple_Kernel_impl::
Simple_Kernel_impl()
    : main_driver(),
      cached_emitter_node(),
      uncached_emitter_node(),
      caching_server(),
      async_update_server(),
      wake_state_server(),
      handler_node(),
      sync_update_server(),
      update_node()
{
    ///////////////////////////////////////////
    // handle tree
    ///////////////////////////////////////////

    main_driver.add_handler(caching_server) ;
    cached_emitter_node.add_handler(caching_server) ;

    caching_server.add_handler(async_update_server) ;
    uncached_emitter_node.add_handler(async_update_server) ;

    async_update_server.add_handler(wake_state_server) ;

    wake_state_server.add_handler(sync_update_server) ;
    wake_state_server.add_handler(handler_node) ;

    ///////////////////////////////////////////
    // update tree
    ///////////////////////////////////////////

    async_update_server.add(update_node) ;
    sync_update_server.add(update_node) ;

    ///////////////////////////////////////////
    // tick tree
    ///////////////////////////////////////////

    main_driver.peek_tick_sender().add(sync_update_server) ;
}

Simple_Kernel_impl::
~Simple_Kernel_impl()
{
}

}} // namespace esve::kernel
