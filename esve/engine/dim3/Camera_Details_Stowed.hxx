
#ifndef esve_engine_dim3_Camera_Details_Stowed_hxx
#define esve_engine_dim3_Camera_Details_Stowed_hxx

namespace esve { namespace engine { namespace dim3 {

///
/// @class Camera_Details_Stowed esve/engine/dim3/Camera_Details_Stowed.hxx
/// @brief Stowed camera details.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///

class Camera_Details ;

class Camera_Details_Stowed
{
public:
    ///@{
    /// @brief Peek at the camera details.
    virtual const engine::dim3::Camera_Details &
    peek_camera_details() const = 0 ;
    virtual engine::dim3::Camera_Details &
    peek_camera_details() = 0 ;
    ///@}

    virtual ~Camera_Details_Stowed() = 0 ;

protected:
    Camera_Details_Stowed() ;

private:
    Camera_Details_Stowed( const Camera_Details_Stowed & ) ;
    Camera_Details_Stowed & operator=( const Camera_Details_Stowed & ) ;
} ;

}}} // namespace esve::engine::dim3

#endif

