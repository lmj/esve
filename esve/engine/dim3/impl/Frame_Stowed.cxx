
#include <esve/engine/dim3/impl/Frame_Stowed.hxx>
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Frame.hxx>

namespace esve { namespace engine { namespace dim3 { namespace impl {

struct Frame_Stowed::Private
{
    //
    // The frame tree holds Frame pointers, and therefore behavior
    // cannot be modified except through delegating out everything
    // from the held instance.
    //
    
    //
    // hook to destination...
    //
    struct Own_Frame
        : public impl::Frame
    {
        typedef impl::Frame super ;
        
        Frame_Stowed::Private & m ;

        Own_Frame( Frame_Stowed::Private & m_ )
            : m(m_) { }
        
        const dim3::Transform & peek_transform() const
        {
            return m.dst.peek_frame().peek_transform() ;
        }
        
        dim3::Transform & peek_transform()
        {
            return m.dst.peek_frame().peek_transform() ;
        }

        const dim3::Transform & world_transform() const
        {
            return m.dst.peek_frame().world_transform() ;
        }

        void add( engine::dim3::Frame & a )
        {
            m.dst.peek_frame().add(a) ;
        }
        
        void remove( engine::dim3::Frame & a )
        {
            m.dst.peek_frame().remove(a) ;
        }
        
        void remove_all()
        {
            m.dst.peek_frame().remove_all() ;
        }

        void remove_parent()
        {
            m.dst.peek_frame().remove_parent() ;
        }

        void update()
        {
            call_update(m.dst.peek_frame()) ;
        }

        void update( double dt )
        {
            call_update(m.dst.peek_frame(), dt) ;
        }

        void base_update()
        {
            super::update() ;
        }

        // protected workaround
        void base_update( double dt )
        {
            super::update(dt) ;
        }
    } ;

    //
    // ... and back again
    //
    struct Own_Frame_Hook
        : virtual public engine::dim3::Frame
    {
        Frame_Stowed::Private & m ;

        Own_Frame_Hook( Frame_Stowed::Private & m_ )
            : m(m_) { }
        
        void update()
        {
            m.frame.base_update() ;
        }

        void update( double dt )
        {
            m.frame.base_update(dt) ;
        }
        
        const Transform & peek_transform() const
        {
            return m.frame.Own_Frame::super::peek_transform() ;
        }
        
        Transform & peek_transform()
        {
            return m.frame.Own_Frame::super::peek_transform() ;
        }
        
        const engine::dim3::Transform & world_transform() const
        {
            return m.frame.Own_Frame::super::world_transform() ;
        }
        
        void add( engine::dim3::Frame & a )
        {
            m.frame.Own_Frame::super::add(a) ;
        }
        
        void remove( engine::dim3::Frame & a )
        {
            m.frame.Own_Frame::super::remove(a) ;
        }
        
        void remove_all()
        {
            m.frame.Own_Frame::super::remove_all() ;
        }
        
        void remove_parent()
        {
            m.frame.Own_Frame::super::remove_parent() ;
        }

        impl::Frame & frame()
        {
            return m.frame ;
        }
        
        const impl::Frame & frame() const
        {
            return m.frame ;
        }

        message::impl::Update_Receiver & update_receiver()
        {
            return m.frame ;
        }
    } ;

    engine::dim3::Frame_Stowed & dst ;
    Own_Frame frame ;
    Own_Frame_Hook frame_hook ;

    Private( engine::dim3::Frame_Stowed & dst_ )
        : dst(dst_),
          frame(*this),
          frame_hook(*this) { }
} ;

Frame_Stowed::
Frame_Stowed( engine::dim3::Frame_Stowed & dst )
    : m(new Private(dst))
{
}

Frame_Stowed::
~Frame_Stowed()
{
}

engine::dim3::Frame &
Frame_Stowed::
peek_frame()
{
    return m->frame_hook ;
}

const engine::dim3::Frame &
Frame_Stowed::
peek_frame() const
{
    return m->frame_hook ;
}

}}}} // namespace esve::engine::dim3::impl
