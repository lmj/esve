
#include <esve/engine/dim3/Rendering_Error.hxx>

namespace esve { namespace engine { namespace dim3 {

Rendering_Error::
Rendering_Error( const std::string & what )
    : std::runtime_error("OpenGL error: " + what)
{
}

Rendering_Error::
~Rendering_Error() throw()
{
}

}}} // namespace esve::engine::dim3
