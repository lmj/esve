
#ifndef esve_ui_extra_File_Selector_Handler_hxx
#define esve_ui_extra_File_Selector_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <memory>

namespace esve { namespace ui { namespace extra {

class File_Selector ;

///
/// @class File_Selector_Handler esve/ui/extra/File_Selector_Handler.hxx
/// @brief Receive handle_file_selector().
///
/// @see File_Selector_Emitter
///

class File_Selector_Handler
    : virtual public kernel::Handler
{
public:
    ~File_Selector_Handler() = 0 ;

protected:
    File_Selector_Handler() ;

    /// @typedef File_Selector
    /// @brief .
    typedef ui::extra::File_Selector File_Selector ;

    /// The filename has changed.
    virtual bool handle_file_selector( const File_Selector & ) = 0 ;

private:
    File_Selector_Handler( const File_Selector_Handler & ) ;
    File_Selector_Handler & operator=( const File_Selector_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::extra

#endif

