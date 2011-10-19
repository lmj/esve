//
// This class deals only with rotations, and will in fact normalize
// the transformation it is given.
//

#ifndef esve_components_dim4_Rotation_Handler_hxx
#define esve_components_dim4_Rotation_Handler_hxx

#include <esve/components/dimn/Differential_Motion_Handler.hxx>
#include <esve/engine/dim4/Transform.hxx>
#include <esve/types/pure.hxx>
#include <memory>

namespace esve { namespace components { namespace dim4 {

///
/// @class Rotation_Handler esve/components/dim4/Rotation_Handler.hxx
/// @brief Mappings from two-dimensional mouse input to four-dimensional rotations.
///

class Rotation_Handler
    : public components::dimn::Differential_Motion_Handler
             <
                 engine::dim4::Transform
             >
{
private:
    typedef
    components::dimn::Differential_Motion_Handler
             <
                 engine::dim4::Transform
             >
    super ;

    Rotation_Handler( const Rotation_Handler & ) ;
    Rotation_Handler & operator=( const Rotation_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    ///
    /// @enum Mapping
    ///
    /// @brief Mappings from 2D mouse input to 4D rotations.
    ///
    /// Let @e u represent the mouse drag, lying in the <em>(i,j)</em> plane.
    ///
    /// In principle we could rotate any orthonormal pair
    /// <em>(a,b)</em>, however since our input is only
    /// two-dimensional it is most natural to make <em>a = 1</em> and
    /// <em>b = u</em>.  Rotations of <em>(1,u)</em> and
    /// <em>(1,u)</em>-perp are more than enough to generate <em>SO(4)</em>.
    ///
    /// To rotate a general plane in four dimensions, one can provide a
    /// basis for the motion with the @e basis() method.
    ///
    enum Mapping
    {
        ///
        /// Rotate the <em>(k,u)</em> plane by angle
        /// <em>abs(u)</em>.  This is a 3D rotation with axis
        /// <em>cross(k,u)</em>.
        ///
        ROTATE_K_TOWARD_U,

        ///
        /// Rotate the <em>(k,u)</em>-perp plane by angle <em>abs(u)</em>
        ///
        ROTATE_K_TOWARD_U_PERP,

        ///
        /// Rotate the <em>(1,u)</em> plane by angle <em>abs(u)</em>.
        ///
        ROTATE_1_TOWARD_U,

        ///
        /// Rotate the <em>(1,u)</em>-perp plane by angle
        /// <em>abs(u)</em>.  This is a 3D rotation with axis @e u.
        ///
        ROTATE_1_TOWARD_U_PERP,

        ///
        /// Rotate the <em>(1,u)</em> plane by angle
        /// <em>abs(u)/sqrt(2)</em> and rotate the <em>(1,u)</em>-perp
        /// plane by angle <em>abs(u)/sqrt(2)</em>.  This is
        /// quaternion multiplication on the left.
        ///
        LEFT_HOPF_ROTATION,

        ///
        /// Rotate the <em>(1,u)</em> plane by angle
        /// <em>abs(u)/sqrt(2)</em> and rotate the <em>(1,u)</em>-perp
        /// plane by angle <em>-abs(u)/sqrt(2)</em>.  This is
        /// quaternion multiplication on the right.
        ///
        RIGHT_HOPF_ROTATION,

        ///
        /// Same as LEFT_HOPF_ROTATION but with motion angles in
        /// opposite direction.
        ///
        NEG_LEFT_HOPF_ROTATION,

        ///
        /// Same as RIGHT_HOPF_ROTATION but with motion angles in
        /// opposite direction
        ///
        NEG_RIGHT_HOPF_ROTATION,

        ///
        /// Torus double-rotation.  The first plane is rotated by
        /// angle <em>dot(i, u)</em>, the second is rotated by angle
        /// <em>dot(j, u)</em>.
        ///
        DOUBLE_ROTATE_1IJK,

        ///
        /// Torus double-rotation.  The first plane is rotated by
        /// angle <em>dot(i, u)</em>, the second is rotated by angle
        /// <em>dot(j, u)</em>.
        ///
        DOUBLE_ROTATE_1JKI,

        ///
        /// Torus double-rotation.  The first plane is rotated by
        /// angle <em>dot(i, u)</em>, the second is rotated by angle
        /// <em>dot(j, u)</em>.
        ///

        DOUBLE_ROTATE_1KIJ,

        ///
        /// Torus double-rotation.  The first plane is rotated by
        /// angle <em>dot(i, u)</em>, the second is rotated by angle
        /// <em>dot(j, u)</em>.
        ///
        DOUBLE_ROTATE_IJ1K,

        ///
        /// Ignore mouse input.
        ///
        DO_NOTHING
    } ;

    /// Constructor.  Give the transform on which this handler operates.
    explicit Rotation_Handler( engine::dim4::Transform & ) ;

    ///@{
    /// @brief The method to associate mouse drags with rotations.
    virtual Mapping mapping( Button ) const ;
    virtual void mapping( Button, Mapping ) ;
    ///@}

    ~Rotation_Handler() ;

protected:
    ///@{
    /// @brief Base class hook.
    void create_motion( Button, const types::pure & du_dt ) ;
    engine::dim4::Transform
    differential_motion( Button button, types::real dt ) ;
    void stop_motion( Button ) ;
    bool has_motion( Button ) ;
    ///@}
} ;

}}} // namespace esve::components::dim4

#endif

