
#ifndef esve_components_dim4_Simple_Rotation_Handler_hxx
#define esve_components_dim4_Simple_Rotation_Handler_hxx

#include <esve/components/dimn/Motion_Handler.hxx>
#include <esve/components/dimn/Inertial_Motion_Handler.hxx>
#include <esve/types/real.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim4 {

class Transform ;

}}} // namespace esve::engine::dim4

namespace esve { namespace components { namespace dim4 {

///
/// @class Simple_Rotation_Handler esve/components/dim4/Simple_Rotation_Handler.hxx
/// @brief Front-end to Rotation_Handler.
///
/// The longitudinal/latitudinal parameterization of SO(4) and the Hopf
/// parameterization of SO(4).
///
/// See <a href=../../README.4d>README.4d</a>.

class Simple_Rotation_Handler
    : virtual public components::dimn::Inertial_Motion_Handler,
      public components::dimn::Motion_Handler
{
public:
    ///
    /// @enum Mapping
    ///
    enum Mapping
    {
        /// Longitudinal/latitudinal motions.
        LONGLAT,

        /// Hopf motions.
        HOPF
    } ;

    /// Constructor.  Give the transform on which this handler operates.
    explicit Simple_Rotation_Handler( engine::dim4::Transform & ) ;

    ///@{
    ///
    /// @brief The method of associating input motion with rotations.
    ///
    virtual Mapping mapping() const ;
    virtual void mapping( Mapping ) ;
    ///@}

    ///@{
    ///
    /// @brief Convert the right mouse button to yield double-rotations
    /// aligned with the transform itself.
    ///
    virtual bool slide() const ;
    virtual void slide( bool ) ;
    ///@}

    ///@{
    /// @brief The transform on which this handler operates.
    const engine::dim4::Transform & active_transform() const ;
    void active_transform( engine::dim4::Transform & ) ;
    ///@}

    ~Simple_Rotation_Handler() ;

    void stop() ;
    types::real sensitivity() const ;
    void sensitivity( types::real ) ;

protected:
    bool handle_check_awake( bool ) ;

    void update() ;
    void update( double dt ) ;

private:
    Simple_Rotation_Handler( const Simple_Rotation_Handler & ) ;
    Simple_Rotation_Handler & operator=( const Simple_Rotation_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::components::dim4

#endif

