#ifndef esve_engine_dim3_Camera_hxx
#define esve_engine_dim3_Camera_hxx

#include <esve/engine/dim3/Frame_Stowed.hxx>
#include <esve/engine/dim3/Camera_Details_Stowed.hxx>
#include <esve/engine/dim3/Camera.hxx>
#include <esve/ui/base/Display.hxx>
#include <memory>
#include <string>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Camera esve/engine/dim3/Camera.hxx
/// @brief A Display with a Frame.
///
/// Camera derives multiply from Frame and Display.  Its update()
/// method calls both Frame::update() and Display::update(), marking
/// the Frame as dirty and marking the Display for redrawing.
///
/// Camera computes its projection matrix after its compute tree has
/// been called (see message::Compute_Receiver).
///
/// If two cameras are part of the same frame hierarchy, one call to
/// the root frame's update() will suffice for redrawing both displays.
///

class Camera
    :
    virtual public Camera_Details_Stowed,
    virtual public Frame_Stowed,
    public ui::base::Display
{
private:
    typedef ui::base::Display super ;

    Camera( const Camera & ) ;
    Camera & operator=( const Camera & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    /// Constructor.
    Camera( const std::string & label, const Rectangle & ) ;

    message::Compute_Sender & peek_compute_sender() ;

    message::Draw_Sender & peek_draw_sender() ;

    ///@{
    const ui::base::Display_Details &
    peek_display_details() const ;
    ui::base::Display_Details &
    peek_display_details() ;
    ///@}

    ///@{
    const Camera_Details & peek_camera_details() const ;
    Camera_Details & peek_camera_details() ;
    ///@}

    ///@{
    const Frame & peek_frame() const ;
    Frame & peek_frame() ;
    ///@}

    ~Camera() ;

protected:
    void update() ;
    void update( double dt ) ;
} ;

}}} // namespace esve::engine::dim3

#endif

