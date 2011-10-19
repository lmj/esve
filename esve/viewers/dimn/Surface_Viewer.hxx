
#ifndef esve_viewers_dimn_Surface_Viewer_hxx
#define esve_viewers_dimn_Surface_Viewer_hxx

#include <esve/viewers/dimn/Surface_Tie.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>
#include <string>

namespace esve { namespace viewers { namespace dimn {

///
/// @if details
///
/// @class Surface_Viewer esve/viewers/dimn/Surface_Viewer.hxx
/// @brief Simple_Viewer specialized for surfaces.
///
/// @endif
///

template< typename T_Spec >
class Surface_Viewer
      // i.e., Simple_Viewer
    : public T_Spec::Viewer
{
private:
    typedef typename T_Spec::Viewer super ;
    typedef T_Spec m_Spec ;
    typedef typename m_Spec::Surface_Spec m_Surface_Spec ;
    typedef typename m_Spec::Surface m_Surface ;

    typedef
    Surface_Tie<m_Surface>
    m_Tie ;

    typedef typename super::Toggle m_Toggle ;
    typedef typename m_Surface::Facets_size_type m_size_type ;

    Surface_Viewer( const Surface_Viewer & ) ;
    Surface_Viewer & operator=( const Surface_Viewer & ) ;

    m_Surface_Spec m_surface_spec ;
    m_Surface m_surface ;
    m_Tie m_tie ;
    m_Toggle* m_hide_back ;
    components::dimn::Valuator<types::complex>* m_res_valuator ;

public:
    Surface_Viewer( int argc,
                    char** argv,
                    const std::string & name = "surface viewer" ) ;

protected:
    typedef m_Spec Spec ;
    typedef m_Surface_Spec Surface_Spec ;
    typedef m_Toggle Toggle ;
    typedef m_size_type size_type ;

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

    static const Valuator_Effect CHANGES_DOMAIN =
       valuator_effect::CHANGES_DOMAIN ;

    static const Valuator_Effect CHANGES_DOMAIN_CLIP =
       valuator_effect::CHANGES_DOMAIN_CLIP ;

    static const Valuator_Effect CHANGES_SURFACE =
       valuator_effect::CHANGES_SURFACE ;

    static const Valuator_Effect CHANGES_SURFACE_CLIP =
       valuator_effect::CHANGES_SURFACE_CLIP ;

    static const Valuator_Effect CHANGES_COLOR =
       valuator_effect::CHANGES_COLOR ;

    components::dimn::Valuator<types::real> &
    create_valuator( Real_Member member,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, effect, name) ;
    }

    components::dimn::Valuator<types::real> &
    create_valuator( Real_Reader reader,
                     Real_Writer writer,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, effect, name) ;
    }

    components::dimn::Valuator<types::complex> &
    create_valuator( Complex_Member member,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, effect, name) ;
    }

    components::dimn::Valuator<types::complex> &
    create_valuator( Complex_Reader reader,
                     Complex_Writer writer,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, effect, name) ;
    }

    components::dimn::Valuator<types::pure> &
    create_valuator( Pure_Member member,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, effect, name) ;
    }

    components::dimn::Valuator<types::pure> &
    create_valuator( Pure_Reader reader,
                     Pure_Writer writer,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, effect, name) ;
    }

    components::dimn::Valuator<types::quat> &
    create_valuator( Quat_Member member,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(member, effect, name) ;
    }

    components::dimn::Valuator<types::quat> &
    create_valuator( Quat_Reader reader,
                     Quat_Writer writer,
                     Valuator_Effect effect,
                     const std::string & name = "" )
    {
        return m_tie.create_valuator(reader, writer, effect, name) ;
    }

    using super::create_valuator ;

    components::dimn::Valuator<types::complex> &
    create_resolution_valuator( const std::string & name = "resolution" ) ;

    // in case the user doesn't want to create the resolution valuator
    void resolution( size_type width, size_type height ) ;

    Toggle &
    create_hide_back_toggle( const std::string & name = "hide back" ) ;

    bool handle_toggle( const Toggle & ) ;

    bool handle_valuator(
        const components::dimn::Valuator<types::complex> & ) ;
    using super::handle_valuator ;

    ~Surface_Viewer() ;
} ;

}}} // namespace esve::viewers::dimn

#include <esve/viewers/dimn/Surface_Viewer.template.cxx>

#endif

