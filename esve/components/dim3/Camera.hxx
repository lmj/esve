
#ifndef esve_components_dim3_Camera_hxx
#define esve_components_dim3_Camera_hxx

#include <esve/engine/dim3/Camera.hxx>
#include <memory>

namespace esve { namespace components { namespace dim3 {

///
/// @class Camera esve/components/dim3/Camera.hxx
/// @brief A camera with a preconfigured draw tree.
///
/// Front-end for components::dimn::Draw_Tree_impl.  Buffers are
/// automatically cleared.
///

class Camera
    :
    public engine::dim3::Camera
{
private:
    typedef engine::dim3::Camera super ;

    class Private ;
    const std::auto_ptr<Private> m ;

    Camera( const Camera & ) ;
    Camera & operator=( const Camera & ) ;

public:
    Camera( const std::string & label, const Rectangle & ) ;

    ///@{
    ///
    /// @brief Receivers intended for OpenGL initialization.
    ///
    /// Receivers added here will be called before all other draw()
    /// receivers.
    ///
    virtual message::Draw_Sender & peek_draw_initializer() ;

    ///
    /// @brief Draw tree for lit drawing; place lights
    /// here.
    ///
    virtual message::Draw_Sender & peek_draw_sender() ;

    ///
    /// @brief Draw tree for unlit drawing; place backgrounds here.
    ///
    virtual message::Draw_Sender & peek_unlit_draw_sender() ;
    ///@}

    ~Camera() = 0 ;

protected:
    Camera() ;
} ;

}}} // namespace esve::components::dim3

#endif

