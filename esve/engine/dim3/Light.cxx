
#include <esve/engine/dim3/Light.hxx>
#include <esve/engine/dim3/impl/Frame_Stowed.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dim3/transform_util.hxx>
#include <esve/engine/dimn/Materials.hxx>
#include <esve/gl/gl.hxx>
#include <cassert>
#include <sstream>

namespace esve { namespace engine { namespace dim3 {

using gl::gl ;

const GLfloat LIGHT_ORIGIN[4] = { 0, 0, 0, 1 } ;

namespace {

GLenum index2id( GLint index )
{
    switch( index )
    {
    case 0:
        return GL_LIGHT0 ;
    case 1:
        return GL_LIGHT1 ;
    case 2:
        return GL_LIGHT2 ;
    case 3:
        return GL_LIGHT3 ;
    case 4:
        return GL_LIGHT4 ;
    case 5:
        return GL_LIGHT5 ;
    case 6:
        return GL_LIGHT6 ;
    case 7:
        return GL_LIGHT7 ;
    default:
        assert(!"More lights than light enums") ;
    }

    return GLenum(-1) ;
}

std::string to_string( int i )
{
    std::ostringstream out ;
    out << i ;
    return out.str() ;
}

} // anon namespace

Light::
Too_Many_Lights_Error::
Too_Many_Lights_Error( int n )
    : Rendering_Error("Maximum number of lights ("
                      +
                      to_string(n)
                      +
                      ") exceeded"),
      max_lights(n)
{
}

Light::
Too_Many_Lights_Error::
~Too_Many_Lights_Error() throw()
{
}

struct Light::Private
{
    GLint max_lights ;
    engine::dimn::Materials materials ;
    impl::Frame_Stowed frame_stowed ;

    Private( Light & outside_ )
        : max_lights(0),
          materials(),
          frame_stowed(outside_) { }
} ;

Light::
Light()
    : m(new Private(*this))
{
}

Light::
~Light()
{
}

void
Light::
send_draw()
{
    if( m->max_lights == 0 )
    {
        // assume the same answer for all OpenGL contexts
        glGetIntegerv(GL_MAX_LIGHTS, &m->max_lights) ;
    }
    
    GLenum light_id = GLenum(0) ;
        
    {
        GLint i = 0 ;
        for( ; i != m->max_lights ; ++i )
        {
            if( glIsEnabled(index2id(i)) == GL_FALSE )
            {
                light_id = index2id(i) ;
                break ;
            }
        }

        if( i == m->max_lights )
        {
            throw Too_Many_Lights_Error(int(m->max_lights)) ;
        }
    }
        
    {
        GLfloat glmat[16] ;
        
        transform_util::build_matrix(
            // hook!
            peek_frame().world_transform(),
            glmat) ;
        
        {
            gl::PushMatrix sentry ;
            glMultMatrixf(glmat) ;
            glLightfv(light_id, GL_POSITION, LIGHT_ORIGIN) ;
        }
    }
    
    {
        gl::PushAttrib sentry(GL_LIGHTING_BIT) ;
        glEnable(light_id) ;
        
        glLightfv(light_id,
                  GL_AMBIENT,
                  // hook!
                  peek_materials().ambient().data()) ;
        
        glLightfv(light_id,
                  GL_DIFFUSE,
                  // hook!
                  peek_materials().diffuse().data()) ;
        
        glLightfv(light_id,
                  GL_SPECULAR,
                  // hook!
                  peek_materials().specular().data()) ;
    
        super::send_draw() ;
    }
}

const engine::dimn::Materials &
Light::
peek_materials() const
{
    return m->materials ;
}

engine::dimn::Materials &
Light::
peek_materials()
{
    return m->materials ;
}

const Frame &
Light::
peek_frame() const
{
    return m->frame_stowed.peek_frame() ;
}

Frame &
Light::
peek_frame()
{
    return m->frame_stowed.peek_frame() ;
}

}}} // namespace esve::engine::dim3
