//
// Frame Hierarchy
//
// A frame is a local coordinate system which inherits the local
// coordinate system of its parent.
//
// world_transform() returns the transform in world coordinates.
//
// After a frame is changed, update() needs to be called somehow.
// The user can either call update() manually or call it implicitly
// through the update hierarchy.  A single update() on the root frame
// is sufficient.
//
// Note that update() only marks the frame as needing its world
// transform recomputed.  The world transform is not actually
// computed until world_transform() is called.  The world_transform()
// value is cached for efficiency.
//
// The Right_Act functor looks like
//
//     struct Right_Act
//     {
//         // a := a*b
//         void operator()( Transform & a,
//                          const Transform & b ) ;
//     } ;
//
// When a child frame is updated by its parent, the Update_Notify
// functor is call.
//

#ifndef esve_base_dimn_Frame_hxx
#define esve_base_dimn_Frame_hxx

#include <esve/util/SP_Tree.hxx>

namespace esve { namespace base { namespace dimn {

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
class Frame
    : protected util::SP_Tree_Child<Frame<Transform,
                                          Right_Act,
                                          Update_Notify>*,
                                    Frame<Transform,
                                          Right_Act,
                                          Update_Notify>*>,
      protected util::SP_Tree_Parent<Frame<Transform,
                                           Right_Act,
                                           Update_Notify>*,
                                     Frame<Transform,
                                           Right_Act,
                                           Update_Notify>*>
{
private:
    typedef
    util::SP_Tree_Child<Frame<Transform,
                              Right_Act,
                              Update_Notify>*,
                        Frame<Transform,
                              Right_Act,
                              Update_Notify>*>
    m_Base_Child ;

    typedef
    util::SP_Tree_Parent<Frame<Transform,
                               Right_Act,
                               Update_Notify>*,
                         Frame<Transform,
                               Right_Act,
                               Update_Notify>*>
    m_Base_Parent ;

#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1() const
    {
        Right_Act right_act ;
        Transform a ;
        const Transform b ;
        right_act(a, b) ;
    }

    void m_requirements_2( Update_Notify & notify,
                           const typename Update_Notify::Args & args ) const
    {
        typedef typename Update_Notify::Args Args ;
        notify(args) ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (Frame::*R1)() const ;
            typedef void (Frame::*R2)(
                Update_Notify &,
                const typename Update_Notify::Args & ) const ;
            
            R1 r1 = &Frame::m_requirements_1 ;
            R2 r2 = &Frame::m_requirements_2 ;
            m_unused(r1) ;
            m_unused(r2) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    Frame( const Frame & ) ;
    Frame & operator=( const Frame & ) ;

    const Transform & m_transform ;
    Update_Notify & m_update_notify ;
    mutable Transform m_world_transform ;
    mutable bool m_need_compute_world_transform ;

public:
    Frame( const Transform &, Update_Notify & ) ;

    const Transform & world_transform() const ;

    virtual void update( const typename Update_Notify::Args & ) ;

    void add_child_frame( Frame & )  ;
    void remove_child_frame( Frame & )  ;
    void remove_child_frames()  ;
    void remove_parent_frame() ;

    ~Frame() ;
} ;

}}} // namespace esve::base::dimn

#include <esve/base/dimn/Frame.template.cxx>

#endif

