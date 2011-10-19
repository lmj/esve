
#ifndef esve_ui_extra_Toggle_Creator_hxx
#define esve_ui_extra_Toggle_Creator_hxx

#include <string>

namespace esve { namespace ui { namespace extra {

///
/// @class Toggle_Creator esve/ui/extra/Toggle_Creator.hxx
/// @brief Create toggles.
///

class Toggle ;

class Toggle_Creator
{
public:
    /// Create a toggle.
    virtual
    Toggle &
    create_toggle( bool initial_value, const std::string & label ) = 0 ;

    virtual ~Toggle_Creator() = 0 ;

protected:
    Toggle_Creator() ;

private:
    Toggle_Creator( const Toggle_Creator & ) ;
    Toggle_Creator & operator=( const Toggle_Creator & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

