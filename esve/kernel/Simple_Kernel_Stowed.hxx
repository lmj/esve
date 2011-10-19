
#ifndef esve_kernel_Simple_Kernel_Stowed_hxx
#define esve_kernel_Simple_Kernel_Stowed_hxx

namespace esve { namespace kernel {

class Simple_Kernel ;

///
/// @class Simple_Kernel_Stowed esve/kernel/Simple_Kernel_Stowed.hxx
/// @brief Stowed kernel.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///

class Simple_Kernel_Stowed
{
public:
    ///@{
    /// @brief Peek at the kernel.
    virtual Simple_Kernel & peek_kernel() = 0 ;
    ///@}

    virtual ~Simple_Kernel_Stowed() = 0 ;

protected:
    Simple_Kernel_Stowed() ;

private:
    Simple_Kernel_Stowed( const Simple_Kernel_Stowed & ) ;
    Simple_Kernel_Stowed & operator=( const Simple_Kernel_Stowed & ) ;
} ;

}} // namespace esve::kernel

#endif

