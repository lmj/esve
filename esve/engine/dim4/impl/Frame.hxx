
#ifndef esve_engine_dim4_impl_Frame_hxx
#define esve_engine_dim4_impl_Frame_hxx

#include <esve/engine/dim4/Frame.hxx>
#include <esve/message/impl/Update_Receiver.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim4 { namespace impl {

///
/// @class Frame esve/engine/dim4/impl/Frame.hxx
/// @brief Implements engine::dim4::Frame.
///

class Frame
    : virtual public engine::dim4::Frame,
      virtual public message::impl::Update_Receiver
{
public:
    /// Construct identity.
    Frame() ;

    /// Construct with a current Transform.
    explicit Frame( const Transform & ) ;

    const engine::dim4::Transform &
    world_transform() const ;

    void add( engine::dim4::Frame & ) ;
    void remove( engine::dim4::Frame & ) ;
    void remove_all() ;

    void remove_parent() ;

    ///@{
    const engine::dim4::Transform & peek_transform() const ;
    engine::dim4::Transform & peek_transform() ;
    ///@}

    impl::Frame & frame() ;
    const impl::Frame & frame() const ;

    ~Frame() ;

protected:
    void update() ;
    void update( double dt ) ;

private:
    Frame( const Frame & ) ;
    Frame & operator=( const Frame & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}}} // namespace esve::engine::dim4::impl

#endif

