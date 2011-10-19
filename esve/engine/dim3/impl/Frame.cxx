
#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/message/Update_Receiver.hxx>
#include <esve/message/diagnostic.hxx>
#include <esve/base/dimn/Frame.hxx>
#include <cassert>

namespace esve { namespace engine { namespace dim3 { namespace impl {

struct Frame::Private
{
    struct Right_Act
    {
        // a := a*b
        void operator()( Transform & a, const Transform & b )
        {
            a.right_act(b) ;
        }
    } ;

    enum Update_Source
    {
        FROM_ENGINE,
        FROM_FRAME
    } ;

    class Update_Notify
    {
    private:
        Frame::Private & m ;

    public:
        struct Args
        {
            double dt ;
            bool sync ;

            Args( double dt_,
                  bool sync_ )
                : dt(dt_),
                  sync(sync_) { }
        } ;

        Update_Notify( Frame::Private & m_ )
            : m(m_) { }

        void operator()( const Args & args )
        {
#if defined(ESVE_DIAGNOSTIC)
            message::diagnostic::header_receiver_only("update",
                                                      m.outside) ;
            message::diagnostic::
                pair("", "(frame update)") ;

#endif
            m.update_source = FROM_FRAME ;

            if( args.sync )
            {
                Own_Update_Receiver::call_update(m.outside, args.dt) ;
            }
            else
            {
                m.outside.update() ;
            }

            m.update_source = FROM_ENGINE ;
        }
    } ;

    struct Own_Update_Receiver : public message::Update_Receiver
    {
        using message::Update_Receiver::call_update ;
    } ;

    typedef
    base::dimn::Frame<Transform, Right_Act, Update_Notify>
    Frame_base ;

    Frame & outside ;
    Update_Source update_source ;
    Transform transform ;
    Update_Notify update_notify ;
    Frame_base frame_base ;

    Private( Frame & outside_ )
            : outside(outside_),
              update_source(FROM_ENGINE),
              transform(),
              update_notify(*this),
              frame_base(transform, update_notify) { }

    void common_update( double dt, bool sync )
    {
        switch( update_source )
        {
        case FROM_FRAME:
            {
                // The original update() message passed through the
                // frame tree and ended up here.
                
                // This is a hook; we do nothing.
            }
            break ;
            
        case FROM_ENGINE:
            {
                // update() message received from the engine; pass
                // this on to the frame tree.
                
                frame_base.update(Frame::Private::Update_Notify::
                                  Args(dt, sync)) ;
            }
            break ;
        }
    }
} ;

Frame::
Frame()
    : m(new Private(*this))
{
}

Frame::
~Frame()
{
}

const dim3::Transform &
Frame::
peek_transform() const
{
    return m->transform ;
}

dim3::Transform &
Frame::
peek_transform()
{
    return m->transform ;
}

const engine::dim3::Transform &
Frame::
world_transform() const
{
    return m->frame_base.world_transform() ;
}

void
Frame::
add( engine::dim3::Frame & a )
{
    m->frame_base.add_child_frame(a.frame().m->frame_base) ;
}

void
Frame::
remove( engine::dim3::Frame & a )
{
    m->frame_base.remove_child_frame(a.frame().m->frame_base) ;
}

void
Frame::
remove_all()
{
    m->frame_base.remove_child_frames() ;
}

void
Frame::
remove_parent()
{
    m->frame_base.remove_parent_frame() ;
}

void
Frame::
update()
{
    m->common_update(0, false) ;
}

void
Frame::
update( double dt )
{
    m->common_update(dt, true) ;
}

impl::Frame &
Frame::
frame()
{
    return *this ;
}

const impl::Frame &
Frame::
frame() const
{
    return *this ;
}

}}}} // namespace esve::engine::dim3::impl
