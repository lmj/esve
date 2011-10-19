
#ifndef esve_engine_dim3_impl_Frame_hxx
#define esve_engine_dim3_impl_Frame_hxx

#include <esve/engine/dim3/Frame.hxx>
#include <esve/message/impl/Update_Receiver.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim3 { namespace impl {

///
/// @class Frame esve/engine/dim3/impl/Frame.hxx
/// @brief Implements engine::dim3::Frame.
///

class Frame
    : virtual public engine::dim3::Frame,
      virtual public message::impl::Update_Receiver
{
public:
    /// Construct identity.
    Frame() ;

    /// Construct with a current Transform.
    explicit Frame( const Transform & ) ;

    const engine::dim3::Transform &
    world_transform() const ;

    void add( engine::dim3::Frame & ) ;
    void remove( engine::dim3::Frame & ) ;
    void remove_all() ;

    void remove_parent() ;

    ///@{
    const engine::dim3::Transform & peek_transform() const ;
    engine::dim3::Transform & peek_transform() ;
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

}}}} // namespace esve::engine::dim3::impl

#endif

