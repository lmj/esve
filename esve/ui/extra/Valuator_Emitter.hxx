
#ifndef esve_ui_extra_Valuator_Emitter_hxx
#define esve_ui_extra_Valuator_Emitter_hxx

#include <esve/ui/extra/Widget_Emitter.hxx>

namespace esve { namespace ui { namespace extra {

class Valuator ;

///
/// @class Valuator_Emitter esve/ui/extra/Valuator_Emitter.hxx
/// @brief Send handle_valuator().
///
/// @see Valuator_Handler
///

class Valuator_Emitter
    : public Widget_Emitter
{
public:
    ~Valuator_Emitter() ;

protected:
    Valuator_Emitter() ;

    /// @brief You have somehow obtained information that this widget
    /// has changed.  Inform the world by calling this method.
    virtual bool emit_valuator( const Valuator & ) ;

private:
    Valuator_Emitter( const Valuator_Emitter & ) ;
    Valuator_Emitter & operator=( const Valuator_Emitter & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

