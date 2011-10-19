//
// Exception-safe OpenGL state changes.
//

#ifndef esve_gl_gl_hxx
#define esve_gl_gl_hxx

#ifdef WIN32
#include <windows.h>
#endif

#ifndef APIENTRY
#if defined(__CYGWIN__)
#define APIENTRY __attribute__ ((__stdcall__))
#else
#define APIENTRY
#endif
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace esve { namespace gl {

struct gl
{
    class Begin
    {
    public:
        explicit Begin( GLenum mode )
        {
            glBegin(mode) ;
        }
        
        ~Begin()
        {
            glEnd() ;
        }

    private:
        Begin( const Begin & ) ;
        Begin & operator=( const Begin & ) ;
    } ;

    class PushAttrib
    {
    public:
        explicit PushAttrib( GLbitfield mask )
        {
            glPushAttrib(mask) ;
        }
        
        ~PushAttrib()
        {
            glPopAttrib() ;
        }

    private:
        PushAttrib( const PushAttrib & ) ;
        PushAttrib & operator=( const PushAttrib & ) ;
    } ;

    class PushClientAttrib
    {
    public:
        explicit PushClientAttrib( GLbitfield mask )
        {
            glPushClientAttrib(mask) ;
        }
        
        ~PushClientAttrib()
        {
            glPopClientAttrib() ;
        }

    private:
        PushClientAttrib( const PushClientAttrib & ) ;
        PushClientAttrib & operator=( const PushClientAttrib & ) ;
    } ;

    class PushMatrix
    {
    public:
        PushMatrix()
        {
            glPushMatrix() ;
        }
        
        ~PushMatrix()
        {
            glPopMatrix() ;
        }

    private:
        PushMatrix( const PushMatrix & ) ;
        PushMatrix & operator=( const PushMatrix & ) ;
    } ;

    class MatrixMode
    {
    public:
        explicit MatrixMode( GLenum mode )
        {
            glMatrixMode(mode) ;
        }
    
        ~MatrixMode()
        {
            glMatrixMode(GL_MODELVIEW) ;
        }

    private:
        MatrixMode( const MatrixMode & ) ;
        MatrixMode & operator=( const MatrixMode & ) ;
    } ;
            
    class NewList
    {
    public:
        NewList( GLuint list, GLenum mode )
        {
            glNewList(list, mode) ;
        }
        
        ~NewList()
        {
            glEndList() ;
        }

    private:
        NewList( const NewList & ) ;
        NewList & operator=( const NewList & ) ;
    } ;

    class PushName
    {
    public:
        explicit PushName( GLuint name )
        {
            glPushName(name) ;
        }
        
        ~PushName()
        {
            glPopName() ;
        }

    private:
        PushName( const PushName & ) ;
        PushName & operator=( const PushName & ) ;
    } ;
} ;

}} // namespace esve::gl

#endif

