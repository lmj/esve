
#ifndef esve_components_dim3_Z_Clipper_hxx
#define esve_components_dim3_Z_Clipper_hxx

#include <esve/message/impl/Compute_Receiver.hxx>
#include <esve/types/real.hxx>

namespace esve { namespace engine { namespace dim3 {

class Camera ;

}}} // namespace esve::engine::dim3

namespace esve { namespace components { namespace dim3 {

class Min_Z ;

///
/// @class Z_Clipper esve/components/dim3/Z_Clipper.hxx
/// @brief Automatically adjust a camera's far clip.
///

class Z_Clipper
    : virtual public message::impl::Compute_Receiver
{
public:
    /// Constructor.  Give the camera to be clipped and the object reporting a minimum z.
    Z_Clipper( engine::dim3::Camera &, const Min_Z & ) ;

    ///@{
    ///
    /// @brief Amount to change the far clip, when needed.
    ///
    types::real clip_step() const
    {
        return m_clip_step ;
    }

    void clip_step( types::real a )
    {
        m_clip_step = a ;
    }
    ///@}

    ///@{
    ///
    /// @brief clip_step() multiplier
    ///
    types::real scale() const
    {
        return m_scale ;
    }

    void scale( types::real a )
    {
        m_scale = a ;
    }
    ///@}

    ~Z_Clipper() ;

protected:
    void compute() ;

private:
    Z_Clipper( const Z_Clipper & ) ;
    Z_Clipper & operator=( const Z_Clipper & ) ;

    engine::dim3::Camera & m_camera ;
    const Min_Z & m_min_z ;
    types::real m_clip_step ;
    types::real m_scale ;
} ;

}}} // namespace esve::components::dim3

#endif

