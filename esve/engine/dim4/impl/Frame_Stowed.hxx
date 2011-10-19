
#ifndef esve_engine_dim4_impl_Frame_Stowed_hxx
#define esve_engine_dim4_impl_Frame_Stowed_hxx

#include <esve/engine/dim4/Frame_Stowed.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim4 { 

class Frame_Stowed ;

}}} // namespace esve::engine::dim4

namespace esve { namespace engine { namespace dim4 { namespace impl {

///
/// @class Frame_Stowed esve/engine/dim4/impl/Frame_Stowed.hxx
/// @brief Implements engine::dim4::Frame_Stowed.
///

class Frame_Stowed
    : virtual public engine::dim4::Frame_Stowed
{
public:
    /// Constructor.  Where shall we send calls?
    Frame_Stowed( engine::dim4::Frame_Stowed & destination ) ;
    
    const engine::dim4::Frame & peek_frame() const ;
    engine::dim4::Frame & peek_frame() ;

    ~Frame_Stowed() ;

private:
    Frame_Stowed( const Frame_Stowed & ) ;
    Frame_Stowed & operator=( const Frame_Stowed & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}}} // namespace esve::engine::dim4::impl

#endif

