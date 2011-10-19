
#ifndef esve_kernel_Caching_Node_hxx
#define esve_kernel_Caching_Node_hxx

#include <esve/kernel/Handler.hxx>
#include <esve/kernel/Emitter.hxx>
#include <esve/message/Active_State.hxx>
#include <memory>

namespace esve { namespace kernel {

///
/// @class Caching_Node esve/kernel/Caching_Node.hxx
/// @brief Cache handle_*() messages.
///

class Caching_Node
    : virtual public Handler,
      virtual public Emitter
{
public:
    /// Construct with caching state on or off.
    Caching_Node( bool caching ) ;

    /// Start caching handle_*() messages.
    virtual void start_caching() ;

    ///
    /// @brief Emit the cache; stop caching handle_*() messages.
    ///
    /// @return The or'd result of the emitted handle_*() return values.
    ///
    virtual bool stop_caching() ;

    ///
    /// @brief Throw away the contents of the cache; do not emit
    /// anything.
    ///
    /// Does not affect caching state.
    ///
    virtual void discard_cache() ;

    /// Is caching on?
    virtual bool caching() const ;

    ///@{
    bool active() const ;
    void active( bool ) ;
    ///@}

    /// The cache is emitted upon destruction.
    ~Caching_Node() ;

private:
    Caching_Node( const Caching_Node & ) ;
    Caching_Node & operator=( const Caching_Node & ) ;
    
    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}} // namespace esve::kernel

#endif

