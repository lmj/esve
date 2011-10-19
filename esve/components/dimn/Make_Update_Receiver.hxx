
#ifndef esve_components_dimn_Make_Update_Receiver_hxx
#define esve_components_dimn_Make_Update_Receiver_hxx

#include <esve/message/impl/Update_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @if details
///
/// @class Make_Update_Receiver esve/components/dimn/Make_Update_Receiver.hxx
/// @brief Make a class an update() receiver (convenience).
///
/// The target class must have a (conventionally public) update()
/// method and a (conventionally protected) update(double) method.
///
/// @endif
///

template< typename T_Target >
class Make_Update_Receiver
    : virtual public message::impl::Update_Receiver,
      public T_Target
{
private:
#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1()
    {
        T_Target::update() ;
        T_Target::update(double(1.0)) ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Make_Update_Receiver::*R)() ;
            R r = &Make_Update_Receiver::m_requirements_1 ;
            m_unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    Make_Update_Receiver( const Make_Update_Receiver & ) ;
    Make_Update_Receiver & operator=( const Make_Update_Receiver & ) ;
    
public:
    /// Default constructor.
    Make_Update_Receiver() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Update_Receiver( T_Arg & arg ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Update_Receiver( const T_Arg & arg ) ;

    ~Make_Update_Receiver() ;

protected:
    void update() ;
    void update( double dt ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Make_Update_Receiver.template.cxx>

#endif

