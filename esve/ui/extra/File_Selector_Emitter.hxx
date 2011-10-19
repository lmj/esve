
#ifndef esve_ui_extra_File_Selector_Emitter_hxx
#define esve_ui_extra_File_Selector_Emitter_hxx

#include <esve/ui/extra/Widget_Emitter.hxx>

namespace esve { namespace ui { namespace extra {

///
/// @class File_Selector_Emitter esve/ui/extra/File_Selector_Emitter.hxx
/// @brief Send handle_file_selector().
///
/// @see File_Selector_Handler
///

class File_Selector ;

class File_Selector_Emitter
    : public Widget_Emitter
{
public:
    ~File_Selector_Emitter() ;

protected:
    File_Selector_Emitter() ;

    /// @brief You have somehow obtained information that this widget
    /// has changed.  Inform the world by calling this method.
    virtual bool emit_file_selector( const File_Selector & ) ;

private:
    File_Selector_Emitter( const File_Selector_Emitter & ) ;
    File_Selector_Emitter & operator=( const File_Selector_Emitter & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

