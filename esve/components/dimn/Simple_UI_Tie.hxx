
#ifndef esve_components_dimn_Simple_UI_Tie_hxx
#define esve_components_dimn_Simple_UI_Tie_hxx

#include <esve/components/dimn/Valuator.hxx>
#include <esve/components/dimn/Valuator_Struct_Tie.hxx>
#include <esve/components/dimn/Valuator_Class_Tie.hxx>
#include <esve/components/dimn/Simple_UI.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @if details
///
/// @class Simple_UI_Tie esve/components/dimn/Simple_UI_Tie.hxx
/// @brief Tie class or struct data to a Simple_UI.
///
/// The valuator is initialized by the target (either by a data member
/// or by a reader method).
///
/// Make sure the tie is able to receive handle_valuator() messages.
///
/// @endif
///

////////////////////////////////////////////////////////////////
//
// Simple_UI_Tie
//
////////////////////////////////////////////////////////////////

template< typename T_Target >
class Simple_UI_Tie
    : public components::dimn::Valuator_Handler<types::real>,
      public components::dimn::Valuator_Handler<types::complex>,
      public components::dimn::Valuator_Handler<types::pure>,
      public components::dimn::Valuator_Handler<types::quat>
{
private:
    Simple_UI_Tie( const Simple_UI_Tie & ) ;
    Simple_UI_Tie & operator=( const Simple_UI_Tie & ) ;

    struct m_Tie
        :
        public Valuator_Struct_Tie<T_Target, types::real>,
        public Valuator_Struct_Tie<T_Target, types::complex>,
        public Valuator_Struct_Tie<T_Target, types::pure>,
        public Valuator_Struct_Tie<T_Target, types::quat>,

        public Valuator_Class_Tie<T_Target, types::real>,
        public Valuator_Class_Tie<T_Target, types::complex>,
        public Valuator_Class_Tie<T_Target, types::pure>,
        public Valuator_Class_Tie<T_Target, types::quat>
    {
        m_Tie( Simple_UI & ui, T_Target & target ) ;

        using Valuator_Struct_Tie<T_Target, types::real>::create_valuator ;
        using Valuator_Struct_Tie<T_Target, types::complex>::create_valuator ;
        using Valuator_Struct_Tie<T_Target, types::pure>::create_valuator ;
        using Valuator_Struct_Tie<T_Target, types::quat>::create_valuator ;

        using Valuator_Class_Tie<T_Target, types::real>::create_valuator ;
        using Valuator_Class_Tie<T_Target, types::complex>::create_valuator ;
        using Valuator_Class_Tie<T_Target, types::pure>::create_valuator ;
        using Valuator_Class_Tie<T_Target, types::quat>::create_valuator ;

        using Valuator_Struct_Tie<T_Target, types::real>::tie ;
        using Valuator_Struct_Tie<T_Target, types::complex>::tie ;
        using Valuator_Struct_Tie<T_Target, types::pure>::tie ;
        using Valuator_Struct_Tie<T_Target, types::quat>::tie ;

        using Valuator_Class_Tie<T_Target, types::real>::tie ;
        using Valuator_Class_Tie<T_Target, types::complex>::tie ;
        using Valuator_Class_Tie<T_Target, types::pure>::tie ;
        using Valuator_Class_Tie<T_Target, types::quat>::tie ;

        bool handle_valuator( const Valuator<types::real> & ) ;
        bool handle_valuator( const Valuator<types::complex> & ) ;
        bool handle_valuator( const Valuator<types::pure> & ) ;
        bool handle_valuator( const Valuator<types::quat> & ) ;
    } ;

    m_Tie m_tie ;

public:
    typedef T_Target Target ;

    ///@{
    /// @name Data members.
    /// @brief For example 'real foo' is a Real_Member.
    typedef types::real Target::* Real_Member ;
    typedef types::complex Target::* Complex_Member ;
    typedef types::pure Target::* Pure_Member ;
    typedef types::quat Target::* Quat_Member ;
    ///@}

    ///@{
    /// @name Reader/writer methods.
    ///
    /// @brief For example 'real foo() const' is a Real_Reader and
    /// 'void foo( real )' is a Real_Writer.
    ///
    typedef types::real (Target::*Real_Reader)() const ;
    typedef void (Target::*Real_Writer)( types::real ) ;

    typedef const types::complex & (Target::*Complex_Reader)() const ;
    typedef void (Target::*Complex_Writer)( const types::complex & ) ;

    typedef const types::pure & (Target::*Pure_Reader)() const ;
    typedef void (Target::*Pure_Writer)( const types::pure & ) ;

    typedef const types::quat & (Target::*Quat_Reader)() const ;
    typedef void (Target::*Quat_Writer)( const types::quat & ) ;
    ///@}

    /// Constructor.
    Simple_UI_Tie( components::dimn::Simple_UI & ui,
                   Target & data ) ;

    ///@{
    ///
    /// @brief Fuse this data member with a new valuator.
    ///
    Valuator<types::real> &
    create_valuator( Real_Member member,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, name) ;
    }

    Valuator<types::complex> &
    create_valuator( Complex_Member member,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, name) ;
    }

    Valuator<types::pure> &
    create_valuator( Pure_Member member,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, name) ;
    }

    Valuator<types::quat> &
    create_valuator( Quat_Member member,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, name) ;
    }
    ///@}

    ///@{
    ///
    /// @brief Fuse this reader/writer pair with a new valuator.
    ///
    Valuator<types::real> &
    create_valuator( Real_Reader reader,
                     Real_Writer writer,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, name) ;
    }

    Valuator<types::complex> &
    create_valuator( Complex_Reader reader,
                     Complex_Writer writer,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, name) ;
    }

    Valuator<types::pure> &
    create_valuator( Pure_Reader reader,
                     Pure_Writer writer,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, name) ;
    }

    Valuator<types::quat> &
    create_valuator( Quat_Reader reader,
                     Quat_Writer writer,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, name) ;
    }
    ///@}

    ///@{
    ///
    /// @brief Fuse this data member with an existing valuator.
    ///
    void tie( Valuator<types::real> & valuator,
              Real_Member member )
    {
        m_tie.tie(valuator, member) ;
    }

    void tie( Valuator<types::complex> & valuator,
              Complex_Member member )
    {
        m_tie.tie(valuator, member) ;
    }

    void tie( Valuator<types::pure> & valuator,
              Pure_Member member )
    {
        m_tie.tie(valuator, member) ;
    }

    void tie( Valuator<types::quat> & valuator,
              Quat_Member member )
    {
        m_tie.tie(valuator, member) ;
    }
    ///@}

    ///@{
    ///
    /// @brief Fuse this reader/writer pair with an existing valuator.
    ///
    void tie( Valuator<types::real> & valuator,
              Real_Reader reader,
              Real_Writer writer )
    {
        m_tie.tie(valuator, reader, writer) ;
    }

    void tie( Valuator<types::complex> & valuator,
              Complex_Reader reader,
              Complex_Writer writer )
    {
        m_tie.tie(valuator, reader, writer) ;
    }

    void tie( Valuator<types::pure> & valuator,
              Pure_Reader reader,
              Pure_Writer writer )
    {
        m_tie.tie(valuator, reader, writer) ;
    }

    void tie( Valuator<types::quat> & valuator,
              Quat_Reader reader,
              Quat_Writer writer )
    {
        m_tie.tie(valuator, reader, writer) ;
    }
    ///@}

    ~Simple_UI_Tie() ;

protected:
    bool handle_valuator( const Valuator<types::real> & v ) ;
    bool handle_valuator( const Valuator<types::complex> & v ) ;
    bool handle_valuator( const Valuator<types::pure> & v ) ;
    bool handle_valuator( const Valuator<types::quat> & v ) ;
} ;

}}} // namespace esve::components::dimn

#include <esve/components/dimn/Simple_UI_Tie.template.cxx>

#endif

