
#include <esve/viewers/dimn/Surface_Tie.hxx>
#include <cassert>

namespace esve { namespace viewers { namespace dimn {

////////////////////////////////////////////////////////////////
//
// Surface_Tie
//
////////////////////////////////////////////////////////////////

template< typename T_Surface >
Surface_Tie<T_Surface>::
Surface_Tie( components::dimn::Simple_UI & ui,
             Spec & spec,
             Surface & surface )
    : super(),
      m_tie(ui, spec),
      m_real_map(),
      m_complex_map(),
      m_pure_map(),
      m_quat_map(),
      m_surface(surface)
{
}

template< typename T_Surface >
Surface_Tie<T_Surface>::
~Surface_Tie()
{
}

template< typename T_Surface >
components::dimn::Valuator<types::real> &
Surface_Tie<T_Surface>::
create_valuator( Real_Member member,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::real> & valuator =
        m_tie.create_valuator(member, name) ;
    m_real_map.insert(m_Real_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::real> &
Surface_Tie<T_Surface>::
create_valuator( Real_Reader reader,
                 Real_Writer writer,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::real> & valuator =
        m_tie.create_valuator(reader, writer, name) ;
    m_real_map.insert(m_Real_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::complex> &
Surface_Tie<T_Surface>::
create_valuator( Complex_Member member,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::complex> & valuator =
        m_tie.create_valuator(member, name) ;
    m_complex_map.insert(m_Complex_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::complex> &
Surface_Tie<T_Surface>::
create_valuator( Complex_Reader reader,
                 Complex_Writer writer,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::complex> & valuator =
        m_tie.create_valuator(reader, writer, name) ;
    m_complex_map.insert(m_Complex_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::pure> &
Surface_Tie<T_Surface>::
create_valuator( Pure_Member member,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::pure> & valuator =
        m_tie.create_valuator(member, name) ;
    m_pure_map.insert(m_Pure_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::pure> &
Surface_Tie<T_Surface>::
create_valuator( Pure_Reader reader,
                 Pure_Writer writer,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::pure> & valuator =
        m_tie.create_valuator(reader, writer, name) ;
    m_pure_map.insert(m_Pure_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::quat> &
Surface_Tie<T_Surface>::
create_valuator( Quat_Member member,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::quat> & valuator =
        m_tie.create_valuator(member, name) ;
    m_quat_map.insert(m_Quat_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
components::dimn::Valuator<types::quat> &
Surface_Tie<T_Surface>::
create_valuator( Quat_Reader reader,
                 Quat_Writer writer,
                 Valuator_Effect effect,
                 const std::string & name )
{
    components::dimn::Valuator<types::quat> & valuator =
        m_tie.create_valuator(reader, writer, name) ;
    m_quat_map.insert(m_Quat_Pair(&valuator, effect)) ;
    return valuator ;
}

template< typename T_Surface >
bool
Surface_Tie<T_Surface>::
handle_valuator( const components::dimn::Valuator<types::real> & valuator )
{
    bool handled = m_tie.handle_valuator(valuator) ;

    if( handled )
    {
        typename m_Real_Map::const_iterator i =
            m_real_map.find(&valuator) ;
        assert(i != m_real_map.end()) ;
        m_update_surface((*i).second) ;
    }

    return handled ;
}

template< typename T_Surface >
bool
Surface_Tie<T_Surface>::
handle_valuator( const components::dimn::Valuator<types::complex> & valuator )
{
    bool handled = m_tie.handle_valuator(valuator) ;

    if( handled )
    {
        typename m_Complex_Map::const_iterator i =
            m_complex_map.find(&valuator) ;
        assert(i != m_complex_map.end()) ;
        m_update_surface((*i).second) ;
    }

    return handled ;
}

template< typename T_Surface >
bool
Surface_Tie<T_Surface>::
handle_valuator( const components::dimn::Valuator<types::pure> & valuator )
{
    bool handled = m_tie.handle_valuator(valuator) ;

    if( handled )
    {
        typename m_Pure_Map::const_iterator i =
            m_pure_map.find(&valuator) ;
        assert(i != m_pure_map.end()) ;
        m_update_surface((*i).second) ;
    }

    return handled ;
}

template< typename T_Surface >
bool
Surface_Tie<T_Surface>::
handle_valuator( const components::dimn::Valuator<types::quat> & valuator )
{
    bool handled = m_tie.handle_valuator(valuator) ;

    if( handled )
    {
        typename m_Quat_Map::const_iterator i =
            m_quat_map.find(&valuator) ;
        assert(i != m_quat_map.end()) ;
        m_update_surface((*i).second) ;
    }

    return handled ;
}

template< typename T_Surface >
void
Surface_Tie<T_Surface>::
m_update_surface( Valuator_Effect effect )
{
    switch( effect )
    {
    case valuator_effect::CHANGES_DOMAIN:
        m_surface.update_domain() ;
        break ;

    case valuator_effect::CHANGES_DOMAIN_CLIP:
        m_surface.update_domain_clip() ;
        break ;

    case valuator_effect::CHANGES_SURFACE:
        m_surface.update_surface() ;
        break ;

    case valuator_effect::CHANGES_SURFACE_CLIP:
        m_surface.update_surface_clip() ;
        break ;

    case valuator_effect::CHANGES_COLOR:
        m_surface.update_color() ;
        break ;
    }
}

}}} // namespace esve::viewers::dimn
