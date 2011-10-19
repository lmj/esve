
#ifndef esve_ui_extra_Valuator_Creator_hxx
#define esve_ui_extra_Valuator_Creator_hxx

#include <string>

namespace esve { namespace ui { namespace extra {

class Valuator ;

class Valuator_Creator
{
public:
    /// Create a valuator.
    virtual
    Valuator &
    create_valuator( double initial_value,
                     const std::string & label = "" ) = 0 ;

    virtual ~Valuator_Creator() = 0 ;

protected:
    Valuator_Creator() ;

private:
    Valuator_Creator( const Valuator_Creator & ) ;
    Valuator_Creator & operator=( const Valuator_Creator & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

