
#include "UI.hxx"
#include "help/help_text.hxx"
#include <limits>

using esve::ui::base::Display ;

UI::
UI( Display & display )
    : Simple_UI(display),
      m_valuators(int(CAMERA_FOV) + 1),
      m_file_selector(0)
{
    create_help(help_text()) ;
    m_file_selector = &create_file_selector() ;

    m_valuators[CAMERA_ZPOS] = &create_valuator(0, "camera pos") ;
    m_valuators[CAMERA_FOV] = &create_valuator(0, "camera fov") ;
    m_valuators[SLIDE_COLOR] = &create_valuator(0, "slide color") ;
    m_valuators[BALL_RADIUS] = &create_valuator(0, "ball radius") ;
    m_valuators[TUBE_RADIUS] = &create_valuator(0, "tube radius") ;

    create_label("clip balls") ;
    m_valuators[CUT_BALLS_MIN] = &create_valuator(0) ;
    m_valuators[CUT_BALLS_MAX] = &create_valuator(0) ;

    create_label("clip edges") ;
    m_valuators[CUT_EDGES_MIN] = &create_valuator(0) ;
    m_valuators[CUT_EDGES_MAX] = &create_valuator(0) ;

    create_label("edge lengths") ;
    m_valuators[MIN_LENGTH] = &create_valuator(0) ;
    m_valuators[MAX_LENGTH] = &create_valuator(0) ;

    m_valuators[INVERSION] = &create_valuator(0, "inversion") ;

    const real max = std::numeric_limits<real>::max() ;

    valuator(INVERSION).step(0.002) ;
    valuator(INVERSION).range(0.0, 1.0) ;

    valuator(MIN_LENGTH).step(0.0002) ;
    valuator(MIN_LENGTH).range(0.0, max) ;

    valuator(MAX_LENGTH).step(0.0002) ;
    valuator(MAX_LENGTH).range(0.0, max) ;

    valuator(CUT_EDGES_MIN).step(0.005) ;
    valuator(CUT_EDGES_MIN).range(0.0, max) ;
    valuator(CUT_EDGES_MAX).step(0.005) ;
    valuator(CUT_EDGES_MAX).range(0.0, max) ;

    valuator(CUT_BALLS_MIN).step(0.005) ;
    valuator(CUT_BALLS_MIN).range(0.0, max) ;
    valuator(CUT_BALLS_MAX).step(0.005) ;
    valuator(CUT_BALLS_MAX).range(0.0, max) ;

    valuator(TUBE_RADIUS).step(0.0002) ;
    valuator(TUBE_RADIUS).range(0.0, max) ;

    valuator(BALL_RADIUS).step(0.0002) ;
    valuator(BALL_RADIUS).range(0.0, max) ;

    valuator(SLIDE_COLOR).step(0.0005) ;

    valuator(CAMERA_ZPOS).step(0.01) ;
    valuator(CAMERA_ZPOS).range(0.0, max) ;

    valuator(CAMERA_FOV).step(0.1) ;
    valuator(CAMERA_FOV).range(0.01, 179.9) ;
}

UI::
~UI()
{
}

