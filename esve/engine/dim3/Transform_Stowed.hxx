#ifndef esve_engine_dim3_Transform_Stowed_hxx
#define esve_engine_dim3_Transform_Stowed_hxx

namespace esve { namespace engine { namespace dim3 {

///
/// @class Transform_Stowed esve/engine/dim3/Transform_Stowed.hxx
/// @brief Stowed transform.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///

class Transform ;

class Transform_Stowed
{
public:
    ///@{
    /// @brief Peek at the transform.
    virtual const engine::dim3::Transform & peek_transform() const = 0 ;
    virtual engine::dim3::Transform & peek_transform() = 0 ;
    ///@}

    virtual ~Transform_Stowed() = 0 ;

protected:
    Transform_Stowed() ;

private:
    Transform_Stowed( const Transform_Stowed & ) ;
    Transform_Stowed & operator=( const Transform_Stowed & ) ;
} ;

}}} // namespace esve::engine::dim3

#endif

