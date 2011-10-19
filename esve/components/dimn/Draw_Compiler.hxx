#ifndef esve_components_dimn_Draw_Compiler_hxx
#define esve_components_dimn_Draw_Compiler_hxx

#include <esve/message/impl/Draw_Node.hxx>
#include <memory>
#include <esve/gl/gl.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Draw_Compiler esve/components/dimn/Draw_Compiler.hxx
/// @brief OpenGL display list.
///
/// On the first draw() message, all child Draw_Receiver objects are
/// compiled into the OpenGL display list.  Thereafter, the display
/// list is called instead of the children.
///
/// This class would be called Display_List were it not for the
/// potential confusion with the Display class.
///

class Draw_Compiler
    : public message::impl::Draw_Node
{
private:
    typedef message::impl::Draw_Node super ;

    Draw_Compiler( const Draw_Compiler & ) ;
    Draw_Compiler & operator=( const Draw_Compiler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
    
public:
    Draw_Compiler() ;

    ~Draw_Compiler() ;

protected:
    // override.
    void send_draw() ;

    /// Recompile the display list on next draw() message.
    void draw_initialize() ;
} ;

}}} // namespace esve::components::dimn

#endif

