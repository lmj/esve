
#include <esve/viewers/dimn/Surface_Viewer.hxx>
#include <esve/components/dimn/Valuator.hxx>
#include <esve/ui/extra/Toggle.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace viewers { namespace dimn {

template< typename T_Spec >
Surface_Viewer<T_Spec>::
Surface_Viewer( int argc,
                char** argv,
                const std::string & name )
    : super(argc, argv, name),
      m_surface_spec(),
      m_surface(m_surface_spec),
      m_tie(*this, m_surface_spec, m_surface),
      m_hide_back(0),
      m_res_valuator(0)
{
    super::add_geom(m_surface) ;
    super::add_handler(m_tie) ;
    m_surface.resolution(20, 20) ;
}

template< typename T_Spec >
Surface_Viewer<T_Spec>::
~Surface_Viewer()
{
}

template< typename T_Spec >
components::dimn::Valuator<types::complex> &
Surface_Viewer<T_Spec>::
create_resolution_valuator( const std::string & name )
{
    assert(m_res_valuator == 0 && "Only one resolution valuator allowed") ;

    if( m_res_valuator == 0 )
    {
        const types::real max = std::numeric_limits<types::real>::max() ;

        components::dimn::Valuator_Creator<types::complex> & ui = *this ;

        m_res_valuator =
            &
            ui.
            create_valuator(types::complex(m_surface.width_resolution(),
                                           m_surface.height_resolution()),
                            name).
            range(types::complex(0, 0), types::complex(max, max)).
            step(1, 1) ;
    }

    return *m_res_valuator ;
}

template< typename T_Spec >
void
Surface_Viewer<T_Spec>::
resolution( size_type width, size_type height )
{
    m_surface.resolution(width, height) ;
}

template< typename T_Spec >
typename Surface_Viewer<T_Spec>::Toggle &
Surface_Viewer<T_Spec>::
create_hide_back_toggle( const std::string & name )
{
    assert(m_hide_back == 0 && "Only one hide_back_toggle allowed") ;

    if( m_hide_back == 0 )
    {
        m_hide_back = &super::create_toggle(false, name) ;
    }

    return *m_hide_back ;
}

template< typename T_Spec >
bool
Surface_Viewer<T_Spec>::
handle_toggle( const Toggle & toggle )
{
    bool handled = super::handle_toggle(toggle) ;

    if( m_hide_back == &toggle )
    {
        if( toggle.value() )
        {
            glEnable(GL_CULL_FACE) ;
        }
        else
        {
            glDisable(GL_CULL_FACE) ;
        }

        handled = true ;
    }

    return handled ;
}

template< typename T_Spec >
bool
Surface_Viewer<T_Spec>::
handle_valuator( const components::dimn::Valuator<types::complex> & valuator )
{
    bool handled = super::handle_valuator(valuator) ;

    if( m_res_valuator == &valuator )
    {
        typedef typename m_Surface::Facets_size_type size_type ;

        m_surface.resolution(size_type(m_res_valuator->value().real()),
                             size_type(m_res_valuator->value().imag())) ;
        handled = true ;
    }

    return handled ;
}

}}} // namespace esve::viewers::dimn
