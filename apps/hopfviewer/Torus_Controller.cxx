
#include "Torus_Controller.hxx"
#include "UI.hxx"
#include "Torus.hxx"
#include "torus_func.hxx"
#include <esve/math/misc.hxx>
#include <esve/math/constants.hxx>
#include <cmath>

using esve::math::misc::rad2deg ;
using esve::math::misc::deg2rad ;
using esve::math::misc::round ;

const double PI_4 = double(esve::math::constants::PI_4) ;

Torus_Controller::
Torus_Controller( UI & ui, Torus & torus )
    : m_ui(ui),
      m_torus(torus)
{
    // Ideally one would set ui parameters then manually call
    // handle(), however the autoquad feature requires a particular
    // initial state.  Set everything manually.

    m_torus.wind_u(12) ;
    m_torus.wind_v(11) ;
    m_torus.width_res(1) ;
    m_torus.height_res(2500) ;
    m_torus.width(m_torus.width_res()*2.0/3.0) ;
    m_torus.height(m_torus.height_res()) ;
    m_torus.ratio_angle(PI_4) ;
    m_torus.gap(0.0) ;

    m_ui.wind_u(m_torus.wind_u()) ;
    m_ui.wind_v(m_torus.wind_v()) ;
    m_ui.width_res(m_torus.width_res()) ;
    m_ui.height_res(m_torus.height_res()) ;
    m_ui.width(m_torus.width()) ;
    m_ui.height(m_torus.height()) ;
    m_ui.ratio_angle(rad2deg(m_torus.ratio_angle())) ;
    m_ui.gap(m_torus.gap()) ;
    m_ui.cull_toggle(false) ;
    m_ui.slide_surface_toggle(false) ;
    m_ui.autoquad_mode(UI::AUTOQUAD_STRIPS) ;
    m_ui.autoquad(m_torus.height_res()) ;
}

bool
Torus_Controller::
handle_widget( Widget widget )
{
    switch( widget )
    {
    case UI::SKEW:
        {
            m_torus.skew(m_ui.skew()) ;
        }
        return true ;

    case UI::WIND_U:
        {
            m_torus.wind_u(m_ui.wind_u()) ;
            m_autoquad() ;
        }
        return true ;

    case UI::WIND_V:
        {
            m_torus.wind_v(m_ui.wind_v()) ;
            m_autoquad() ;
        }
        return true ;

    case UI::WIDTH_RES:
        {
            m_set_resolution(m_ui.width_res(),
                             m_torus.height_res()) ;
        }
        return true ;

    case UI::HEIGHT_RES:
        {
            m_set_resolution(m_torus.width_res(),
                             m_ui.height_res()) ;
        }
        return true ;

    case UI::GAP:
        {
            m_torus.gap(m_ui.gap()) ;
        }
        return true ;

    case UI::RATIO_ANGLE:
        {
            m_torus.ratio_angle(deg2rad(m_ui.ratio_angle())) ;
            m_autoquad() ;
        }
        return true ;

    case UI::WIDTH:
        {
            if( m_ui.autoquad_mode() == UI::AUTOQUAD_NONE )
            {
                // absolute measure
                m_torus.width(m_ui.width()) ;
            }
            else
            {
                // percentage
                m_torus.width(m_ui.width()*m_torus.width_res()) ;
                
                // autoquad again? keeps resolution constant but
                // has has a jumpy feel.
                //m_autoquad() ;
            }
        }
        return true ;

    case UI::HEIGHT:
        {
            if( m_ui.autoquad_mode() == UI::AUTOQUAD_NONE )
            {
                // absolute measure
                m_torus.height(m_ui.height()) ;
            }
            else
            {
                // percentage
                m_torus.height(m_ui.height()*m_torus.height_res()) ;

                // autoquad again? keeps resolution constant but
                // has has a jumpy feel.
                //m_autoquad() ;
            }
        }
        return true ;

    case UI::AUTOQUAD:
        {
            if( m_ui.autoquad_mode() == UI::AUTOQUAD_STRIPS )
            {
                // possibly turn off the insufficient flag
                m_ui.signal_autoquad_sufficient() ;
            }

            m_autoquad() ;
        }
        return true ;

    default:
        ;
    }

    return false ;
}

bool
Torus_Controller::
handle_autoquad_strips_to_squares()
{
    m_autoquad() ;
    return true ;
}

bool
Torus_Controller::
handle_autoquad_squares_to_strips()
{
    m_ui.signal_autoquad_sufficient() ;
    m_autoquad() ;
    return true ;
}

bool
Torus_Controller::
handle_autoquad_activated()
{
    // convert to percentage width/height

    if( m_torus.width_res() == 0 || m_torus.height_res() == 0 )
    {
        return true ;
    }

    m_ui.width(m_ui.width()/m_torus.width_res()) ;
    m_ui.width_range(0, 1) ;

    m_ui.height(m_ui.height()/m_torus.height_res()) ;
    m_ui.height_range(0, 1) ;

    m_autoquad() ;

    return true ;
}

bool
Torus_Controller::
handle_autoquad_deactivated()
{
    // convert to absolute width/height

    m_ui.width(m_ui.width()*m_torus.width_res()) ;
    m_ui.width_range(0, m_torus.width_res()) ;

    m_ui.height(m_ui.height()*m_torus.height_res()) ;
    m_ui.height_range(0, m_torus.height_res()) ;

    // possibly turn off the insufficient flag
    m_ui.signal_autoquad_sufficient() ;

    return true ;
}

void
Torus_Controller::
m_set_resolution( int w, int h )
{
    double frac_w = 0.0 ;
    double frac_h = 0.0 ;

    if( m_torus.width_res() != 0 )
    {
        frac_w = m_torus.width()/m_torus.width_res() ;
    }
    if( m_torus.height_res() != 0 )
    {
        frac_h = m_torus.height()/m_torus.height_res() ;
    }

    m_torus.width_res(w) ;
    m_ui.width_res(w) ;

    m_torus.height_res(h) ;
    m_ui.height_res(h) ;

    if( frac_w == 0.0 || frac_h == 0.0 )
    {
        return ;
    }

    if( m_ui.autoquad_mode() == UI::AUTOQUAD_NONE )
    {
        // absolute

        m_torus.width(frac_w*w) ;
        m_ui.width_range(0, w) ;
        m_ui.width(m_torus.width()) ;

        m_torus.height(frac_h*h) ;
        m_ui.height_range(0, h) ;
        m_ui.height(m_torus.height()) ;
    }
    else
    {
        // percentage

        m_torus.width(m_ui.width()*w) ;
        m_torus.height(m_ui.height()*h) ;
    }
}

void
Torus_Controller::
m_regularize_skew()
{
    const double r1 = std::fabs(std::cos(m_torus.ratio_angle())) ;
    const double r2 = std::fabs(std::sin(m_torus.ratio_angle())) ;

    if( (r1 == 0.0 && r2 == 0.0) ||
        (m_torus.wind_u() == 0.0 && m_torus.wind_v() == 0.0) )
    {
        return ;
    }

    const double skew =
        torus_func::regularized_skew(std::abs(std::cos(m_torus.ratio_angle())),
                                     std::abs(std::sin(m_torus.ratio_angle())),
                                     m_torus.wind_u(),
                                     m_torus.wind_v()) ;

    m_torus.skew(skew) ;
    m_ui.skew(m_torus.skew()) ;
}

void
Torus_Controller::
m_autostrip()
{
    if( m_torus.height_res() == 0 ||
        m_torus.height() == 0 )
    {
        return ;
    }

    const double frac_h = m_torus.height()/m_torus.height_res() ;
    m_set_resolution(
        1,
        int(round(double(m_ui.autoquad())/frac_h))) ;
    m_regularize_skew() ;
}

void
Torus_Controller::
m_autosquare()
{
    if( m_torus.width_res() == 0 ||
        m_torus.height_res() == 0 ||
        m_torus.width() == 0 ||
        m_torus.height() == 0 ||
        m_ui.ratio_angle() == 0 ||
        (m_torus.wind_u() == 0 &&
         m_torus.wind_v() == 0) )
    {
        return ;
    }

    // account for partial domain
    //const double frac_w = m_torus.width()/m_torus.width_res() ;
    //const double frac_h = m_torus.height()/m_torus.height_res() ;

    // compute as if full domain is showing
    const double frac_w = 1.0 ;
    const double frac_h = 1.0 ;

    const double r1 = std::fabs(std::cos(m_torus.ratio_angle())) ;
    const double r2 = std::fabs(std::sin(m_torus.ratio_angle())) ;

    if( r1 == 0.0 || r2 == 0.0 )
    {
        return ;
    }

    const double t =
        torus_func::regularized_slope(r1, r2,
                                      m_torus.wind_u(),
                                      m_torus.wind_v()) ;

    const double area = double(m_ui.autoquad())/(frac_w*frac_h) ;
    const int w = int(std::sqrt(area/t)) ;
    const int h = int(round(w*t)) ;

    if( w == 0 || h == 0 )
    {
        m_ui.signal_autoquad_insufficient() ;
    }
    else
    {
        m_ui.signal_autoquad_sufficient() ;
        m_set_resolution(w, h) ;
        m_regularize_skew() ;
    }
}

void
Torus_Controller::
m_autoquad()
{
    if( m_ui.autoquad_mode() != UI::AUTOQUAD_NONE )
    {
        if( m_ui.autoquad_mode() == UI::AUTOQUAD_SQUARES )
        {
            m_autosquare() ;
        }
        else
        {
            m_autostrip() ;
        }
    }
}

