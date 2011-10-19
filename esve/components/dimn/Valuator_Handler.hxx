
#ifndef esve_components_dimn_Valuator_Handler_hxx
#define esve_components_dimn_Valuator_Handler_hxx

#include <esve/kernel/Handler.hxx>
#include <esve/message/Handle_Args.hxx>
#include <string>
#include <memory>

namespace esve { namespace components { namespace dimn {

template< typename T_Value > class Valuator_Emitter ;
template< typename T_Value > class Valuator ;

///
/// @class Valuator_Handler esve/components/dimn/Valuator_Handler.hxx
/// @brief Receive handle_valuator().
///
/// @see Valuator_Emitter
///

template< typename T_Value >
class Valuator_Handler
    : virtual public kernel::Handler
{
public:
    ~Valuator_Handler() ;

protected:
    Valuator_Handler() ;

    /// The valuator has changed.
    virtual bool handle_valuator( const Valuator<T_Value> & ) = 0 ;

private:
    Valuator_Handler( const Valuator_Handler & ) ;
    Valuator_Handler & operator=( const Valuator_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Valuator.template.cxx>

#endif

