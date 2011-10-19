
#ifndef esve_ui_extra_Modal_Tie_hxx
#define esve_ui_extra_Modal_Tie_hxx

namespace esve { namespace ui { namespace extra {

///
/// @class Modal_Tie esve/ui/extra/Modal_Tie.hxx
/// @brief Tie modally to a display.
///

class Modal_Tie
{
public:
    /// Hide/show the tied modal object.
    virtual void toggle_modal_visible() = 0 ;

    /// Switch the tied display to/from fullscreen mode.
    virtual void toggle_display_fullscreen() = 0 ;

    virtual ~Modal_Tie() = 0 ;

protected:
    Modal_Tie() ;

private:
    Modal_Tie( const Modal_Tie & ) ;
    Modal_Tie & operator=( const Modal_Tie & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

