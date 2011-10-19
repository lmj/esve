
#include <esve/engine/dim3/Camera.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/impl/Frame_Stowed.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/engine/dim3/Camera_Details.hxx>
#include <esve/engine/dim3/transform_util.hxx>
#include <esve/ui/base/Display_Details.hxx>
#include <esve/message/Draw_Sender_Delegator.hxx>
#include <esve/message/Compute_Sender_Delegator.hxx>
#include <esve/gl/gl.hxx>
#include <esve/gl/glu.hxx>
#include <limits>

namespace esve { namespace engine { namespace dim3 {

using types::real ;
using gl::gl ;

const double INIT_ORTH_WIDTH = 1.0 ;
const double INIT_NEAR_CLIP = 0.1 ;
const double INIT_FAR_CLIP = 20.0 ;
const double INIT_FOV = 45.0 ;

struct Camera::Private
{
    struct Own_Frame
        : public Frame
    {
        Frame & base ;
        Camera::Private & m ;

        Own_Frame( Frame & base_,
                   Camera::Private & m_ )
            : base(base_),
              m(m_) { }

        const dim3::Transform & peek_transform() const
        {
            return base.peek_transform() ;
        }
        
        dim3::Transform & peek_transform()
        {
            return base.peek_transform() ;
        }

        const dim3::Transform & world_transform() const
        {
            return base.world_transform() ;
        }

        void add( Frame & a )
        {
            base.add(a) ;
        }
        
        void remove( Frame & a )
        {
            base.remove(a) ;
        }
        
        void remove_all()
        {
            base.remove_all() ;
        }

        void remove_parent()
        {
            base.remove_parent() ;
        }

        impl::Frame & frame()
        {
            return base.frame() ;
        }
        
        const impl::Frame & frame() const
        {
            return base.frame() ;
        }

        void update( double dt )
        {
            // outside will call base_update(dt)
            call_update(m.outside, dt) ;
        }

        void update()
        {
            // outside will call base_update()
            m.outside.update() ;
        }

        void base_update( double dt )
        {
            call_update(base, dt) ;
        }

        void base_update()
        {
            call_update(base) ;
        }

        message::impl::Update_Receiver & update_receiver()
        {
            return base.update_receiver() ;
        }
    } ;

    struct Own_Draw_Sender : public message::Draw_Sender_Delegator
    {
        typedef message::Draw_Sender_Delegator super ;
        
        Camera::Private & m ;

        Own_Draw_Sender( message::Draw_Sender & base,
                         Camera::Private & m_ )
            : super(base),
              m(m_) { }

        void add( message::Draw_Receiver & a )
        {
            super::add(a) ;
        }

        void remove( message::Draw_Receiver & a )
        {
            super::remove(a) ;
        }

        void remove_all()
        {
            super::remove_all() ;
        }

        void send_draw()
        {
            Transform world_inverse(
                m.outside.peek_frame().world_transform()) ;

            world_inverse.invert() ;

            GLfloat glmat[16] ;

            transform_util::build_matrix(world_inverse, glmat) ;
            
            {
                gl::PushMatrix sentry ;
                glMultMatrixf(glmat) ;
                super::send_draw() ;
            }
        }

        void send_draw_initialize()
        {
            super::send_draw_initialize() ;
        }
    } ;

    struct Own_Display_Details : public ui::base::Display_Details
    {
        ui::base::Display_Details & base ;
        Camera::Private & m ;

        Own_Display_Details( ui::base::Display_Details & base_,
                             Camera::Private & m_ )
            : base(base_),
              m(m_) { }

        const std::string & label() const
        {
            return base.label() ;
        }
        
        void label( const std::string & a )
        {
            base.label(a) ;
        }

        const Display::Rectangle & rectangle() const
        {
            return base.rectangle() ;
        }

        void make_current()
        {
            base.make_current() ;
        }

        void reshape( const Display::Rectangle & rectangle )
        {
            m.need_compute = true ;
            call_reshape(base, rectangle) ;
        }
    } ;

    struct Own_Camera_Details
        : virtual public Camera_Details
    {
        Camera::Private & m ;

        Own_Camera_Details( Camera::Private & m_ )
            : m(m_) { }

        real near_clip() const
        {
            return m.orthogonal.near_clip ;
        }

        void near_clip( real a )
        {
            m.need_compute = true ;
            m.orthogonal.near_clip = a ;
            m.perspective.near_clip = a ;
        }

        real far_clip() const
        {
            return m.orthogonal.far_clip ;
        }

        void far_clip( real a )
        {
            m.need_compute = true ;
            m.orthogonal.far_clip = a ;
            m.perspective.far_clip = a ;
        }

        Camera_Details::Projection projection() const
        {
            return m.projection ;
        }

        const Perspective_Projection & perspective_projection_data() const
        {
            return m.perspective ;
        }

        const Orthogonal_Projection & orthogonal_projection_data() const
        {
            return m.orthogonal ;
        }
        
        void
        perspective_projection( const Perspective_Projection & perspective )
        {
            m.need_compute = true ;
            m.perspective = perspective ;
            m.projection = PERSPECTIVE ;

            m.orthogonal.far_clip = m.perspective.far_clip ;
            m.orthogonal.near_clip = m.perspective.near_clip ;
        }

        void orthogonal_projection( const Orthogonal_Projection & orthogonal )
        {
            m.need_compute = true ;
            m.orthogonal = orthogonal ;
            m.projection = ORTHOGONAL ;

            m.perspective.far_clip = m.orthogonal.far_clip ;
            m.perspective.near_clip = m.orthogonal.near_clip ;
        }

        void custom_projection()
        {
            m.need_compute = true ;
            m.projection = CUSTOM ;
        }
        
        void compute_perspective_projection()
        {
            Camera::Rectangle rectangle = 
                m.outside.peek_display_details().rectangle() ;
            
            gluPerspective(
                GLdouble(m.perspective.field_of_view),
                (rectangle.height == 0
                 ?
                 std::numeric_limits<GLdouble>::max()
                 :
                 GLdouble(rectangle.width)/GLdouble(rectangle.height)),
                GLdouble(m.perspective.near_clip),
                GLdouble(m.perspective.far_clip)) ;
        }

        void compute_orthogonal_projection()
        {
            Camera::Rectangle rectangle = 
                m.outside.peek_display_details().rectangle() ;

            GLdouble world_half_height = m.orthogonal.frustum_height/2 ;
            
            GLdouble world_half_width =
                rectangle.height == 0
                ?
                std::numeric_limits<GLdouble>::max()
                :
                GLdouble(world_half_height)
                *
                GLdouble(rectangle.width)/GLdouble(rectangle.height) ;

            glOrtho(GLdouble(-world_half_width),
                    GLdouble(world_half_width),
                    GLdouble(-world_half_height),
                    GLdouble(world_half_height),
                    GLdouble(m.orthogonal.near_clip),
                    GLdouble(m.orthogonal.far_clip)) ;
        }

        void compute_custom_projection()
        {
        }

        // workaround protected status
        static
        void call_compute_projection( Camera_Details & camera )
        {
            Camera_Details::call_compute_projection(camera) ;
        }
    } ;

    struct Own_Compute_Sender : public message::Compute_Sender_Delegator
    {
        typedef message::Compute_Sender_Delegator super ;

        Camera::Private & m ;

        Own_Compute_Sender( message::Compute_Sender & base,
                            Camera::Private & m_ )
            : super(base),
              m(m_) { }

        void add( message::Compute_Receiver & a )
        {
            super::add(a) ;
        }

        void remove( message::Compute_Receiver & a )
        {
            super::remove(a) ;
        }

        void remove_all()
        {
            super::remove_all() ;
        }

        void send_compute()
        {
            super::send_compute() ;

            if( m.need_compute )
            {
                gl::MatrixMode sentry(GL_PROJECTION) ;
                glLoadIdentity() ;

                Own_Camera_Details::call_compute_projection(
                    m.outside.peek_camera_details()) ;

                m.need_compute = false ;
            }
        }
    } ;

    Camera & outside ;

    impl::Frame_Stowed base_frame ;
    Own_Frame frame ;
    Own_Camera_Details camera_details ;
    Own_Display_Details display_details ;
    Own_Compute_Sender compute_sender ;
    Own_Draw_Sender draw_sender ;
    Camera_Details::Orthogonal_Projection orthogonal ;
    Camera_Details::Perspective_Projection perspective ;
    Camera_Details::Projection projection ;
    bool need_compute ;

    Private( Camera & outside_ ) ;
} ;

Camera::Private::
Private( Camera & outside_ )
    : outside(outside_),
      base_frame(outside),
      frame(base_frame.peek_frame(), *this),
      camera_details(*this),
      display_details(outside.Camera::super::peek_display_details(),
                      *this),
      compute_sender(outside.Camera::super::peek_compute_sender(),
                     *this),
      draw_sender(outside.Camera::super::peek_draw_sender(),
                  *this),
      orthogonal(INIT_ORTH_WIDTH,
                 INIT_NEAR_CLIP,
                 INIT_FAR_CLIP),
      perspective(INIT_FOV,
                  INIT_NEAR_CLIP,
                  INIT_FAR_CLIP),
      projection(Camera_Details::PERSPECTIVE),
      need_compute(true)
{
}

Camera::
Camera( const std::string & label, const Rectangle & rectangle )
    : Display(label, rectangle),
      m(new Private(*this))
{
}

Camera::
~Camera()
{
}

message::Compute_Sender &
Camera::
peek_compute_sender()
{
    return m->compute_sender ;
}

const ui::base::Display_Details &
Camera::
peek_display_details() const
{
    return m->display_details ;
}

ui::base::Display_Details &
Camera::
peek_display_details()
{
    return m->display_details ;
}

const Camera_Details &
Camera::
peek_camera_details() const
{
    return m->camera_details ;
}

Camera_Details &
Camera::
peek_camera_details()
{
    return m->camera_details ;
}

message::Draw_Sender &
Camera::
peek_draw_sender()
{
    return m->draw_sender ;
}

const dim3::Frame &
Camera::
peek_frame() const
{
    return m->frame ;
}

dim3::Frame &
Camera::
peek_frame()
{
    return m->frame ;
}

void
Camera::
update( double dt )
{
    Display::update(dt) ;
    m->frame.base_update(dt) ;
}

void
Camera::
update()
{
    Display::update() ;
    m->frame.base_update() ;
}

}}} // namespace esve::engine::dim3
