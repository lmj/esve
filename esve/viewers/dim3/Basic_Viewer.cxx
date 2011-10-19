
#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/viewers/dim3/Default_Initializer.hxx>
#include <esve/components/dim3/Camera.hxx>
#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Light.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dim3/Camera_Details.hxx>
#include <esve/engine/dim3/Geom.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/engine/dimn/Materials.hxx>
#include <esve/ui/base/End_Condition.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/impl/Draw_Node.hxx>
#include <esve/message/impl/Compute_Node.hxx>
#include <esve/message/Draw_Sender_Delegator.hxx>
#include <esve/util/misc.hxx>
#include <esve/types/rgba.hxx>
#include <cassert>
#include <algorithm>

namespace esve { namespace viewers { namespace dim3 {

using types::pure ;
using types::rgba ;

struct Basic_Viewer::Private
{
    struct Own_Draw_Node : public message::impl::Draw_Node
    {
        typedef message::impl::Draw_Node super ;
        
        Basic_Viewer::Private & m ;

        Own_Draw_Node( Basic_Viewer::Private & m_ )
            : m(m_) { }

        void send_draw()
        {
            if( !m.block_draw )
            {
                super::send_draw() ;
            }
        }

        void send_draw_initialize()
        {
            if( !m.block_draw )
            {
                super::send_draw_initialize() ;
            }
        }
    } ;

    typedef
    util::auto_ptr_vector<Basic_Viewer::Private_Light>
    Lights ;

    util::misc::Complete_Object_Flag complete_object ;
    kernel::Simple_Kernel kernel ;
    Cameras cameras ;
    Lights lights ;
    Default_Initializer own_initialize ;
    Own_Draw_Node shared_initialize_node ;
    Own_Draw_Node lit_draw_node ;
    Own_Draw_Node unlit_draw_node ;
    Own_Draw_Node shared_draw_node ;
    message::impl::Compute_Node shared_compute_node ;
    engine::dim3::impl::Frame root_frame ;
    ui::base::End_Condition end_condition ;
    bool block_draw ;
    util::misc::Complete_Object_Guard complete_object_guard ;

    Private() ;
    ~Private() ;

    void connect_lights() ;
} ;

Basic_Viewer::Private::
Private()
    : complete_object(),
      kernel(),
      cameras(),
      lights(),
      own_initialize(),
      shared_initialize_node(*this),
      lit_draw_node(*this),
      unlit_draw_node(*this),
      shared_draw_node(*this),
      shared_compute_node(),
      root_frame(),
      end_condition(),
      block_draw(true),
      complete_object_guard(complete_object)
{
}

Basic_Viewer::Private::
~Private()
{
}

Basic_Viewer::Private_Camera::
Private_Camera(
    const std::string & label,
    const Camera::Rectangle & rectangle,
    Basic_Viewer & viewer )
    :
    components::dim3::Camera(label, rectangle),
    m_viewer(viewer)
{
    m_viewer.m->cameras.push_back(
        std::auto_ptr<Basic_Viewer::Private_Camera>(this)) ;

    // params
    peek_frame().peek_transform().translate(pure(0, 0, 5)) ;
    peek_camera_details().near_clip(0.1) ;
    peek_camera_details().far_clip(50) ;

    // frame tree
    m_viewer.m->root_frame.add(peek_frame()) ;

    // compute tree
    peek_compute_sender().add(m_viewer.m->shared_compute_node) ;

    // draw tree
    peek_draw_initializer().add(m_viewer.m->shared_initialize_node) ;
    peek_draw_sender().add(m_viewer.m->lit_draw_node) ;
    peek_unlit_draw_sender().add(m_viewer.m->unlit_draw_node) ;

    // handle tree
    m_viewer.m->kernel.add_emitter(*this) ;
}

Basic_Viewer::Private_Camera::
~Private_Camera()
{
    if( m_viewer.m->complete_object )
    {
        Basic_Viewer::Cameras::const_iterator found =
            std::find(m_viewer.m->cameras.begin(),
                      m_viewer.m->cameras.end(),
                      this) ;
        
        assert(found != m_viewer.m->cameras.end()) ;
        
        if( found != m_viewer.m->cameras.end() )
        {
            std::auto_ptr<Basic_Viewer::Private_Camera> camera =
                m_viewer.m->cameras.release(found) ;
            
            assert(camera.get() == this) ;
            
            // caller is already deleting this
            camera.release() ;
        }
        
        assert(std::find(m_viewer.m->cameras.begin(),
                         m_viewer.m->cameras.end(),
                         this)
               ==
               m_viewer.m->cameras.end()) ;
    }
}

Basic_Viewer::Private_Light::
Private_Light( Basic_Viewer & viewer )
    :
    engine::dim3::Light(),
    m_viewer(viewer)
{
    m_viewer.m->lights.push_back(
        std::auto_ptr<Basic_Viewer::Private_Light>(this)) ;
    
    // params
    peek_frame().peek_transform().translate(pure(-0.5, 0.5, 5.0)) ;
    peek_materials().ambient(rgba(0.2, 0.2, 0.2, 1.0)) ;
    peek_materials().diffuse(rgba(0.8, 0.8, 0.8, 1.0)) ;

    // frame tree
    m_viewer.m->root_frame.add(peek_frame()) ;

    // draw tree
    m_viewer.m->connect_lights() ;
}

Basic_Viewer::Private_Light::
~Private_Light()
{
    if( m_viewer.m->complete_object )
    {
        Basic_Viewer::Private::Lights::const_iterator found =
            std::find(m_viewer.m->lights.begin(),
                      m_viewer.m->lights.end(),
                      this) ;
        
        assert(found != m_viewer.m->lights.end()) ;
        
        if( found != m_viewer.m->lights.end() )
        {
            std::auto_ptr<Basic_Viewer::Private_Light> light =
                m_viewer.m->lights.release(found) ;
            
            assert(light.get() == this) ;
            
            // caller is already deleting this
            light.release() ;
        }
        
        assert(std::find(m_viewer.m->lights.begin(),
                         m_viewer.m->lights.end(),
                         this)
               ==
               m_viewer.m->lights.end()) ;
        
        // rope 'em up again
        m_viewer.m->connect_lights() ;
    }
}

Basic_Viewer::
Basic_Viewer()
    : m(new Private())
{
    // initialize tree
    m->shared_initialize_node.add(m->own_initialize) ;

    // draw tree
    m->connect_lights() ;

    // update tree
    m->kernel.add_update_receiver(m->root_frame) ;

    // handle tree
    m->kernel.add_handler(m->end_condition) ;
}

Basic_Viewer::
~Basic_Viewer()
{
}

int
Basic_Viewer::
takeover()
{
    //
    // The modal tie screws up initialization since it fiddles with
    // showing/hiding in order to get the thing to work right.
    // Ideally, the camera would be hidden until takeover(), but this
    // is not the case.  As a workaround, block all draw messages
    // until takeover().
    //

    m->block_draw = false ;
    
    for( Cameras::const_iterator i = m->cameras.begin() ;
         i != m->cameras.end() ;
         ++i )
    {
        (**i).reinitialize() ;
    }
    
    return m->kernel.takeover() ;
}

engine::dim3::Camera &
Basic_Viewer::
create_camera( const std::string & label,
               const engine::dim3::Camera::Rectangle & rectangle )
{
    // Constructor adds itself to Basic_Viewer's list of owned cameras
    return *(new Basic_Viewer::Private_Camera(label, rectangle, *this)) ;
}

void
Basic_Viewer::Private::
connect_lights()
{
    //
    //
    // lit_draw_node --> light0 --> light1 --> ... --> shared_draw_node
    //
    //

    lit_draw_node.remove_all() ;

    if( lights.size() == 0 )
    {
        // bypass lights
        lit_draw_node.add(shared_draw_node) ;
    }
    else
    {
        for( Lights::const_iterator i = lights.begin() ;
             i != lights.end() ;
             ++i )
        {
            (**i).remove_all() ;
        }

        lit_draw_node.add(*lights.front()) ;

        {
            Lights::const_iterator i = lights.begin() ;
            Lights::const_iterator j = lights.begin() ;
            ++j ;
            while( j != lights.end() )
            {
                (**i).add(**j) ;
                ++i ;
                ++j ;
            }
        }

        lights.back()->add(shared_draw_node) ;
    }
}

engine::dim3::Light &
Basic_Viewer::
create_light()
{
    // Constructor adds itself to Basic_Viewer's list of owned lights
    return *(new Basic_Viewer::Private_Light(*this)) ;
}

void
Basic_Viewer::
add_geom( engine::dim3::Geom & geom )
{
    // compute tree
    m->shared_compute_node.add(geom) ;

    // draw tree
    m->shared_draw_node.add(geom) ;

    // frame tree
    m->root_frame.add(geom) ;
}

void
Basic_Viewer::
remove_geom( engine::dim3::Geom & geom )
{
    // compute tree
    m->shared_compute_node.remove(geom) ;

    // draw tree
    m->shared_draw_node.remove(geom) ;

    // frame tree
    m->root_frame.remove(geom) ;
}

void
Basic_Viewer::
add_frame( engine::dim3::Frame & frame )
{
    m->root_frame.add(frame) ;
}

void
Basic_Viewer::
remove_frame( engine::dim3::Frame & frame )
{
    m->root_frame.remove(frame) ;
}

void
Basic_Viewer::
add_handler( components::dimn::Motion_Handler & a )
{
    // handle tree
    m->kernel.add_handler(a) ;

    // sync update tree
    m->kernel.add_update_receiver(a) ;
}

void
Basic_Viewer::
remove_handler( components::dimn::Motion_Handler & a )
{
    // handle tree
    m->kernel.remove_handler(a) ;

    // sync update tree
    m->kernel.remove_update_receiver(a) ;
}

message::Compute_Sender &
Basic_Viewer::
peek_compute_sender()
{
    return m->shared_compute_node ;
}

message::Draw_Sender &
Basic_Viewer::
peek_draw_sender()
{
    return m->shared_draw_node ;
}

message::Draw_Sender &
Basic_Viewer::
peek_unlit_draw_sender()
{
    return m->unlit_draw_node ;
}

message::Draw_Sender &
Basic_Viewer::
peek_draw_initializer()
{
    return m->shared_initialize_node ;
}

void
Basic_Viewer::
add_handler( kernel::Handler & a )
{
    m->kernel.add_handler(a) ;
}

void
Basic_Viewer::
remove_handler( kernel::Handler & a )
{
    m->kernel.remove_handler(a) ;
}

void
Basic_Viewer::
remove_all_handlers()
{
    m->kernel.remove_all_handlers() ;
}

kernel::Simple_Kernel &
Basic_Viewer::
peek_kernel()
{
    return m->kernel ;
}

Basic_Viewer::Cameras::const_iterator
Basic_Viewer::
cameras_begin()
{
    return m->cameras.begin() ;
}

Basic_Viewer::Cameras::const_iterator
Basic_Viewer::
cameras_end()
{
    return m->cameras.end() ;
}

const std::string
Basic_Viewer::
default_camera_label = "Camera" ;

const engine::dim3::Camera::Rectangle
Basic_Viewer::
default_camera_rectangle = engine::dim3::Camera::Rectangle(500, 500) ;

}}} // namespace esve::viewers::dim3

