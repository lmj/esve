
#include <esve/components/dimn/Draw_Compiler.hxx>
#include <esve/message/Draw_Sender_Delegator.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace components { namespace dimn {

using gl::gl ;

struct Draw_Compiler::Private
{
    bool compiled ;
    bool mark_for_recompile ;
    GLuint list_index ;

    Private()
        : compiled(false),
          mark_for_recompile(true),
          list_index(0) { }
} ;

Draw_Compiler::
Draw_Compiler()
    : super(),
      m(new Private())
{
}

Draw_Compiler::
~Draw_Compiler()
{
    if( m->compiled )
    {
        glDeleteLists(m->list_index, 1) ;
    }
}

void
Draw_Compiler::
draw_initialize()
{
    m->mark_for_recompile = true ;
}

void
Draw_Compiler::
send_draw()
{
    if( m->mark_for_recompile )
    {
        if( m->compiled )
        {
            glDeleteLists(m->list_index, 1) ;
        }
        
        m->list_index = glGenLists(1) ;
        m->compiled = true ;
        
        {
            gl::NewList sentry(m->list_index, GL_COMPILE_AND_EXECUTE) ;
            super::send_draw() ;
        }
        
        m->mark_for_recompile = false ;
    }
    else
    {
        glCallList(m->list_index) ;
    }
}

}}} // namespace esve::components::dimn
