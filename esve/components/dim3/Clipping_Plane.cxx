
#include <esve/components/dim3/Clipping_Plane.hxx>
#include <esve/engine/dim3/impl/Frame_Stowed.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dim3/Rendering_Error.hxx>
#include <esve/engine/dim3/transform_util.hxx>
#include <esve/gl/gl.hxx>
#include <cassert>
#include <sstream>

namespace esve { namespace components { namespace dim3 {

using engine::dim3::Transform ;
using engine::dim3::transform_util::apply_transform ;
using types::pure ;
using gl::gl ;

namespace {

GLenum index2id( GLint index )
{
    switch( index )
    {
    case 0:
        return GL_CLIP_PLANE0 ;
    case 1:
        return GL_CLIP_PLANE1 ;
    case 2:
        return GL_CLIP_PLANE2 ;
    case 3:
        return GL_CLIP_PLANE3 ;
    case 4:
        return GL_CLIP_PLANE4 ;
    case 5:
        return GL_CLIP_PLANE5 ;
    default:
        assert(!"More clip planes than clip plane enums") ;
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

struct Clipping_Plane::Private
{
    GLint max_clip_planes ;
    engine::dim3::impl::Frame_Stowed frame_stowed ;

    Private( Clipping_Plane & outside_ )
        : max_clip_planes(0),
          frame_stowed(outside_) { }
} ;

Clipping_Plane::
Clipping_Plane()
    : m(new Private(*this))
{
}

Clipping_Plane::
~Clipping_Plane()
{
}

void
Clipping_Plane::
send_draw()
{
    if( m->max_clip_planes == 0 )
    {
        // assume the same answer for all OpenGL contexts
        glGetIntegerv(GL_MAX_CLIP_PLANES, &m->max_clip_planes) ;
    }
    
    GLenum clip_plane_id = GLenum(0) ;
        
    {
        GLint i = 0 ;
        for( ; i != m->max_clip_planes ; ++i )
        {
            if( glIsEnabled(index2id(i)) == GL_FALSE )
            {
                clip_plane_id = index2id(i) ;
                break ;
            }
        }

        if( i == m->max_clip_planes )
        {
            throw Too_Many_Clipping_Planes_Error(int(m->max_clip_planes)) ;
        }
    }
        
    //
    // plane equation:
    //
    //     dot(x - p, n) == 0
    //
    // where x is a pure variable, p is an arbitrary point on the
    // plane, and n is the plane normal.
    //
    
    // hook!
    const Transform world = peek_frame().world_transform() ;
    
    const pure p = world.translation() ;
    const pure n = apply_transform(Transform(world.rotation()),
                                   pure(0, 0, 1)) ;
    
    const GLdouble plane_equation[4] =
        {
            n.x(),
            n.y(),
            n.z(),
            -dot(p, n)
        } ;
    
    {
        gl::PushAttrib sentry(GL_TRANSFORM_BIT) ;
        glEnable(clip_plane_id) ;
        
        glClipPlane(clip_plane_id, plane_equation) ;
        
        super::send_draw() ;
    }
}

const engine::dim3::Frame &
Clipping_Plane::
peek_frame() const
{
    return m->frame_stowed.peek_frame() ;
}

engine::dim3::Frame &
Clipping_Plane::
peek_frame()
{
    return m->frame_stowed.peek_frame() ;
}

Clipping_Plane::
Too_Many_Clipping_Planes_Error::
Too_Many_Clipping_Planes_Error( int n )
    : Rendering_Error("Maximum number of clip planes ("
                      +
                      to_string(n)
                      +
                      ") exceeded"),
      max_clip_planes(n)
{
}

Clipping_Plane::
Too_Many_Clipping_Planes_Error::
~Too_Many_Clipping_Planes_Error() throw()
{
}

}}} // namespace esve::components::dim3
