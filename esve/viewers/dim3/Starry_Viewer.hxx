
#ifndef esve_viewers_dim3_Starry_Viewer_hxx
#define esve_viewers_dim3_Starry_Viewer_hxx

#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <memory>

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Starry_Viewer esve/viewers/dim3/Starry_Viewer.hxx
/// @brief A basic viewer with some stars.
///

class Starry_Viewer
    : public Basic_Viewer
{
private:
    typedef Basic_Viewer super ;

    Starry_Viewer( const Starry_Viewer & ) ;
    Starry_Viewer & operator=( const Starry_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    Starry_Viewer() ;

    engine::dim3::Camera &
    create_camera( const std::string & = default_camera_label,
                   const engine::dim3::Camera::Rectangle & =
                   default_camera_rectangle ) ;

    ///@{
    /// @brief Whether stars are showing.
    virtual bool stars_active() const ;
    virtual void stars_active( bool ) ;
    ///@}

    ~Starry_Viewer() ;

protected:
    // For derivation in Starry_Viewer subclasses
    class Private_Camera
        :
        public Basic_Viewer::Private_Camera
    {
    public:
        Private_Camera(
            const std::string &,
            const Camera::Rectangle &,
            Starry_Viewer & ) ;
        ~Private_Camera() ;

    private:
        friend class Starry_Viewer ;
        class Private ;
        std::auto_ptr<Private> m ;
    } ;
} ;

}}} // namespace esve::viewers::dim3

#endif
