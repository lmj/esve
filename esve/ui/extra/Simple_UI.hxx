
#ifndef esve_ui_extra_Simple_UI_hxx
#define esve_ui_extra_Simple_UI_hxx

#include <esve/ui/extra/Simple_UI_Base.hxx>
#include <esve/ui/extra/Toggle_Creator.hxx>
#include <esve/ui/extra/Toggle_Emitter.hxx>
#include <esve/ui/extra/Valuator_Creator.hxx>
#include <esve/ui/extra/Valuator_Emitter.hxx>
#include <esve/ui/extra/File_Selector_Emitter.hxx>
#include <esve/ui/extra/Modal_Tie.hxx>
#include <esve/kernel/Catcher.hxx>
#include <string>
#include <memory>

namespace esve { namespace ui { namespace base { class Display ; } } }

namespace esve { namespace ui { namespace extra {

///
/// @class Simple_UI esve/ui/extra/Simple_UI.hxx
/// @brief A simple user-interface.
///
/// Valuators, toggles, a file selector, and a help dialog.
///

class Simple_UI
    :
    virtual public Simple_UI_Base,
    virtual public extra::Toggle_Creator,
    virtual public extra::Valuator_Creator,
    virtual public kernel::Catcher,
    virtual public Modal_Tie,
    public Valuator_Emitter,
    public Toggle_Emitter,
    public File_Selector_Emitter
{
public:
    /// Constructor.  A display is needed for the modal tie.
    Simple_UI( ui::base::Display & ) ;

    ///
    /// @brief Create a valuator.
    ///
    /// @code Valuator & v = create_valuator(0.5, "foo") @endcode
    /// is equivalent to
    /// @code
    /// create_label("foo") ;
    /// Valuator & v = create_valuator(0.5) ;
    /// @endcode
    ///
    Valuator &
    create_valuator( double initial_value,
                     const std::string & label = "" ) ;

    void create_label( const std::string & label ) ;

    Toggle & create_toggle( bool initial_value, const std::string & label ) ;

    File_Selector &
    create_file_selector( const std::string & initial_value = "",
                          const std::string & label = "file",
                          const std::string & selector_label = "select a file",
                          const std::string & initial_directory = ".",
                          const std::string & filter = "*" ) ;

    void create_help( const std::string & text,
                      const std::string & label = "help" ) ;

    void toggle_display_fullscreen() ;
    void toggle_modal_visible() ;

    Catch_Function catch_function() const ;
    void catch_function( Catch_Function ) ;

    ~Simple_UI() ;

private:
    Simple_UI( const Simple_UI & ) ;
    Simple_UI & operator=( const Simple_UI & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::extra

#endif

