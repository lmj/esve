#ifndef esve_components_dimn_Make_Draw_Receiver_hxx
#define esve_components_dimn_Make_Draw_Receiver_hxx

#include <esve/message/impl/Draw_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

/// @if details
///
/// @class Make_Draw_Receiver esve/components/dimn/Make_Draw_Receiver.hxx
/// @brief Make a class a draw() receiver (convenience).
///
/// The target class must have a (conventionally protected) draw()
/// method.
///
/// @endif

template< typename T_Target >
class Make_Draw_Receiver
    : virtual public message::impl::Draw_Receiver,
      public T_Target
{
private:
#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1()
    {
        T_Target::draw() ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Make_Draw_Receiver::*R)() ;
            R r = &Make_Draw_Receiver::m_requirements_1 ;
            m_unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    Make_Draw_Receiver( const Make_Draw_Receiver & ) ;
    Make_Draw_Receiver & operator=( const Make_Draw_Receiver & ) ;

public:
    /// Default constructor.
    Make_Draw_Receiver() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Draw_Receiver( T_Arg & arg ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Draw_Receiver( const T_Arg & arg ) ;

    ~Make_Draw_Receiver() ;

protected:
    void draw() ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Make_Draw_Receiver.template.cxx>

#endif

