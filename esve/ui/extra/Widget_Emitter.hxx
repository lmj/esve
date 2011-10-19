
#ifndef esve_ui_extra_Widget_Emitter_hxx
#define esve_ui_extra_Widget_Emitter_hxx

#include <esve/kernel/Emitter.hxx>
#include <memory>

namespace esve { namespace message { class Handle_Args ; } }

namespace esve { namespace ui { namespace extra {

//
// @class Widget_Emitter esve/ui/extra/Widget_Emitter.hxx
// @brief Undocumented base class.
//
// Blocks handle()-recursion on the same widget.
//

class Widget ;

class Widget_Emitter
    : virtual public kernel::Emitter
{
public:
    ~Widget_Emitter() ;

protected:
    Widget_Emitter() ;

    virtual bool emit_widget( const Widget &,
                              const message::Handle_Args & ) ;

private:
    Widget_Emitter( const Widget_Emitter & ) ;
    Widget_Emitter & operator=( const Widget_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::extra

#endif

