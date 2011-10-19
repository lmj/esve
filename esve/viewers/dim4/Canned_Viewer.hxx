
#ifndef esve_viewers_dim4_Canned_Viewer_hxx
#define esve_viewers_dim4_Canned_Viewer_hxx

#include <esve/viewers/dim4/Inversion.hxx>
#include <esve/viewers/dim3/Canned_Viewer_Base.hxx>
#include <esve/viewers/dimn/Scaling.hxx>
#include <esve/types/quat.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim4 {

class Transform ;
class Geom ;

}}} // namespace esve::engine::dim4

namespace esve { namespace viewers { namespace dim4 {

///
/// @class Canned_Viewer esve/viewers/dim4/Canned_Viewer.hxx
/// @brief A prepackaged, shrink-wrapped viewer stuffed into a can.
///
/// This class encapsulates most of the implementation for
/// Simple_Viewer.
///

class Canned_Viewer
    : virtual public dimn::Scaling,
      virtual public Inversion,
      public viewers::dim3::Canned_Viewer_Base
{
private:
    typedef viewers::dim3::Canned_Viewer_Base super ;

    Canned_Viewer( const Canned_Viewer & ) ;
    Canned_Viewer & operator=( const Canned_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    /// Constructor.  Give the arguments from main().
    Canned_Viewer( int argc, char** argv ) ;

    ///@{
    ///
    /// @brief Geoms.
    ///
    /// The Geom is added to the shared compute node, to the shared
    /// draw node, and to the shared rotation frame.
    ///
    virtual void add_geom( engine::dim4::Geom & ) ;

    ///
    /// @brief Geoms.
    ///
    /// The Geom is removed from the shared compute node, from the
    /// shared draw node, and from the shared rotation frame (if it
    /// was a direct child).
    ///
    virtual void remove_geom( engine::dim4::Geom & ) ;
    ///@}

    using super::add_geom ;
    using super::remove_geom ;

    ///@{
    /// @brief Scaling applied to all added geoms.
    void scaling( types::real ) ;
    types::real scaling() const ;
    ///@}

    ///@{
    /// @brief Inversion applied to all added geoms.
    void inversion( types::real ) ;
    types::real inversion() const ;
    ///@}

    ///@{
    /// @brief Rotation applied to all added geoms (unitary diagonal).
    virtual const engine::dim4::Transform & rotation() const ;
    virtual void rotation( const types::quat & upper_left,
                           const types::quat & lower_right ) ;
    ///@}

    ///@{
    /// @brief Reset to this transform.
    virtual const engine::dim4::Transform & home_transform() const ;
    virtual void home_transform( const engine::dim4::Transform & ) ;
    ///@}

    /// Stop the motion handler.
    virtual void stop_motion() ;

    ///@{
    /// @brief See components::dim4::Simple_Rotation_Handler::slide().
    virtual bool slide() const ;
    virtual void slide( bool ) ;
    ///@}

    ~Canned_Viewer() ;
} ;

}}} // namespace esve::viewers::dim4

#endif
