
#include <esve/base/dimn/Frame.hxx>

namespace esve { namespace base { namespace dimn {

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
Frame<Transform,
      Right_Act,
      Update_Notify>::
Frame( const Transform & transform,
       Update_Notify & update_notify )
    : m_Base_Child(this),
      m_Base_Parent(this),
      m_transform(transform),
      m_update_notify(update_notify),
      m_world_transform(),
      m_need_compute_world_transform(true)
{
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
Frame<Transform,
      Right_Act,
      Update_Notify>::
~Frame()
{
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
void
Frame<Transform,
      Right_Act,
      Update_Notify>::
update( const typename Update_Notify::Args & args )
{
    m_need_compute_world_transform = true ;

    for( typename m_Base_Parent::children_iterator i =
             m_Base_Parent::children_begin() ;
         i != m_Base_Parent::children_end() ;
         ++i )
    {
        (*i).update(args) ;
    }

    m_update_notify(args) ;
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
const Transform &
Frame<Transform,
      Right_Act,
      Update_Notify>::
world_transform() const
{
    if( m_need_compute_world_transform )
    {
        if( m_Base_Child::parent() )
        {
            m_world_transform = m_Base_Child::parent()->world_transform() ;

            Right_Act right_act ;
            right_act(m_world_transform, m_transform) ;
        }
        else
        {
            m_world_transform = m_transform ;
        }

        m_need_compute_world_transform = false ;
    }

    return m_world_transform ;
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
void
Frame<Transform,
      Right_Act,
      Update_Notify>::
add_child_frame( Frame & a )
{
    m_Base_Parent::add_child(&a) ;
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
void
Frame<Transform,
      Right_Act,
      Update_Notify>::
remove_child_frame( Frame & a )
{
    m_Base_Parent::remove_child(&a) ;
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
void
Frame<Transform,
      Right_Act,
      Update_Notify>::
remove_child_frames()
{
    m_Base_Parent::remove_children() ;
}

template< typename Transform,
          typename Right_Act,
          typename Update_Notify >
void
Frame<Transform,
      Right_Act,
      Update_Notify>::
remove_parent_frame()
{
    m_Base_Child::remove_parent() ;
}

}}} // namespace esve::base::dimn
