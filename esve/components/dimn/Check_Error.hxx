
#ifndef esve_components_dimn_Check_Error_hxx
#define esve_components_dimn_Check_Error_hxx

#include <esve/message/impl/Draw_Receiver.hxx>
#include <stdexcept>

namespace esve { namespace components { namespace dimn {

///
/// @class Check_Error esve/components/dimn/Check_Error.hxx
/// @brief Check and report OpenGL errors.
///
/// Calls glGetError() on each draw().  If an error is detected then
/// engine::dim3::Rendering_Error is thrown with an appropriate
/// description.
///

class Check_Error
    : virtual public message::impl::Draw_Receiver
{
public:
    Check_Error() ;
    ~Check_Error() ;

protected:
    void draw() ;

private:
    Check_Error( const Check_Error & ) ;
    Check_Error & operator=( const Check_Error & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

