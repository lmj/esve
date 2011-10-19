
#ifndef esve_components_dimn_Valuator_Struct_Tie_hxx
#define esve_components_dimn_Valuator_Struct_Tie_hxx

#include <esve/components/dimn/Valuator_Handler.hxx>
#include <string>
#include <map>

namespace esve { namespace components { namespace dimn {

template< typename T_Value > class Valuator_Creator ;

//
// @class Valuator_Struct_Tie esve/components/dimn/Valuator_Struct_Tie.hxx
// @brief Tie valuators to a struct.
//
// Whenever a valuator changes, the corresponding data member is
// updated.  The initial value is read from the data member.
//
// Make sure the tie is able to receive handle_valuator() messages.
//

template< typename T_Target,
          typename T_Value_Type >
class Valuator_Struct_Tie
    : public Valuator_Handler<T_Value_Type>
{
private:
    typedef Valuator_Handler<T_Value_Type> super ;

    typedef T_Target m_Target ;
    typedef T_Value_Type m_Value_Type ;

    typedef m_Value_Type m_Target::* m_Member ;
    typedef std::map<Valuator<m_Value_Type>*, m_Member> m_Map ;
    typedef std::pair<Valuator<m_Value_Type>*, m_Member> m_Pair ;
    typedef typename m_Map::iterator m_Map_iterator ;
    typedef typename m_Map::const_iterator m_Map_const_iterator ;

    Valuator_Struct_Tie( const Valuator_Struct_Tie & ) ;
    Valuator_Struct_Tie & operator=( const Valuator_Struct_Tie & ) ;

    Valuator_Creator<m_Value_Type> & m_ui ;
    m_Target & m_target ;
    m_Map m_map ;

public:
    typedef m_Target Target ;
    typedef m_Member Member ;
    typedef m_Value_Type Value_Type ;

    /// Constructor.
    Valuator_Struct_Tie( Valuator_Creator<Value_Type> & ui,
                         Target & data ) ;

    /// Fuse this data member with a new valuator.
    Valuator<Value_Type> &
    create_valuator( Member, const std::string & name = "" ) ;

    /// Fuse this data member with an existing valuator.
    void tie( Valuator<Value_Type> &, Member ) ;

    ~Valuator_Struct_Tie() ;

protected:
    bool handle_valuator( const Valuator<Value_Type> & ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Valuator_Struct_Tie.template.cxx>

#endif

