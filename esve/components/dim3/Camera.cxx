
#include <esve/components/dim3/Camera.hxx>
#include <esve/components/dimn/Draw_Tree_impl.hxx>
#include <esve/message/Draw_Sender_Delegator.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace components { namespace dim3 {

struct Camera::Private
{
    struct Clear_Buffers
        : virtual public message::impl::Draw_Receiver
    {
        void draw()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        }
    } ;
    
    struct Own_Draw_Sender : public message::Draw_Sender_Delegator
    {
        typedef message::Draw_Sender_Delegator super ;
        
        Own_Draw_Sender( message::Draw_Sender & base,
                         Camera::Private & m )
            : Draw_Sender_Delegator(base)
        {
            super::add(m.draw_tree.root_draw_node) ;
            m.draw_tree.clear_buffers_node.add(m.clear_buffers) ;
        }
        
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
            super::send_draw() ;
        }
        
        void send_draw_initialize()
        {
            super::send_draw_initialize() ;
        }
    } ;
    
    components::dimn::Draw_Tree_impl draw_tree ;
    Clear_Buffers clear_buffers ;
    Own_Draw_Sender draw_sender ;

    Private( Camera & outside )
        : draw_tree(),
          clear_buffers(),
          draw_sender(outside.Camera::super::peek_draw_sender(),
                      *this) { }
} ;

Camera::
Camera( const std::string & label,
        const Rectangle & rectangle )
    : super(label, rectangle),
      m(new Private(*this))
{
}

Camera::
~Camera()
{
}

message::Draw_Sender &
Camera::
peek_draw_sender()
{
    return m->draw_sender ;
}

message::Draw_Sender &
Camera::
peek_unlit_draw_sender()
{
    return m->draw_tree.unlit_draw_node ;
}

message::Draw_Sender &
Camera::
peek_draw_initializer()
{
    return m->draw_tree.draw_initialize_node ;
}

}}} // namespace esve::components::dim3
