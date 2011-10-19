
#ifndef esve_engine_dim3_Light_hxx
#define esve_engine_dim3_Light_hxx

#include <esve/engine/dim3/Frame_Stowed.hxx>
#include <esve/engine/dim3/Rendering_Error.hxx>
#include <esve/engine/dimn/Materials_Stowed.hxx>
#include <esve/message/impl/Draw_Node.hxx>
#include <memory>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Light esve/engine/dim3/Light.hxx
/// @brief An OpenGL light.
///
/// The light is applied to its child Draw_Receivers.
///
/// All materials default to (1,1,1,1).
///

class Light
    :
    virtual public engine::dimn::Materials_Stowed,
    virtual public Frame_Stowed,
    public message::impl::Draw_Node
{
public:
    struct Too_Many_Lights_Error
        : public Rendering_Error
    {
        int max_lights ;

        Too_Many_Lights_Error( int ) ; 
        ~Too_Many_Lights_Error() throw() ;
    } ;

    Light() ;
    
    ///@{
    const engine::dimn::Materials & peek_materials() const ;
    engine::dimn::Materials & peek_materials() ;
    ///@}

    ///@{
    const engine::dim3::Frame & peek_frame() const ;
    engine::dim3::Frame & peek_frame() ;
    ///@}

    ~Light() ;

protected:
    // Draw_Node override
    void send_draw() ;

private:
    typedef message::impl::Draw_Node super ;

    class Private ;
    const std::auto_ptr<Private> m ;

    Light( const Light & ) ;
    Light & operator=( const Light & ) ;
} ;

}}} // namespace esve::engine::dim3

#endif


