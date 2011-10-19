#ifndef esve_engine_dim3_Make_Frame_hxx
#define esve_engine_dim3_Make_Frame_hxx

#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/message/impl/Draw_Receiver.hxx>
#include <esve/util/misc.hxx>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Make_Frame esve/engine/dim3/Make_Frame.hxx
/// @brief Make a class into a Frame.
///
/// The target class must possess a draw() method.
///
/// The target class becomes a message::Draw_Receiver.  Make_Frame works by
/// overriding the target class' draw() method to set the OpenGL
/// matrix just before drawing the object.
///

template< typename T_Target, typename T_Frame = impl::Frame >
class Make_Frame
    : virtual public message::impl::Draw_Receiver,
      public T_Target,
      public T_Frame
{
private:
#if !defined(NDEBUG)
    void m_requirements_1()
    {
        T_Target::draw() ;
        engine::dim3::Frame* r = util::misc::implicit_cast<T_Frame*>(this) ;
        util::misc::unused(r) ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Make_Frame::*R)() ;
            R r = &Make_Frame::m_requirements_1 ;
            util::misc::unused(r) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)
    
    Make_Frame( const Make_Frame & ) ;
    Make_Frame & operator=( const Make_Frame & ) ;

public:
    /// Default constructor.
    Make_Frame() ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Frame( T_Arg & arg ) ;

    /// Construct T_Target with an arbitrary argument.
    template< typename T_Arg >
    Make_Frame( const T_Arg & arg ) ;

    ~Make_Frame() ;

protected:
    /// Set the transform then call T_Target's draw().
    void draw() ;
} ;

}}} // namespace esve::engine::dim3

#include <esve/engine/dim3/Make_Frame.template.cxx>

#endif

