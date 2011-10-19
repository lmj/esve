
#ifndef esve_engine_dim3_Camera_Details_hxx
#define esve_engine_dim3_Camera_Details_hxx

#include <esve/types/real.hxx>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Camera_Details esve/engine/dim3/Camera_Details.hxx
/// @brief Projection and clip parameters.
///

class Camera_Details
{
public:
    ///
    /// @enum Projection
    /// @brief The type of frustum.
    ///
    enum Projection
    {
        /// .
        ORTHOGONAL,

        /// .
        PERSPECTIVE,

        /// .
        CUSTOM
    } ;

    ///
    /// @class Orthogonal_Projection esve/engine/dim3/Camera_Details.hxx
    /// @brief Orthogonal projection data.
    ///
    struct Orthogonal_Projection
    {
        /// @brief Height of the centered rectangular viewing frustum.
        types::real frustum_height ;

        ///@{
        /// @brief .
        types::real near_clip ;
        types::real far_clip ;
        ///@}

        /// Constructor.
        Orthogonal_Projection( types::real frustum_height,
                               types::real near_clip,
                               types::real far_clip ) ;
    } ;

    ///
    /// @class Perspective_Projection esve/engine/dim3/Camera_Details.hxx
    /// @brief Perspective projection data.
    ///
    struct Perspective_Projection
    {
        /// Field of view (vertical angle), in degrees.
        types::real field_of_view ;

        ///@{
        /// @brief .
        types::real near_clip ;
        types::real far_clip ;
        ///@}

        /// Constructor.
        Perspective_Projection( types::real field_of_view,
                                types::real near_clip,
                                types::real far_clip ) ;
    } ;

    /// Query the current projection.
    virtual Projection projection() const = 0 ;

    ///@{

    /// @brief Set to orthogonal projection.
    virtual void orthogonal_projection( const Orthogonal_Projection & ) = 0 ;

    /// @brief Set to perspective projection.
    virtual void perspective_projection( const Perspective_Projection & ) = 0 ;

    /// @brief Set to custom projection.
    virtual void custom_projection() = 0 ;

    ///@}

    ///@{

    /// @brief Query stored orthogonal projection data.
    virtual const Orthogonal_Projection &
    orthogonal_projection_data() const = 0 ;

    /// @brief Query stored perspective projection data.
    virtual const Perspective_Projection &
    perspective_projection_data() const = 0 ;

    ///@}

    ///@{
    /// @brief Clip planes.
    virtual types::real far_clip() const = 0 ;
    virtual void far_clip( types::real ) = 0 ;
    virtual types::real near_clip() const = 0 ;
    virtual void near_clip( types::real ) = 0 ;
    ///@}

    virtual ~Camera_Details() = 0 ;

protected:
    Camera_Details() ;

    ///@{
    ///
    /// @brief Set the OpenGL projection matrix.
    ///
    /// Called by the camera directly after the compute() message is
    /// sent to children.
    ///
    /// OpenGL is set to projection matrix mode just before calling
    /// (with the identity loaded), and modelview matrix mode is
    /// restored afterward.
    ///
    virtual void compute_perspective_projection() = 0 ;
    virtual void compute_orthogonal_projection() = 0 ;
    virtual void compute_custom_projection() = 0 ;
    ///@}

    // Allow aggregates to call compute_*_projection().
    static void call_compute_projection( Camera_Details & ) ;

private:
    Camera_Details( const Camera_Details & ) ;
    Camera_Details & operator=( const Camera_Details & ) ;
} ;

}}} // namespace esve::engine::dim3

#endif

