
#ifndef esve_viewers_dim3_Auto_Widgets_hxx
#define esve_viewers_dim3_Auto_Widgets_hxx

#include <esve/components/dimn/Valuator.hxx>
#include <esve/types/real.hxx>
#include <string>

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Auto_Widgets esve/viewers/dim3/Auto_Widgets.hxx
/// @brief Predefined widgets for three-dimensional viewers.
///

class Auto_Widgets
{
public:
    /// Create a scaling valuator.
    virtual
    components::dimn::Valuator<types::real> &
    create_scaling_valuator( const std::string & label = "scale" ) = 0 ;

    virtual ~Auto_Widgets() = 0 ;

protected:
    Auto_Widgets() ;

private:
    Auto_Widgets( const Auto_Widgets & ) ;
    Auto_Widgets & operator=( const Auto_Widgets & ) ;
} ;

}}} // namespace esve::viewers::dim3

#endif

