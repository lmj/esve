
#ifndef esve_ui_extra_Toggle_Emitter_hxx
#define esve_ui_extra_Toggle_Emitter_hxx

#include <esve/ui/extra/Widget_Emitter.hxx>

namespace esve { namespace ui { namespace extra {

///
/// @class Toggle_Emitter esve/ui/extra/Toggle_Emitter.hxx
/// @brief Send handle_toggle().
///
/// @see Toggle_Handler 
///

class Toggle ;

class Toggle_Emitter
    : public Widget_Emitter
{
public:
    ~Toggle_Emitter() ;

protected:
    Toggle_Emitter() ;

    /// @brief You have somehow obtained information that this widget
    /// has changed.  Inform the world by calling this method.
    virtual bool emit_toggle( const Toggle & ) ;

private:
    Toggle_Emitter( const Toggle_Emitter & ) ;
    Toggle_Emitter & operator=( const Toggle_Emitter & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

