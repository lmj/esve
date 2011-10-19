
#ifndef esve_engine_dim4_Frame_Stowed_hxx
#define esve_engine_dim4_Frame_Stowed_hxx

namespace esve { namespace engine { namespace dim4 {

///
/// @class Frame_Stowed esve/engine/dim4/Frame_Stowed.hxx
/// @brief Stowed frame.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///
/// @see Frame
///

class Frame ;

class Frame_Stowed
{
public:
    ///@{
    /// @brief Peek at the frame.
    virtual const engine::dim4::Frame & peek_frame() const = 0 ;
    virtual engine::dim4::Frame & peek_frame() = 0 ;
    ///@}

    virtual ~Frame_Stowed() = 0 ;

protected:
    Frame_Stowed() ;

private:
    Frame_Stowed( const Frame_Stowed & ) ;
    Frame_Stowed & operator=( const Frame_Stowed & ) ;
} ;

}}} // namespace esve::engine::dim4

#endif

