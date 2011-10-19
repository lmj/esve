
#ifndef esve_ui_extra_Widget_hxx
#define esve_ui_extra_Widget_hxx

namespace esve { namespace ui { namespace extra {

//
// @class Widget esve/ui/extra/Widget.hxx
// @brief A generic user-interface thingamajig.
//

class Widget
{
protected:
    Widget() ;

    // creator owns it
    virtual ~Widget() = 0 ;

private:
    Widget( const Widget & ) ;
    Widget & operator=( const Widget & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

