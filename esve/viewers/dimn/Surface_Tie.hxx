

#ifndef esve_viewers_dimn_Surface_Tie_hxx
#define esve_viewers_dimn_Surface_Tie_hxx

#include <esve/viewers/dimn/Valuator_Effect.hxx>
#include <esve/components/dimn/Simple_UI_Tie.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>
#include <map>
#include <string>

namespace esve { namespace viewers { namespace dimn {

///
/// @if details
///
/// @class Surface_Tie esve/viewers/dimn/Surface_Tie.hxx
/// @brief Tie surface data/methods to a user-interface.
///
/// The UI's data is initialized from the struct or class.
///
/// @endif
///

template< typename T_Surface >
class Surface_Tie
    : public components::dimn::Valuator_Handler<types::real>,
      public components::dimn::Valuator_Handler<types::complex>,
      public components::dimn::Valuator_Handler<types::pure>,
      public components::dimn::Valuator_Handler<types::quat>
{
private:
    typedef components::dimn::Valuator_Handler<types::real> super ;

#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef void (T_Surface::*R)() ;
            R r1 = &T_Surface::update_domain ;
            R r2 = &T_Surface::update_domain_clip ;
            R r3 = &T_Surface::update_surface ;
            R r4 = &T_Surface::update_surface_clip ;
            R r5 = &T_Surface::update_color ;
            m_unused(r1) ;
            m_unused(r2) ;
            m_unused(r3) ;
            m_unused(r4) ;
            m_unused(r5) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    typedef T_Surface m_Surface ;
    typedef typename m_Surface::Spec m_Spec ;

    typedef std::map<const components::dimn::Valuator<types::real>*,
                     Valuator_Effect> m_Real_Map ;
    typedef std::pair<const components::dimn::Valuator<types::real>*,
                      Valuator_Effect> m_Real_Pair ;

    typedef std::map<const components::dimn::Valuator<types::complex>*,
                     Valuator_Effect> m_Complex_Map ;
    typedef std::pair<const components::dimn::Valuator<types::complex>*,
                      Valuator_Effect> m_Complex_Pair ;

    typedef std::map<const components::dimn::Valuator<types::pure>*,
                     Valuator_Effect> m_Pure_Map ;
    typedef std::pair<const components::dimn::Valuator<types::pure>*,
                      Valuator_Effect> m_Pure_Pair ;

    typedef std::map<const components::dimn::Valuator<types::quat>*,
                     Valuator_Effect> m_Quat_Map ;
    typedef std::pair<const components::dimn::Valuator<types::quat>*,
                      Valuator_Effect> m_Quat_Pair ;

    struct m_Tie : public components::dimn::Simple_UI_Tie<m_Spec>
    {
        m_Tie( components::dimn::Simple_UI & ui, m_Spec & target )
            : components::dimn::Simple_UI_Tie<m_Spec>(ui, target) { }

        using components::dimn::Simple_UI_Tie<m_Spec>::handle_valuator ;
    } ;

    Surface_Tie( const Surface_Tie & ) ;
    Surface_Tie & operator=( const Surface_Tie & ) ;

    void m_update_surface( Valuator_Effect ) ;

    m_Tie m_tie ;

    m_Real_Map m_real_map ;
    m_Complex_Map m_complex_map ;
    m_Pure_Map m_pure_map ;
    m_Quat_Map m_quat_map ;

    m_Surface & m_surface ;

public:
    typedef m_Surface Surface ;
    typedef m_Spec Spec ;

    typedef typename m_Tie::Real_Member Real_Member ;
    typedef typename m_Tie::Real_Reader Real_Reader ;
    typedef typename m_Tie::Real_Writer Real_Writer ;

    typedef typename m_Tie::Complex_Member Complex_Member ;
    typedef typename m_Tie::Complex_Reader Complex_Reader ;
    typedef typename m_Tie::Complex_Writer Complex_Writer ;

    typedef typename m_Tie::Pure_Member Pure_Member ;
    typedef typename m_Tie::Pure_Reader Pure_Reader ;
    typedef typename m_Tie::Pure_Writer Pure_Writer ;

    typedef typename m_Tie::Quat_Member Quat_Member ;
    typedef typename m_Tie::Quat_Reader Quat_Reader ;
    typedef typename m_Tie::Quat_Writer Quat_Writer ;

    Surface_Tie( components::dimn::Simple_UI & ui,
                 Spec & spec,
                 Surface & surface ) ;

    components::dimn::Valuator<types::real> &
    create_valuator( Real_Member,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::real> &
    create_valuator( Real_Reader,
                     Real_Writer,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::complex> &
    create_valuator( Complex_Member,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::complex> &
    create_valuator( Complex_Reader,
                     Complex_Writer,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::pure> &
    create_valuator( Pure_Member,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::pure> &
    create_valuator( Pure_Reader,
                     Pure_Writer,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::quat> &
    create_valuator( Quat_Member,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    components::dimn::Valuator<types::quat> &
    create_valuator( Quat_Reader,
                     Quat_Writer,
                     Valuator_Effect,
                     const std::string & name = "" ) ;

    ~Surface_Tie() ;

protected:
    bool handle_valuator(
        const components::dimn::Valuator<types::real> & ) ;
    bool handle_valuator(
        const components::dimn::Valuator<types::complex> & ) ;
    bool handle_valuator(
        const components::dimn::Valuator<types::pure> & ) ;
    bool handle_valuator(
        const components::dimn::Valuator<types::quat> & ) ;
} ;

}}} // namespace esve::viewers::dimn

#include <esve/viewers/dimn/Surface_Tie.template.cxx>

#endif

