
#ifndef esve_engine_dim3_Rendering_Error_hxx
#define esve_engine_dim3_Rendering_Error_hxx

#include <stdexcept>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Rendering_Error esve/engine/dim3/Rendering_Error.hxx
/// @brief An OpenGL error.
///

struct Rendering_Error
    : public std::runtime_error
{
    Rendering_Error( const std::string & what ) ;
    ~Rendering_Error() throw() ;
} ;

}}} // namespace esve::engine::dim3

#endif

