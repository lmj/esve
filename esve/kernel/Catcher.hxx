
#ifndef esve_kernel_Catcher_hxx
#define esve_kernel_Catcher_hxx

namespace std { class exception ; }

namespace esve { namespace kernel {

///
/// @class Catcher esve/kernel/Catcher.hxx
/// @brief Catch exceptions from system entry points.
///

class Catcher
{
public:
    typedef void (*Catch_Function)( Catcher &, std::exception & ) ;

    ///@{
    /// @brief Catch exceptions from system entry points.
    virtual Catch_Function catch_function() const = 0 ;
    virtual void catch_function( Catch_Function ) = 0 ;
    ///@}

    virtual ~Catcher() = 0 ;

protected:
    Catcher() ;

private:
    Catcher( const Catcher & ) ;
    Catcher & operator=( const Catcher & ) ;
} ;

}} // namespace esve::kernel

#endif

