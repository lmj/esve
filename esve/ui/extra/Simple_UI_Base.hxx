
#ifndef esve_ui_extra_Simple_UI_Base_hxx
#define esve_ui_extra_Simple_UI_Base_hxx

#include <string>

namespace esve { namespace ui { namespace extra {

class File_Selector ;

///
/// @class Simple_UI_Base esve/ui/extra/Simple_UI_Base.hxx
/// @brief Undocumented base class.
///

class Simple_UI_Base
{
public:
    /// Label for widgets which follow.
    virtual void create_label( const std::string & label ) = 0 ;

    /// Create a file selector.  Just one file selector is allowed.
    virtual
    File_Selector &
    create_file_selector( const std::string & initial_value = "",
                          const std::string & label = "file",
                          const std::string & selector_label = "select a file",
                          const std::string & initial_directory = ".",
                          const std::string & filter = "*" ) = 0 ;

    /// Create a help dialog.
    virtual void create_help( const std::string & text,
                              const std::string & label = "help" ) = 0 ;

    virtual ~Simple_UI_Base() = 0 ;

protected:
    Simple_UI_Base() ;

private:
    Simple_UI_Base( const Simple_UI_Base & ) ;
    Simple_UI_Base & operator=( const Simple_UI_Base & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

