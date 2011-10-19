
#ifndef esve_engine_dim4_Frame_hxx
#define esve_engine_dim4_Frame_hxx

#include <esve/engine/dim4/Transform_Stowed.hxx>
#include <esve/message/Update_Receiver.hxx>

namespace esve { namespace engine { namespace dim4 {

namespace impl { class Frame ; }

///
/// @class Frame esve/engine/dim4/Frame.hxx
/// @brief The frame tree.
///
/// The update() message is passed to all child frames.
///
/// Since Frame derives from message::Update_Receiver, a Frame
/// implicitly plays the role of an message::Update_Node (but for
/// Frames only).
///

class Frame
    : virtual public Transform_Stowed,
      virtual public message::Update_Receiver
{
public:
    /// The transform in world (standard) coordinates.
    virtual
    const engine::dim4::Transform &
    world_transform() const = 0 ;

    ///@{
    /// @brief Child frames.
    virtual void add( Frame & ) = 0 ;
    virtual void remove( Frame & ) = 0 ;
    virtual void remove_all() = 0 ;
    ///@}

    // not encouraged; leave out of doxygen.
    virtual void remove_parent() = 0 ;

    // mandatory implementation
    virtual impl::Frame & frame() = 0 ;
    virtual const impl::Frame & frame() const = 0 ;

    virtual ~Frame() = 0 ;

protected:
    Frame() ;

private:
    Frame( const Frame & ) ;
    Frame & operator=( const Frame & ) ;
} ;

}}} // namespace esve::engine::dim4

#endif

