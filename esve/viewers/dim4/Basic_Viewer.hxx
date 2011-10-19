
#ifndef esve_viewers_dim4_Basic_Viewer_hxx
#define esve_viewers_dim4_Basic_Viewer_hxx

#include <esve/viewers/dim4/Minimal_Viewer.hxx>
#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim4 {

class Frame ;

}}} // namespace esve::engine::dim4

namespace esve { namespace viewers { namespace dim4 {

///
/// @class Basic_Viewer esve/viewers/dim4/Basic_Viewer.hxx
/// @brief A basic viewer.
///

class Basic_Viewer
    : virtual public Minimal_Viewer,
      public viewers::dim3::Basic_Viewer
{
private:
    typedef viewers::dim3::Basic_Viewer super ;

    Basic_Viewer( const Basic_Viewer & ) ;
    Basic_Viewer & operator=( const Basic_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Basic_Viewer() ;

    ///@{
    /// @brief Geoms.
    ///
    /// The Geom is added to the shared compute node, to the shared
    /// draw node, and to the children of the root frame.
    ///
    virtual void add_geom( engine::dim4::Geom & ) ;

    ///
    /// @brief Geoms.
    ///
    /// The Geom is removed compute node, from the shared draw node,
    /// and from the root frame (if it was a direct child).
    ///
    virtual void remove_geom( engine::dim4::Geom & ) ;
    ///@}

    ///@{
    using super::add_geom ;
    using super::remove_geom ;
    ///@}

    ///@{
    ///
    /// @brief Frames.
    ///
    /// The frame is made a child of the root frame.
    ///
    virtual void add_frame( engine::dim4::Frame & ) ;

    ///
    /// @brief Frames.
    ///
    /// The frame is orphaned from the root frame (if it was a direct
    /// child).
    ///
    virtual void remove_frame( engine::dim4::Frame & ) ;
    ///@}

    ///@{
    using super::add_frame ;
    using super::remove_frame ;
    ///@}

    ~Basic_Viewer() ;
} ;

}}} // namespace esve::viewers::dim4

#endif
