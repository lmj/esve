
#ifndef esve_components_dimn_Simple_UI_hxx
#define esve_components_dimn_Simple_UI_hxx

#include <esve/components/dimn/Valuator_Creator.hxx>
#include <esve/ui/extra/Toggle_Creator.hxx>
#include <esve/ui/extra/Simple_UI_Base.hxx>
#include <esve/kernel/Catcher.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Simple_UI esve/components/dimn/Simple_UI.hxx
/// @brief A simple user-interface.
///

class Simple_UI
    : virtual public Valuator_Creator<types::real>,
      virtual public Valuator_Creator<types::complex>,
      virtual public Valuator_Creator<types::pure>,
      virtual public Valuator_Creator<types::quat>,
      virtual public ui::extra::Simple_UI_Base,
      virtual public ui::extra::Toggle_Creator,
      virtual public kernel::Catcher
{
public:
    ~Simple_UI() = 0 ;
    
protected:
    Simple_UI() ;

private:
    Simple_UI( const Simple_UI & ) ;
    Simple_UI & operator=( const Simple_UI & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

