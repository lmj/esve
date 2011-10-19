
#include <esve/engine/dim3/Make_Frame.hxx>
#include <esve/engine/dim3/transform_util.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace engine { namespace dim3 {

using gl::gl ;

template< typename T_Target, typename T_Frame >
Make_Frame<T_Target, T_Frame>::
Make_Frame()
    : Draw_Receiver(),
      T_Target(),
      T_Frame()
{
}

template< typename T_Target, typename T_Frame >
template< typename T_Arg >
Make_Frame<T_Target, T_Frame>::
Make_Frame( T_Arg & arg )
    : Draw_Receiver(),
      T_Target(arg),
      T_Frame()
{
}

template< typename T_Target, typename T_Frame >
template< typename T_Arg >
Make_Frame<T_Target, T_Frame>::
Make_Frame( const T_Arg & arg )
    : Draw_Receiver(),
      T_Target(arg),
      T_Frame()
{
}

template< typename T_Target, typename T_Frame >
Make_Frame<T_Target, T_Frame>::
~Make_Frame()
{
}

template< typename T_Target, typename T_Frame >
void
Make_Frame<T_Target, T_Frame>::
draw()
{
    GLfloat glmat[16] ;

    transform_util::build_matrix(T_Frame::world_transform(), glmat) ;

    {
        gl::PushMatrix sentry ;
        glMultMatrixf(glmat) ;
        T_Target::draw() ;
    }
}

}}} // namespace esve::engine::dim3
