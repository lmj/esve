
#ifndef esve_viewers_dim3_Basic_Viewer_hxx
#define esve_viewers_dim3_Basic_Viewer_hxx

#include <esve/viewers/dim3/Minimal_Viewer.hxx>
#include <esve/components/dim3/Camera.hxx>
#include <esve/engine/dim3/Light.hxx>
#include <esve/kernel/Simple_Kernel_Stowed.hxx>
#include <esve/message/Compute_Sender_Stowed.hxx>
#include <esve/message/Draw_Sender_Stowed.hxx>
#include <esve/util/auto_ptr_vector.hxx>
#include <string>
#include <memory>

namespace esve { namespace engine { namespace dim3 {

class Frame ;
class Geom ;

}}} // namespace esve::engine::dim3

namespace esve { namespace components { namespace dimn  {

class Motion_Handler ;

}}} // namespace esve::engine::dimn

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Basic_Viewer esve/viewers/dim3/Basic_Viewer.hxx
/// @brief A basic viewer.
///
/// There is one shared handle tree; all emitters send to it; all
/// handlers receive from it.
///
/// There is one shared compute tree; all cameras produced by
/// create_camera() trigger it.
///
/// There is one shared initialize tree; all cameras produced by
/// create_camera() call it.
///
/// There is one shared draw tree; all cameras produced by
/// create_camera() call it; all lights produced by create_light()
/// contribute to it.
///
/// There is one shared frame tree; all lights, cameras, and added
/// geoms are made children of the root frame.  (Of course you may
/// arrange the frame tree according to your whim; the default is
/// simply to be a child of the root frame.)
///

class Basic_Viewer
    : virtual protected kernel::Simple_Kernel_Stowed,
      virtual protected message::Draw_Sender_Stowed,
      virtual protected message::Compute_Sender_Stowed,
      virtual public Minimal_Viewer
{
private:
    Basic_Viewer( const Basic_Viewer & ) ;
    Basic_Viewer & operator=( const Basic_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Basic_Viewer() ;

    /// Shorthand for peek_kernel().takeover().
    virtual int takeover() ;

    ///
    /// @brief Cameras.
    ///
    /// The camera is a child of the root frame.  The viewer owns the
    /// camera.
    ///
    virtual
    engine::dim3::Camera &
    create_camera( const std::string & = default_camera_label,
                   const engine::dim3::Camera::Rectangle & =
                   default_camera_rectangle ) ;

    ///
    /// @brief Lights.
    ///
    /// The light is a child of the root frame.  All lights are
    /// enabled for the shared draw node.  The viewer owns the light.
    ///
    virtual engine::dim3::Light & create_light() ;

    ///@{
    /// @brief Geoms.
    ///
    /// The Geom is added to the shared compute node, to the shared
    /// draw node, and to the children of the root frame.
    ///
    virtual void add_geom( engine::dim3::Geom & ) ;

    ///
    /// @brief Geoms.
    ///
    /// The Geom is removed compute node, from the shared draw node,
    /// and from the root frame (if it was a direct child).
    ///
    virtual void remove_geom( engine::dim3::Geom & ) ;
    ///@}

    ///@{
    /// @brief Motion handlers.
    ///
    /// The handler will receive handle_check_awake() and update(dt)
    /// messages with a time delta dt.
    ///
    virtual void add_handler( components::dimn::Motion_Handler & ) ;

    ///
    /// @brief Motion handlers.
    ///
    /// It will be removed from the handle tree and the update tree.
    ///
    virtual void remove_handler( components::dimn::Motion_Handler & ) ;
    ///@}

    ///@{
    /// @brief Regular handlers.
    virtual void add_handler( kernel::Handler & ) ;
    virtual void remove_handler( kernel::Handler & ) ;
    ///@}

    ///@{

    ///
    /// @brief Frames.
    ///
    /// The frame is made a child of the root frame.
    ///
    virtual void add_frame( engine::dim3::Frame & ) ;

    ///
    /// @brief Frames.
    ///
    /// The frame is orphaned from the root frame (if it was a direct
    /// child).
    ///
    virtual void remove_frame( engine::dim3::Frame & ) ;

    ///@}

    ~Basic_Viewer() ;

    static const std::string default_camera_label ;
    static const engine::dim3::Camera::Rectangle default_camera_rectangle ;

protected:
    // For derivation in Basic_Viewer subclasses
    class Private_Camera
        :
        public components::dim3::Camera
    {
    public:
        Private_Camera(
            const std::string & label,
            const Camera::Rectangle & rectangle,
            Basic_Viewer & viewer ) ;
        ~Private_Camera() ;

    private:
        Private_Camera() ;
        Basic_Viewer & m_viewer ;
    } ;
    
    // For derivation in Basic_Viewer subclasses
    class Private_Light
        :
        public engine::dim3::Light
    {
    public:
        Private_Light( Basic_Viewer & viewer ) ;
        ~Private_Light() ;

    private:
        Private_Light() ;
        Basic_Viewer & m_viewer ;
    } ;
    
    void remove_all_handlers() ;

    /// The shared (lit) draw node.
    message::Draw_Sender & peek_draw_sender() ;

    /// The shared unlit draw node.
    message::Draw_Sender & peek_unlit_draw_sender() ;

    /// The shared initialize node.
    message::Draw_Sender & peek_draw_initializer() ;

    /// The shared compute node.
    message::Compute_Sender & peek_compute_sender() ;

    kernel::Simple_Kernel & peek_kernel() ;

    typedef
    util::auto_ptr_vector<Private_Camera>
    Cameras ;
    
    Cameras::const_iterator cameras_begin() ;
    Cameras::const_iterator cameras_end() ;
} ;

}}} // namespace esve::viewers::dim3

#endif
