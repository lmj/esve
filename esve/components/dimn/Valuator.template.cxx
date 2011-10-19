
#ifndef esve_components_dimn_Valuator_template_cxx
#define esve_components_dimn_Valuator_template_cxx

#include <esve/components/dimn/Valuator_Handler.hxx>
#include <esve/components/dimn/Valuator_Emitter.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

namespace valuator_private {

template< typename T_Value >
struct Valuator_Handle_Args : public message::Handle_Args
{
    const Valuator<T_Value> & valuator ;
    
    Valuator_Handle_Args( const Valuator<T_Value> & valuator_ )
        : Handle_Args(),
          valuator(valuator_) { }
    
    Valuator_Handle_Args( const Valuator_Handle_Args & a )
        : Handle_Args(),
          valuator(a.valuator) { }
    
    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new Valuator_Handle_Args(valuator)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(&valuator) ;
        esve_report(valuator.value()) ;
    }
#endif
} ;

} // namespace valuator_private

template< typename T_Value >
struct Valuator_Handler<T_Value>::Private
    : public message::impl::Handle_Receiver
{
    Valuator_Handler<T_Value> & outside ;

    Private( Valuator_Handler<T_Value> & outside_ )
        : outside(outside_) { }

    bool handle( const message::Handle_Args & ) ;
} ;

/////////////////////////////////////////////////////////////////////

template< typename T_Value >
Valuator_Handler<T_Value>::
Valuator_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

template< typename T_Value >
Valuator_Handler<T_Value>::
~Valuator_Handler()
{
}

template< typename T_Value >
bool
Valuator_Handler<T_Value>::Private::
handle( const message::Handle_Args & generic_args )
{
    typedef valuator_private::Valuator_Handle_Args<T_Value> Args ;

    bool handled = false ;

    if( const Args* valuator_args = dynamic_cast<const Args*>(&generic_args) )
    {
        handled = outside.handle_valuator(valuator_args->valuator) ;
    }

    return handled ;
}

/////////////////////////////////////////////////////////////////////

template< typename T_Value >
Valuator_Emitter<T_Value>::
Valuator_Emitter()
{
}

template< typename T_Value >
Valuator_Emitter<T_Value>::
~Valuator_Emitter()
{
}

template< typename T_Value >
bool
Valuator_Emitter<T_Value>::
emit_valuator( const Valuator<T_Value> & valuator )
{
    typedef valuator_private::Valuator_Handle_Args<T_Value> Args ;

    return emit_widget(valuator, Args(valuator)) ;
}

}}} // namespace esve::components::dimn

#endif
