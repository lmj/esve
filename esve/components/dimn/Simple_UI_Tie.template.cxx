
#include <esve/components/dimn/Simple_UI_Tie.hxx>

namespace esve { namespace components { namespace dimn {

template< typename T_Target >
Simple_UI_Tie<T_Target>::m_Tie::
m_Tie( Simple_UI & ui, T_Target & target )
    :
    Valuator_Struct_Tie<T_Target, types::real>(ui, target),
    Valuator_Struct_Tie<T_Target, types::complex>(ui, target),
    Valuator_Struct_Tie<T_Target, types::pure>(ui, target),
    Valuator_Struct_Tie<T_Target, types::quat>(ui, target),

    Valuator_Class_Tie<T_Target, types::real>(ui, target),
    Valuator_Class_Tie<T_Target, types::complex>(ui, target),
    Valuator_Class_Tie<T_Target, types::pure>(ui, target),
    Valuator_Class_Tie<T_Target, types::quat>(ui, target)
{
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::m_Tie::
handle_valuator( const Valuator<types::real> & v )
{
    return
        Valuator_Struct_Tie<T_Target, types::real>::handle_valuator(v)
        ||
        Valuator_Class_Tie<T_Target, types::real>::handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::m_Tie::
handle_valuator( const Valuator<types::complex> & v )
{
    return
        Valuator_Struct_Tie<T_Target, types::complex>::handle_valuator(v)
        ||
        Valuator_Class_Tie<T_Target, types::complex>::handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::m_Tie::
handle_valuator( const Valuator<types::pure> & v )
{
    return
        Valuator_Struct_Tie<T_Target, types::pure>::handle_valuator(v)
        ||
        Valuator_Class_Tie<T_Target, types::pure>::handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::m_Tie::
handle_valuator( const Valuator<types::quat> & v )
{
    return
        Valuator_Struct_Tie<T_Target, types::quat>::handle_valuator(v)
        ||
        Valuator_Class_Tie<T_Target, types::quat>::handle_valuator(v) ;
}

template< typename T_Target >
Simple_UI_Tie<T_Target>::
Simple_UI_Tie( components::dimn::Simple_UI & ui,
               Target & data )
    : m_tie(ui, data)
{
}

template< typename T_Target >
Simple_UI_Tie<T_Target>::
~Simple_UI_Tie()
{
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::
handle_valuator( const Valuator<types::real> & v )
{
    return m_tie.handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::
handle_valuator( const Valuator<types::complex> & v )
{
    return m_tie.handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::
handle_valuator( const Valuator<types::pure> & v )
{
    return m_tie.handle_valuator(v) ;
}

template< typename T_Target >
bool
Simple_UI_Tie<T_Target>::
handle_valuator( const Valuator<types::quat> & v )
{
    return m_tie.handle_valuator(v) ;
}

}}} // namespace esve::components::dimn
