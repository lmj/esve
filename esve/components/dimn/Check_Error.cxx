
#include <esve/components/dimn/Check_Error.hxx>
#include <esve/engine/dim3/Rendering_Error.hxx>
#include <esve/gl/gl.hxx>
#include <esve/gl/glu.hxx>
#include <sstream>

namespace esve { namespace components { namespace dimn {

Check_Error::
Check_Error()
    : Draw_Receiver()
{
}

Check_Error::
~Check_Error()
{
}

void
Check_Error::
draw()
{
    GLenum error = glGetError() ;

    if( error != GL_NO_ERROR )
    {
        std::ostringstream out ;
        out << gluErrorString(error) ;
        throw engine::dim3::Rendering_Error(out.str()) ;
    }
}

}}} // namespace esve::components::dimn
