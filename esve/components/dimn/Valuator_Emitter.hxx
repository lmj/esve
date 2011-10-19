
#ifndef esve_components_dimn_Valuator_Emitter_hxx
#define esve_components_dimn_Valuator_Emitter_hxx

#include <esve/ui/extra/Widget_Emitter.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Valuator_Emitter esve/components/dimn/Valuator_Emitter.hxx
/// @brief Send handle_valuator().
///
/// @see Valuator_Handler
///

template< typename T_Value > class Valuator ;

template< typename T_Value >
class Valuator_Emitter
    : public ui::extra::Widget_Emitter
{
public:
    ~Valuator_Emitter() ;

protected:
    Valuator_Emitter() ;

    /// @brief You have somehow obtained information that this widget
    /// has changed.  Inform the world by calling this method.
    virtual bool emit_valuator( const Valuator<T_Value> & ) ;

private:
    Valuator_Emitter( const Valuator_Emitter & ) ;
    Valuator_Emitter & operator=( const Valuator_Emitter & ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Valuator.template.cxx>

#endif

