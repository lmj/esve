
#ifndef esve_kernel_Wake_State_Server_hxx
#define esve_kernel_Wake_State_Server_hxx

#include <esve/kernel/Kernel_Node.hxx>
#include <esve/kernel/Wake_State_Handler.hxx>
#include <esve/kernel/Wake_State_Emitter.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Wake_State_Server esve/kernel/Wake_State_Server.hxx
/// @brief Supervise the waking state.
///
/// A Wake_State_Server is both a kernel::Node, a Wake_State_Emitter,
/// and a Wake_State_Handler.
///
/// In response to a handle_check_awake() message:
///    -# As a Kernel_Node, it relays the message to its children.
///    -# If one or more children return true then it sends another
/// message, handle_wake(), otherwise it sends handle_sleep().
///    -# Multiple handle_wake()s in a row will not be sent, nor will
/// multiple handle_sleep()s.
///

//
// The three derivations result in this internal state:
//
//
//         Handler::to_decoders     (shared virtual base)
//                  |\                                            .
//                  | \                                           .
//                  |  +----------+                               .
//                  |              \                              .
//                  |               \                             .
//                  |                |
//                  |               \|/
//                  |                *
//                  |        Wake_State_Handler's decoder
//                  |
//                 \|/
//                  * 
//     Kernel_Node's decoder/encoder pass-through
//                  |
//                  |
//                  |
//                  |       Wake_State_Emitter's encoder
//                  |                  /
//                  |                 /
//                  |     +----------+
//                  |    /
//                  |   /
//                  |   |
//                 \|/ \|/
//                  *   *
//         Emitter::from_encoders   (shared virtual base)
//
//
//

class Wake_State_Server
    : public Kernel_Node,
      public Wake_State_Handler,
      public Wake_State_Emitter
{
public:
    Wake_State_Server() ;
    ~Wake_State_Server() ;

protected:
    bool handle_check_awake( bool currently_awake ) ;
    bool handle_wake() ;
    bool handle_sleep() ;

private:
    Wake_State_Server( const Wake_State_Server & ) ;
    Wake_State_Server & operator=( const Wake_State_Server & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

