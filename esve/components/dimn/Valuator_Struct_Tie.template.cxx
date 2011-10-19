
#include <esve/components/dimn/Valuator_Struct_Tie.hxx>
#include <esve/components/dimn/Valuator_Creator.hxx>
#include <esve/components/dimn/Valuator.hxx>

namespace esve { namespace components { namespace dimn {

template< typename T_Target,
          typename T_Value_Type >
Valuator_Struct_Tie<T_Target,
                    T_Value_Type>::
Valuator_Struct_Tie( Valuator_Creator<Value_Type> & ui,
                     Target & data )
    : super(),
      m_ui(ui),
      m_target(data),
      m_map()
{
}

template< typename T_Target,
          typename T_Value_Type  >
Valuator_Struct_Tie<T_Target,
                    T_Value_Type>::
~Valuator_Struct_Tie()
{
}

template< typename T_Target,
          typename T_Value_Type  >
Valuator<T_Value_Type> &
Valuator_Struct_Tie<T_Target,
                    T_Value_Type>::
create_valuator( Member member, const std::string & name )
{
    Valuator<Value_Type> & valuator =
        m_ui.create_valuator(m_target.*member, name) ;
    m_map.insert(m_Pair(&valuator, member)) ;
    return valuator ;
}

template< typename T_Target,
          typename T_Value_Type  >
void
Valuator_Struct_Tie<T_Target,
                    T_Value_Type>::
tie( Valuator<Value_Type> & valuator, Member member )
{
    valuator.value(m_target.*member) ;
    m_map.insert(m_Pair(&valuator, member)) ;
}

template< typename T_Target,
          typename T_Value_Type  >
bool
Valuator_Struct_Tie<T_Target,
                    T_Value_Type>::
handle_valuator( const Valuator<Value_Type> & valuator )
{
    bool handled = false ;

    // const_cast is harmless since we just use the pointer value
    // without dereferencing.
    m_Map_const_iterator i =
        m_map.find(const_cast<Valuator<Value_Type>*>(&valuator)) ;

    if( i != m_map.end() )
    {
        m_target.*((*i).second) = valuator.value() ;
        handled = true ;
    }

    return handled ;
}

}}} // namespace esve::components::dimn
