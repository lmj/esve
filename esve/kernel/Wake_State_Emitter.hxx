
#ifndef esve_kernel_Wake_State_Emitter_hxx
#define esve_kernel_Wake_State_Emitter_hxx

#include <esve/kernel/Emitter.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Wake_State_Emitter esve/kernel/Wake_State_Emitter.hxx
/// @brief Send handle_check_awake(), handle_wake(), handle_sleep().
///
/// @see Wake_State_Handler
///

class Wake_State_Emitter
    : virtual public Emitter
{
public:
    Wake_State_Emitter() ;
    ~Wake_State_Emitter() ;

protected:
    /// Ask whoever's listening if they want to be awake.
    virtual bool emit_check_awake() ;

    /// Tell folks to go to sleep.
    virtual bool emit_sleep() ;

    /// Tell folks to go to wake up.
    virtual bool emit_wake() ;

private:
    Wake_State_Emitter( const Wake_State_Emitter & ) ;
    Wake_State_Emitter & operator=( const Wake_State_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

