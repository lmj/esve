
#ifndef esve_engine_dim3_Make_Geom_hxx
#define esve_engine_dim3_Make_Geom_hxx

#include <esve/engine/dim3/Geom.hxx>
#include <esve/engine/dim3/Make_Frame.hxx>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Make_Geom esve/engine/dim3/Make_Geom.hxx
/// @brief Make a class into a Geom.
///
/// The target class most possess a compute() method in addition to
/// the draw() method required by Make_Frame.
///

template< typename T_Target >
class Make_Geom
    : public Make_Frame<T_Target, Geom>
{
private:
    typedef Make_Frame<T_Target, Geom> super ;

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
            typedef void (Make_Geom::*R)() ;
            R r = &Make_Geom::m_requirements_1 ;
            m_unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    Make_Geom( const Make_Geom & ) ;
    Make_Geom & operator=( const Make_Geom & ) ;

public:
    Make_Geom() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Geom( T_Arg & arg ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Geom( const T_Arg & arg ) ;

    ~Make_Geom() ;

protected:
    void compute() ;

    // draw() defined by Make_Frame
} ;

}}} // namespace esve::engine::dim3

#include <esve/engine/dim3/Make_Geom.template.cxx>

#endif


