
#ifndef esve_kernel_Simple_Kernel_impl_hxx
#define esve_kernel_Simple_Kernel_impl_hxx

#include <esve/kernel/Main_Driver.hxx>
#include <esve/kernel/Caching_Server.hxx>
#include <esve/kernel/Async_Update_Server.hxx>
#include <esve/kernel/Wake_State_Server.hxx>
#include <esve/kernel/Sync_Update_Server.hxx>
#include <esve/message/impl/Update_Node.hxx>

namespace esve { namespace kernel {

///
/// @class Simple_Kernel_impl esve/kernel/Simple_Kernel_impl.hxx
/// @brief An example application driver.
///
/// This is a starting configuration for implementers building an
/// application from scatch.  Of course, one may have any number of
/// servers and nodes, depending on the size and complexity of the
/// application; this is just an example.
///
/// The setup looks like this:
/// @verbatim
///
/// handle tree:
///
///
/// cached_emitter_node       main_driver
///           \                    |
///            \                   |
///             \                  |
///              +-------+         | handle_driver_start()
///                       \        | handle_driver_check_finished()
///                        \       | handle_driver_finish()
///              handle_*() \      | handle_check_awake()
///                          \     |
///                          |     |
///                         \|/   \|/
///                          *     *
/// uncached_emitter_node    caching_server
///            \                   |
///             \                  |
///              +-------+         |
///                       \        |
///                        \       | handle_*()  (pass-through)
///              handle_*() \      |
///                          \     |
///                          |     |
///                         \|/   \|/
///                          *     *
///                       async_update_server
///                                |
///                                |
///                                |
///                                |
///                                | handle_*()  (pass-through)
///                                |
///                                |
///                                |
///                               \|/
///                                *
///                        wake_state_server
///                               /|
///                              / |
///                     +-------+  |
///                    /           |
///     handle_wake() /            | handle_*()  (pass-through)
///                  /             |
///                 /              |
///                |               |
///               \|/             \|/
///                *               *
///    sync_update_server     handler_node
///
///
///__________________________________________________________________________
///
/// update tree:
///
///
///           async_update_server     sync_update_server
///                       \                /
///                        \              /
///                         \            /
///                          \          /
///                           \        /
///                            \      /
///                             |    |
///                            \|/  \|/
///                             *    *
///                           update_node
///
///__________________________________________________________________________
///
/// tick tree:
///
///                           main_driver
///                                |
///                                |
///                                |
///                                | tick()
///                                |
///                                |
///                               \|/
///                                *
///                        sync_update_server
///
/// @endverbatim
///

struct Simple_Kernel_impl
{
    /// See diagram.
    kernel::Main_Driver main_driver ;

    /// See diagram.
    kernel::Kernel_Node cached_emitter_node ;

    /// See diagram.
    kernel::Kernel_Node uncached_emitter_node ;

    /// See diagram.
    kernel::Caching_Server caching_server ;

    /// See diagram.
    kernel::Async_Update_Server async_update_server ;

    /// See diagram.
    kernel::Wake_State_Server wake_state_server ;

    /// See diagram.
    kernel::Kernel_Node handler_node ;

    /// See diagram.
    kernel::Sync_Update_Server sync_update_server ;

    /// See diagram.
    message::impl::Update_Node update_node ;

    Simple_Kernel_impl() ;
    ~Simple_Kernel_impl() ;
} ;

}} // namespace esve::kernel

#endif

