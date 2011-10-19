
#ifndef esve_viewers_dim3_impl_Auto_Widgets_hxx
#define esve_viewers_dim3_impl_Auto_Widgets_hxx

#include <esve/viewers/dim3/Auto_Widgets.hxx>
#include <esve/components/dimn/Valuator_Handler.hxx>
#include <esve/types/real.hxx>
#include <string>
#include <memory>

namespace esve { namespace components { namespace dimn {

template< typename T_Value > class Valuator ;
template< typename T_Value > class Valuator_Creator ;

}}} // namespace esve::components::dimn

namespace esve { namespace viewers { namespace dimn { class Scaling ; } } }

namespace esve { namespace viewers { namespace dim3 { namespace impl {

///
/// @class Auto_Widgets esve/viewers/dim3/impl/Auto_Widgets.hxx
/// @brief Implements viewers::dim3::Auto_Widgets.
///

class Auto_Widgets
    : virtual public viewers::dim3::Auto_Widgets,
      public components::dimn::Valuator_Handler<types::real>
{
public:
    Auto_Widgets( components::dimn::Valuator_Creator<types::real> & ui,
                  dimn::Scaling & frame ) ;

    components::dimn::Valuator<types::real> &
    create_scaling_valuator( const std::string & label = "scale" ) ;

    ~Auto_Widgets() ;

protected:
    bool handle_valuator( const components::dimn::Valuator<types::real> & ) ;

private:
    Auto_Widgets( const Auto_Widgets & ) ;
    Auto_Widgets & operator=( const Auto_Widgets & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}}} // namespace esve::viewers::dim3::impl

#endif

