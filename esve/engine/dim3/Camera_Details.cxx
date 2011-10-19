
#include <esve/engine/dim3/Camera_Details.hxx>

namespace esve { namespace engine { namespace dim3 {

using types::real ;

Camera_Details::
~Camera_Details()
{
}

Camera_Details::
Camera_Details()
{
}

void
Camera_Details::
call_compute_projection( Camera_Details & camera )
{
    switch( camera.projection() )
    {
    case PERSPECTIVE:
        camera.compute_perspective_projection() ;
        break ;
    case ORTHOGONAL:
        camera.compute_orthogonal_projection() ;
        break ;
    case CUSTOM:
        camera.compute_custom_projection() ;
        break ;
    }
}

Camera_Details::
Orthogonal_Projection::
Orthogonal_Projection( real frustum_height_,
                       real near_clip_,
                       real far_clip_ )
    : frustum_height(frustum_height_),
      near_clip(near_clip_),
      far_clip(far_clip_)
{
}

Camera_Details::
Perspective_Projection::
Perspective_Projection( real field_of_view_,
                        real near_clip_,
                        real far_clip_ )
    : field_of_view(field_of_view_),
      near_clip(near_clip_),
      far_clip(far_clip_)
{
}

}}} // namespace esve::engine::dim3
