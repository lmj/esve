#ifndef esve_kernel_Driver_Emitter_hxx
#define esve_kernel_Driver_Emitter_hxx

#include <esve/kernel/Emitter.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Driver_Emitter esve/kernel/Driver_Emitter.hxx
/// @brief Send handle_driver_*() messages.
///
/// @see Driver_Handler
///

class Driver_Emitter
    : virtual public Emitter
{
public:
    ~Driver_Emitter() ;

protected:
    Driver_Emitter() ;

    /// @brief You have somehow figured out that we have entered a
    /// driving loop; send that information.
    virtual bool emit_driver_start() ;

    /// @brief Someone has given you the power to end a driving loop;
    /// ask others if they wish to end it.
    virtual bool emit_driver_check_finished() ;

    /// @brief You have somehow figured out that the driving loop is
    /// about to exit; send that information.
    virtual bool emit_driver_finish() ;

private:
    Driver_Emitter( const Driver_Emitter & ) ;
    Driver_Emitter & operator=( const Driver_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

