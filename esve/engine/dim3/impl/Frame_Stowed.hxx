
#ifndef esve_engine_dim3_impl_Frame_Stowed_hxx
#define esve_engine_dim3_impl_Frame_Stowed_hxx

#include <esve/engine/dim3/Frame_Stowed.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim3 { 

class Frame_Stowed ;

}}} // namespace esve::engine::dim3

namespace esve { namespace engine { namespace dim3 { namespace impl {

///
/// @class Frame_Stowed esve/engine/dim3/impl/Frame_Stowed.hxx
/// @brief Implements engine::dim3::Frame_Stowed.
///

class Frame_Stowed
    : virtual public engine::dim3::Frame_Stowed
{
public:
    /// Constructor.  Where shall we send calls?
    Frame_Stowed( engine::dim3::Frame_Stowed & destination ) ;
    
    const engine::dim3::Frame & peek_frame() const ;
    engine::dim3::Frame & peek_frame() ;

    ~Frame_Stowed() ;

private:
    Frame_Stowed( const Frame_Stowed & ) ;
    Frame_Stowed & operator=( const Frame_Stowed & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}}} // namespace esve::engine::dim3::impl

#endif

