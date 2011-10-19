
#include <esve/components/dim3/Z_Clipper.hxx>
#include <esve/components/dim3/Min_Z.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dim3/Transform.hxx>
#include <esve/engine/dim3/Camera_Details.hxx>
#include <esve/engine/dim3/Camera.hxx>
#include <cmath>

namespace esve { namespace components { namespace dim3 {

Z_Clipper::
Z_Clipper( engine::dim3::Camera & camera,
           const Min_Z & min_z )
    : m_camera(camera),
      m_min_z(min_z),
      m_clip_step(100.0),
      m_scale(1.0)
{
}

Z_Clipper::
~Z_Clipper()
{
}

void
Z_Clipper::
compute()
{
    const double farthest =
        std::abs(m_camera.peek_frame().peek_transform().translation().z() -
                 m_min_z.min_z()) ;
    double clip_step = m_clip_step ;

    if( m_scale != 0 )
    {
        if( std::abs(m_scale) > 1 )
        {
            clip_step *= std::abs(m_scale) ;
        }

        if( farthest > m_camera.peek_camera_details().far_clip() )
        {
            m_camera.peek_camera_details().far_clip(farthest + clip_step) ;
        }
        else if( m_camera.peek_camera_details().far_clip()
                 >
                 farthest + clip_step )
        {
            m_camera.peek_camera_details().far_clip(farthest + 1) ;
        }
    }
}

}}} // namespace esve::components::dim3
