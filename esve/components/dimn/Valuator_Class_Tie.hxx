
#ifndef esve_components_dimn_Valuator_Class_Tie_hxx
#define esve_components_dimn_Valuator_Class_Tie_hxx

#include <esve/components/dimn/Valuator_Handler.hxx>
#include <esve/types/real.hxx>
#include <string>
#include <map>

namespace esve { namespace components { namespace dimn {

template< typename T_Value > class Valuator_Creator ;

//
// @class Valuator_Class_Tie esve/components/dimn/Valuator_Class_Tie.hxx
// @brief Tie valuators to a class.
//
// Whenever a valuator changes, the corresponding writer method is
// called.  The initial value is taken from the reader method.
//
// Make sure the tie is able to receive handle_valuator() messages.
//

template< typename T_Target,
          typename T_Value_Type >
class Valuator_Class_Tie
    : public Valuator_Handler<T_Value_Type>
{
private:
    typedef Valuator_Handler<T_Value_Type> super ;

    typedef T_Target m_Target ;
    typedef T_Value_Type m_Value_Type ;

    typedef const m_Value_Type & (m_Target::*m_Reader)() const ;
    typedef void (m_Target::*m_Writer)( const m_Value_Type & ) ;

    struct m_Node
    {
        m_Reader reader ;
        m_Writer writer ;

        m_Node( m_Reader r,
                m_Writer w )
            : reader(r),
              writer(w) { }
    } ;

    typedef std::map<Valuator<m_Value_Type>*, m_Node> m_Map ;
    typedef std::pair<Valuator<m_Value_Type>*, m_Node> m_Pair ;
    typedef typename m_Map::iterator m_Map_iterator ;
    typedef typename m_Map::const_iterator m_Map_const_iterator ;

    Valuator_Class_Tie( const Valuator_Class_Tie & ) ;
    Valuator_Class_Tie & operator=( const Valuator_Class_Tie & ) ;

    Valuator_Creator<m_Value_Type> & m_ui ;
    m_Target & m_target ;
    m_Map m_map ;

public:
    typedef m_Target Target ;
    typedef m_Reader Reader ;
    typedef m_Writer Writer ;
    typedef m_Value_Type Value_Type ;

    /// Constructor.
    Valuator_Class_Tie( Valuator_Creator<Value_Type> & ui,
                        Target & data ) ;

    /// Fuse this reader/writer method pair with a new valuator.
    Valuator<Value_Type> &
    create_valuator( Reader,
                     Writer,
                     const std::string & name = "" ) ;

    /// Fuse this reader/writer method pair with an existing valuator.
    void tie( Valuator<Value_Type> &, Reader, Writer ) ;

    ~Valuator_Class_Tie() ;

protected:
    bool handle_valuator( const Valuator<Value_Type> & ) ;
} ;

//
// Specialization for real.
//
// We want
//
//    real foo() const ;
//    void foo( real ) ;
//
// and not
//
//    const real & foo() const ;
//    void foo( const real & ) ;
//
template< typename T_Target >
class Valuator_Class_Tie<T_Target, types::real>
    : public Valuator_Handler<types::real>
{
private:
    typedef Valuator_Handler<types::real> super ;

    typedef T_Target m_Target ;

    typedef types::real (m_Target::*m_Reader)() const ;
    typedef void (m_Target::*m_Writer)( types::real ) ;

    struct m_Node
    {
        m_Reader reader ;
        m_Writer writer ;

        m_Node( m_Reader r,
                m_Writer w )
            : reader(r),
              writer(w) { }
    } ;

    typedef std::map<Valuator<types::real>*, m_Node> m_Map ;
    typedef std::pair<Valuator<types::real>*, m_Node> m_Pair ;
    typedef typename m_Map::iterator m_Map_iterator ;
    typedef typename m_Map::const_iterator m_Map_const_iterator ;

    Valuator_Class_Tie( const Valuator_Class_Tie & ) ;
    Valuator_Class_Tie & operator=( const Valuator_Class_Tie & ) ;

    Valuator_Creator<types::real> & m_ui ;
    m_Target & m_target ;
    m_Map m_map ;

public:
    typedef m_Target Target ;
    typedef m_Reader Reader ;
    typedef m_Writer Writer ;

    /// Constructor.
    Valuator_Class_Tie( Valuator_Creator<types::real> & ui,
                        Target & data ) ;

    /// Fuse this reader/writer method pair with a new valuator.
    Valuator<types::real> &
    create_valuator( Reader,
                     Writer,
                     const std::string & name = "" ) ;

    /// Fuse this reader/writer method pair with an existing valuator.
    void tie( Valuator<types::real> &, Reader, Writer ) ;

    ~Valuator_Class_Tie() ;

protected:
    bool handle_valuator( const Valuator<types::real> & ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Valuator_Class_Tie.template.cxx>

#endif

