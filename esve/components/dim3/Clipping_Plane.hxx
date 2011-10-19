
#ifndef esve_components_dim3_Clipping_Plane_hxx
#define esve_components_dim3_Clipping_Plane_hxx

#include <esve/engine/dim3/Rendering_Error.hxx>
#include <esve/engine/dim3/Frame_Stowed.hxx>
#include <esve/message/impl/Draw_Node.hxx>
#include <memory>

namespace esve { namespace components { namespace dim3 {

///
/// @class Clipping_Plane esve/components/dim3/Clipping_Plane.hxx
/// @brief An extra clipping plane.
///
/// The frame's local x-y plane is the clipping plane; anything on the
/// side of the negative local z-axis is clipped.
///
/// The clipping plane applies to all Draw_Receiver children.
///

class Clipping_Plane
    : public engine::dim3::Frame_Stowed,
      public message::impl::Draw_Node
{
private:
    typedef message::impl::Draw_Node super ;

    Clipping_Plane( const Clipping_Plane & ) ;
    Clipping_Plane & operator=( const Clipping_Plane & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    struct Too_Many_Clipping_Planes_Error
        : public engine::dim3::Rendering_Error
    {
        int max_clip_planes ;

        Too_Many_Clipping_Planes_Error( int ) ; 
        ~Too_Many_Clipping_Planes_Error() throw() ;
    } ;
    
    Clipping_Plane() ;

    ///@{
    const engine::dim3::Frame & peek_frame() const ;
    engine::dim3::Frame & peek_frame() ;
    ///@}

   ~Clipping_Plane() ;

protected:
    // Draw_Node override
    void send_draw() ;
} ;

}}} // namespace esve::components::dim3

#endif


