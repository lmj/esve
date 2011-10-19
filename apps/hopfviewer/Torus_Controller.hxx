
#ifndef apps_hopfviewer_Torus_Controller_hxx
#define apps_hopfviewer_Torus_Controller_hxx

#include "UI_Handler.hxx"

class UI ;
class Torus ;

class Torus_Controller
    : public UI_Handler
{
public:
    Torus_Controller( UI &, Torus & ) ;

protected:
    bool handle_widget( Widget ) ;
    bool handle_autoquad_strips_to_squares() ;
    bool handle_autoquad_squares_to_strips() ;
    bool handle_autoquad_activated() ;
    bool handle_autoquad_deactivated() ;

private:
    Torus_Controller( const Torus_Controller & ) ;
    Torus_Controller & operator=( const Torus_Controller & ) ;

    void m_set_resolution( int w, int h ) ;
    void m_regularize_skew() ;
    void m_autosquare() ;
    void m_autostrip() ;
    void m_autoquad() ;

    UI & m_ui ;
    Torus & m_torus ;
} ;

#endif

