
#include <esve/viewers/dim3/Starry_Viewer.hxx>
#include <esve/components/dim3/Keyboard_Rotation_Handler.hxx>
#include <esve/components/dimn/Draw_Compiler.hxx>
#include <esve/components/dimn/Make_Draw_Receiver.hxx>
#include <esve/engine/dim3/Make_Frame.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/ui/base/Keyboard.hxx>
#include <esve/message/Active_State.hxx>
#include <esve/message/Draw_Sender.hxx>
#include <esve/geom/dim3/Stars.hxx>
#include <esve/util/auto_ptr_vector.hxx>
#include <string>
#include <cassert>
#include <memory>

namespace esve { namespace viewers { namespace dim3 {

struct Starry_Viewer::Private
{
    Starry_Viewer & outside ;
    bool stars_active ;

    Private( Starry_Viewer & outside_ )
        :
        outside(outside_),
        stars_active(true)
    {
    }

    ~Private() ;
} ;

struct Starry_Viewer::Private_Camera::Private
{
    struct Stars_Data
        : public components::dimn::Draw_Compiler
    {
        components::dimn::Make_Draw_Receiver< geom::dim3::Stars > data ;
        
        Stars_Data()
            :
            data()
        {
            add(data) ;
        }
    } ;
    
    typedef engine::dim3::Make_Frame<Stars_Data> Stars ;

    Starry_Viewer & viewer ;
    Stars stars ;
    components::dim3::Keyboard_Rotation_Handler handler ;

    Private( Starry_Viewer & viewer_ )
        :
        viewer(viewer_),
        stars(),
        handler(stars.peek_transform())
    {
    }
} ;

Starry_Viewer::Private_Camera::
Private_Camera( const std::string & label,
                const Camera::Rectangle & rectangle,
                Starry_Viewer & viewer )
    :
    Basic_Viewer::Private_Camera(label, rectangle, viewer),
    m(new Private(viewer))
{
    // draw tree
    peek_unlit_draw_sender().add(m->stars) ;
    
    // frame tree
    peek_frame().add(m->stars) ;
    
    // handle tree
    m->viewer.add_handler(m->handler) ;
    
    m->stars.active(m->viewer.m->stars_active) ;
}

Starry_Viewer::Private_Camera::
~Private_Camera()
{
}

Starry_Viewer::Private::
~Private()
{
}

Starry_Viewer::
Starry_Viewer()
    : super(),
      m(new Private(*this))
{
}

Starry_Viewer::
~Starry_Viewer()
{
}

engine::dim3::Camera &
Starry_Viewer::
create_camera( const std::string & label,
               const engine::dim3::Camera::Rectangle & rectangle )
{
    // Constructor adds itself to Basic_Viewer's list of owned cameras
    return *(new Starry_Viewer::Private_Camera(label, rectangle, *this)) ;
}

bool
Starry_Viewer::
stars_active() const
{
    return m->stars_active ;
}

void
Starry_Viewer::
stars_active( bool a )
{
    for( Cameras::const_iterator
             i = cameras_begin(),
             end = cameras_end() ;
         i != end ;
         ++i )
    {
        if( Starry_Viewer::Private_Camera* camera =
            dynamic_cast<Starry_Viewer::Private_Camera*>(&(**i)) )
        {
            camera->m->stars.active(a) ;
        }
    }

    m->stars_active = a ;
}

}}} // namespace esve::viewers::dim3
