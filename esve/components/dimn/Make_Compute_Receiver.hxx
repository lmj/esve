
#ifndef esve_components_dimn_Make_Compute_Receiver_hxx
#define esve_components_dimn_Make_Compute_Receiver_hxx

#include <esve/message/impl/Compute_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

/// @if details
///
/// @class Make_Compute_Receiver esve/components/dimn/Make_Compute_Receiver.hxx
/// @brief Make a class a compute() receiver (convenience).
///
/// The target class must have a (conventionally protected) compute() method.
///
/// @endif

template< typename T_Target >
class Make_Compute_Receiver
    : virtual public message::impl::Compute_Receiver,
      public T_Target
{
private:
#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1()
    {
        T_Target::compute() ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Make_Compute_Receiver::*R)() ;
            R r = &Make_Compute_Receiver::m_requirements_1 ;
            m_unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    Make_Compute_Receiver( const Make_Compute_Receiver & ) ;
    Make_Compute_Receiver & operator=( const Make_Compute_Receiver & ) ;

public:
    /// Default Constructor.
    Make_Compute_Receiver() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Compute_Receiver( T_Arg & arg ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Compute_Receiver( const T_Arg & arg ) ;

    ~Make_Compute_Receiver() ;

protected:
    void compute() ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Make_Compute_Receiver.template.cxx>

#endif

