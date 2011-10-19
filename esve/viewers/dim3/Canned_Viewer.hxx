
#ifndef esve_viewers_dim3_Canned_Viewer_hxx
#define esve_viewers_dim3_Canned_Viewer_hxx

#include <esve/viewers/dim3/Canned_Viewer_Base.hxx>
#include <esve/viewers/dimn/Scaling.hxx>
#include <esve/types/quat.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim3 {

class Transform ;
class Geom ;

}}} // namespace esve::engine::dim3

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Canned_Viewer esve/viewers/dim3/Canned_Viewer.hxx
/// @brief A prepackaged, shrink-wrapped viewer stuffed into a can.
///
/// Note the override of add_geom(), which makes the added geom a
/// child of the rotation frame.
///
/// This class encapsulates most of the implementation for
/// Simple_Viewer.
///

class Canned_Viewer
    : virtual public dimn::Scaling,
      public Canned_Viewer_Base
{
private:
    typedef Canned_Viewer_Base super ;

    Canned_Viewer( const Canned_Viewer & ) ;
    Canned_Viewer & operator=( const Canned_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Canned_Viewer( int argc, char** argv ) ;

    ///
    /// @brief Add a Geom.
    ///
    /// (Override.)  The Geom is added to the shared compute node, to
    /// the shared draw node, and to the rotation frame.
    ///
    virtual void add_geom( engine::dim3::Geom & ) ;

    ///
    /// @brief Remove a Geom.
    ///
    /// (Override.)  The Geom is removed compute node, from the shared
    /// draw node, and from the rotation frame or the root frame (if
    /// either was a direct child).
    ///
    virtual void remove_geom( engine::dim3::Geom & ) ;

    ///@{
    /// @brief Scaling applied to all added geoms.
    void scaling( types::real ) ;
    types::real scaling() const ;
    ///@}

    ///@{
    /// @brief Rotation applied to all added geoms.
    virtual const engine::dim3::Transform & rotation() const ;
    virtual void rotation( const types::quat & ) ;
    ///@}

    ///@{
    /// @brief Reset to this transform.
    virtual const engine::dim3::Transform & home_transform() const ;
    virtual void home_transform( const engine::dim3::Transform & ) ;
    ///@}

    /// Stop the motion handler.
    virtual void stop_motion() ;

    ~Canned_Viewer() ;
} ;

}}} // namespace esve::viewers::dim3

#endif
