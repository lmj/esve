
//
// I can use 'new' here frivolously since fltk supposedly doesn't
// throw exceptions.  But in any case I've given up on writing safe
// GUI code.
//

#include "UI.hxx"
#include "help/help_text.hxx"
#include <esve/platform/Representation.hxx>
#include <esve/platform/MF_Widget.hxx>
#include <esve/math/misc.hxx>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Value_Input.H>
#include <limits>
#include <memory>

using esve::platform::Representation ;
using esve::platform::MF_Widget ;
using esve::math::misc::fmodp ;

/////////////////////////////////////////////////////////////
//
// constants
//
/////////////////////////////////////////////////////////////

#ifdef WIN32
// strange behavior with sizes < 104
const int PANEL_WIDTH = 104 ;
const int PANEL_MARGIN = 12 ;
#else
const int PANEL_WIDTH = 100 ;
const int PANEL_MARGIN = 10 ;
#endif

const int PANEL_HEIGHT = 480 ;
const int HELP_WIDTH = 525 ;

const int CAMERA_WIDTH = 480 ;
const int CAMERA_HEIGHT = 480 ;
const std::string CAMERA_LABEL = "hopfviewer" ;

const std::string SQUARES_LABEL = "squares" ;
const std::string STRIPS_LABEL = "strips" ;
const std::string MANUAL_LABEL = "manual" ;

const std::string PANEL_LABEL = " " ;
const std::string HELP_LABEL = CAMERA_LABEL ;

/////////////////////////////////////////////////////////////
//
// UI::Private
//
/////////////////////////////////////////////////////////////

struct UI::Private
{
    struct Panel
        : public Fl_Window
    {
        UI::Private & m ;
        
        const std::string m_label ;
        
        Panel( int x,
               int y,
               const std::string & l,
               UI::Private & m_ )
            : Fl_Window(x, y, ""),
              m(m_),
              m_label(l)
        {
            Fl_Window::label(m_label.c_str()) ;
        }
        
        int handle( int fl_args )
        {
            int ret = Fl_Window::handle(fl_args) ;
            
            switch( fl_args )
            {
            case FL_FOCUS:
            case FL_UNFOCUS:
            case FL_KEYDOWN:
            case FL_KEYUP:
                // send key events to the camera
                m.camera->handle(fl_args) ;
                ret = 1 ;
            }
            
            return ret ;
        }
    } ;
        
    struct Camera_Stats
    {
        int x ;
        int y ;
        int w ;
        int h ;

        Camera_Stats( int x_,
                      int y_,
                      int w_,
                      int h_ )
            : x(x_),
              y(y_),
              w(w_),
              h(h_) { }
    } ;

    UI & outside ;
    Fl_Window* camera ;
    Camera_Stats camera_stats ;
    Fl_Text_Display* help_display ;
    std::auto_ptr<Fl_Text_Buffer> help_buffer ;
    std::auto_ptr<Panel> panel ;

    UI::Autoquad_Mode previous_autoquad_mode ;
    bool is_fullscreen ;

    Fl_Light_Button* cull_toggle ;
    void cull_toggle_callback() ;

    Fl_Light_Button* slide_surface_toggle ;
    void slide_surface_toggle_callback() ;

    Fl_Button* help_toggle ;
    void help_toggle_callback() ;

    Fl_Button* autoquad_toggle ;
    void autoquad_toggle_callback() ;

    Fl_Value_Input* ratio_angle ;
    void ratio_angle_callback() ;

    Fl_Value_Input* width ;
    void width_callback() ;

    Fl_Value_Input* height ;
    void height_callback() ;

    Fl_Value_Input* gap ;
    void gap_callback() ;

    Fl_Value_Input* width_res ;
    void width_res_callback() ;

    Fl_Value_Input* height_res ;
    void height_res_callback() ;

    Fl_Value_Input* skew ;
    void skew_callback() ;

    Fl_Value_Input* inversion ;
    void inversion_callback() ;

    Fl_Value_Input* scale ;
    void scale_callback() ;

    Fl_Value_Input* wind_u ;
    void wind_u_callback() ;

    Fl_Value_Input* wind_v ;
    void wind_v_callback() ;

    Fl_Value_Input* autoquad ;
    void autoquad_callback() ;

    Private( UI &, Fl_Window* ) ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

UI::Private::
Private( UI & outside_,
         Fl_Window* camera_ )
    : outside(outside_),
      camera(camera_),
      camera_stats(0, 0, 0, 0),
      help_display(0),
      help_buffer(0),
      panel(0),
      previous_autoquad_mode(UI::Autoquad_Mode(-1)),
      is_fullscreen(false),
      cull_toggle(0),
      slide_surface_toggle(0),
      help_toggle(0),
      autoquad_toggle(0),
      ratio_angle(0),
      width(0),
      height(0),
      gap(0),
      width_res(0),
      height_res(0),
      skew(0),
      inversion(0),
      scale(0),
      wind_u(0),
      wind_v(0),
      autoquad(0)
{
}

//////////////////////////////////////////////////
//
// UI
//
//////////////////////////////////////////////////

UI::
UI( esve::ui::base::Display & display )
    : m(new UI::Private(*this,
                        &Representation::rep(display)))
{
    m->is_fullscreen = false ;
    m->previous_autoquad_mode = AUTOQUAD_STRIPS ;

    const int x = PANEL_MARGIN ;
    int y = 5 ;
    const int dy = 36 ;
    const int button_dy = dy - 10 ;
    const int w = 80 ;
    const int h = 20 ;
    const double max = std::numeric_limits<double>::max() ;

    m->panel = std::auto_ptr<Private::Panel>(
        new Private::Panel(PANEL_WIDTH, PANEL_HEIGHT, PANEL_LABEL, *m)) ;
    m->panel->end() ;
    m->panel->size_range(m->panel->w(), m->panel->h(),
                         m->panel->w(), m->panel->h()) ;
    m->panel->hide() ;

    m->help_display = new Fl_Text_Display(PANEL_WIDTH, 0,
                                          HELP_WIDTH, PANEL_HEIGHT) ;
    m->help_buffer = std::auto_ptr<Fl_Text_Buffer>(new Fl_Text_Buffer()) ;
    m->help_buffer->text(help_text().c_str()) ;
    m->help_display->buffer(m->help_buffer.get()) ;
    m->panel->add(*m->help_display) ;
    m->help_display->hide() ;

    m->help_toggle = new MF_Widget<Fl_Button, UI::Private>(
        x, y, w, h,
        "help",
        *m,&UI::Private::help_toggle_callback) ;
    m->help_toggle->align(FL_ALIGN_CENTER) ;
    m->help_toggle->labelsize(12) ;
    m->help_toggle->box(FL_ENGRAVED_BOX) ;
    m->panel->add(m->help_toggle) ;

    m->autoquad_toggle = new MF_Widget<Fl_Button, UI::Private>(
        x, (y=y+dy-10), w, h,
        "squares",
        *m,&UI::Private::autoquad_toggle_callback) ;
    m->autoquad_toggle->align(FL_ALIGN_CENTER) ;
    m->autoquad_toggle->labelsize(12) ;
    m->autoquad_toggle->box(FL_ENGRAVED_BOX) ;
    m->panel->add(m->autoquad_toggle) ;

    m->autoquad = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+h), w, h,
        "",
        *m,&UI::Private::autoquad_callback) ;
    m->autoquad->align(FL_ALIGN_TOP) ;
    m->autoquad->labelsize(12) ;
    m->autoquad->step(10) ;
    m->autoquad->range(0, max) ;
    m->panel->add(m->autoquad) ;

    m->width = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "subdomain",
        *m,&UI::Private::width_callback) ;
    m->width->align(FL_ALIGN_TOP) ;
    m->width->labelsize(12) ;
    m->width->step(0.005) ;
    m->width->range(0, 1) ;
    m->panel->add(m->width) ;

    m->height = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+h), w, h,
        "",
        *m,&UI::Private::height_callback) ;
    m->height->align(FL_ALIGN_TOP) ;
    m->height->labelsize(12) ;
    m->height->step(0.005) ;
    m->height->range(0, 1) ;
    m->panel->add(m->height) ;

    m->wind_u = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "winding",
        *m,&UI::Private::wind_u_callback) ;
    m->wind_u->align(FL_ALIGN_TOP) ;
    m->wind_u->labelsize(12) ;
    m->wind_u->step(0.005) ;
    m->wind_u->range(0, max) ;
    m->panel->add(m->wind_u) ;

    m->wind_v = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+h), w, h,
        "",
        *m,&UI::Private::wind_v_callback) ;
    m->wind_v->align(FL_ALIGN_TOP) ;
    m->wind_v->labelsize(12) ;
    m->wind_v->step(0.005) ;
    m->wind_v->range(0, max) ;
    m->panel->add(m->wind_v) ;

    m->ratio_angle = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "ratio angle",
        *m,&UI::Private::ratio_angle_callback) ;
    m->ratio_angle->align(FL_ALIGN_TOP) ;
    m->ratio_angle->labelsize(12) ;
    m->ratio_angle->step(0.1) ;
    m->ratio_angle->range(-max, max) ;
    m->panel->add(m->ratio_angle) ;

    m->inversion = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "inversion",
        *m,&UI::Private::inversion_callback) ;
    m->inversion->align(FL_ALIGN_TOP) ;
    m->inversion->labelsize(12) ;
    m->inversion->step(0.002) ;
    m->inversion->range(0, 1) ;
    m->panel->add(m->inversion) ;

    m->scale = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "scale",
        *m,&UI::Private::scale_callback) ;
    m->scale->align(FL_ALIGN_TOP) ;
    m->scale->labelsize(12) ;
    m->scale->step(0.005) ;
    m->scale->range(-max, max) ;
    m->panel->add(m->scale) ;

    m->gap = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "gap",
        *m,&UI::Private::gap_callback) ;
    m->gap->align(FL_ALIGN_TOP) ;
    m->gap->labelsize(12) ;
    m->gap->step(0.001) ;
    m->gap->range(0, max) ;
    m->panel->add(m->gap) ;

    m->width_res = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "",
        *m,&UI::Private::width_res_callback) ;
    m->width_res->align(FL_ALIGN_TOP) ;
    m->width_res->labelsize(12) ;
    m->width_res->step(1) ;
    m->width_res->range(1, max) ;
    m->panel->add(m->width_res) ;

    // make a label which is not grayed out
    Fl_Box* res_label= new MF_Widget<Fl_Box, UI::Private>(
        x, y, w, h,
        "resolution",
        *m, 0) ;
    res_label->align(FL_ALIGN_TOP) ;
    res_label->labelsize(12) ;
    m->panel->add(res_label) ;

    m->height_res = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+h), w, h,
        "",
        *m,&UI::Private::height_res_callback) ;
    m->height_res->align(FL_ALIGN_TOP) ;
    m->height_res->labelsize(12) ;
    m->height_res->step(1) ;
    m->height_res->range(1, max) ;
    m->panel->add(m->height_res) ;

    m->skew = new MF_Widget<Fl_Value_Input, UI::Private>(
        x, (y=y+dy), w, h,
        "",
        *m,&UI::Private::skew_callback) ;
    m->skew->align(FL_ALIGN_TOP) ;
    m->skew->labelsize(12) ;
    m->skew->step(0.0001) ;
    m->skew->range(-max, max) ;
    m->panel->add(m->skew) ;

    // make a label which is not grayed out
    Fl_Box* skew_label= new MF_Widget<Fl_Box, UI::Private>(
        x, y, w, h,
        "skew",
        *m, 0) ;
    skew_label->align(FL_ALIGN_TOP) ;
    skew_label->labelsize(12) ;
    m->panel->add(skew_label) ;

    m->slide_surface_toggle = new MF_Widget<Fl_Light_Button, UI::Private>(
        x, (y=y+button_dy), w, h,
        "align 4D",
        *m,&UI::Private::slide_surface_toggle_callback) ;
    m->slide_surface_toggle->align(FL_ALIGN_CENTER) ;
    m->slide_surface_toggle->labelsize(12) ;
    m->slide_surface_toggle->box(FL_ENGRAVED_BOX) ;
    m->panel->add(m->slide_surface_toggle) ;

    m->cull_toggle = new MF_Widget<Fl_Light_Button, UI::Private>(
        x, (y=y+button_dy), w, h,
        "hide back",
        *m,&UI::Private::cull_toggle_callback) ;
    m->cull_toggle->align(FL_ALIGN_CENTER) ;
    m->cull_toggle->labelsize(12) ;
    m->cull_toggle->box(FL_ENGRAVED_BOX) ;
    m->panel->add(m->cull_toggle) ;

    // make fltk show decimals by setting to nonzero first
    m->wind_u->value(1) ;
    m->wind_u->value(0) ;
    m->wind_v->value(1) ;
    m->wind_v->value(0) ;
    m->skew->value(1) ;
    m->skew->value(0) ;
    m->gap->value(1) ;
    m->gap->value(0) ;

    m->panel->hide() ;

    m->camera->show() ;
    m->panel->hide() ;
    m->panel->set_non_modal() ;
    m->panel->show() ;
    m->camera->show() ;
}

UI::
~UI()
{
    // children of m->panel are automatically deleted
}

//////////////////////////////////////////////////
// autoquad mode
//////////////////////////////////////////////////

UI::Autoquad_Mode
UI::
autoquad_mode() const
{
    if( m->autoquad_toggle->label() == STRIPS_LABEL )
    {
        return AUTOQUAD_STRIPS ;
    }
    else if( m->autoquad_toggle->label() == SQUARES_LABEL )
    {
        return AUTOQUAD_SQUARES ;
    }

    return AUTOQUAD_NONE ;
}

void
UI::
autoquad_mode( UI::Autoquad_Mode mode )
{
    if( mode == AUTOQUAD_SQUARES )
    {
        m->autoquad_toggle->label(SQUARES_LABEL.c_str()) ;
    }
    else if( mode == AUTOQUAD_STRIPS )
    {
        m->autoquad_toggle->label(STRIPS_LABEL.c_str()) ;
    }
    else if( mode == AUTOQUAD_NONE )
    {
        m->autoquad_toggle->label(MANUAL_LABEL.c_str()) ;
        m->autoquad->value(0) ;
    }

    m->autoquad->redraw() ;
}

/////////////////////////////////////////////////
// app-to-ui communication
//////////////////////////////////////////////////

void
UI::
toggle_display_fullscreen()
{
    if( m->is_fullscreen )
    {
        m->camera->fullscreen_off(m->camera_stats.x,
                                  m->camera_stats.y,
                                  m->camera_stats.w,
                                  m->camera_stats.h) ;
        m->camera->size_range(100, 100, 0, 0) ;

    }
    else
    {
        m->camera_stats.x = m->camera->x() ;
        m->camera_stats.y = m->camera->y() ;
        m->camera_stats.w = m->camera->w() ;
        m->camera_stats.h = m->camera->h() ;

        // win32 quirks.  by hiding and resizing we can make the
        // border disappear everywhere but the bottom, however there
        // is now a gap at the bottom of the screen.
        //cam->hide() ;
        //cam->resize(0, 0, Fl::w(), Fl::h()) ;

        m->camera->fullscreen() ;
    }

    m->camera->show() ;
    m->is_fullscreen = !m->is_fullscreen ;
}

void
UI::
signal_autoquad_insufficient()
{
    if( m->autoquad->color() != FL_RED )
    {
        m->autoquad->color(FL_RED) ;
        m->autoquad->redraw() ;
    }
}

void
UI::
signal_autoquad_sufficient()
{
    if( m->autoquad->color() == FL_RED )
    {
        m->autoquad->color(FL_BACKGROUND2_COLOR) ;
        m->autoquad->redraw() ;
    }
}

void
UI::
toggle_modal_visible()
{
    if( m->panel->shown() )
    {
        m->panel->hide() ;
    }
    else
    {
        m->panel->show() ;
        m->camera->show() ;
    }
}

void
UI::
signal_initialize_autoquad()
{
    m->autoquad_callback() ;
}

/////////////////////////////////////////////////
// callbacks
//////////////////////////////////////////////////

namespace {

// I don't understand why fltk allows values outside the range
void clamp( Fl_Valuator* v )
{
    v->value(v->clamp(v->value())) ;
}

} // anon namespace

void
UI::Private::
help_toggle_callback()
{
    if( panel->w() == PANEL_WIDTH + HELP_WIDTH )
    {
        help_display->hide() ;
        panel->resize(panel->x(), panel->y(),
                      PANEL_WIDTH, PANEL_HEIGHT) ;
        panel->size_range(panel->w(), panel->h(),
                          panel->w(), panel->h()) ;
        panel->label(PANEL_LABEL.c_str()) ;
        panel->redraw() ;
    }
    else
    {
        panel->resize(panel->x(), panel->y(),
                      PANEL_WIDTH + HELP_WIDTH, PANEL_HEIGHT) ;

        // I have been unable to make the window resizable with the
        // displayed text.  Apparently non_modal is the reason.
        // So, might as well make it official:
        panel->size_range(panel->w(), panel->h(),
                          panel->w(), panel->h()) ;

        panel->label(HELP_LABEL.c_str()) ;
        help_display->show() ;
        panel->redraw() ;
    }
}

void
UI::Private::
skew_callback()
{
    clamp(skew) ;
    outside.emit_widget(UI::SKEW) ;
}

void
UI::Private::
inversion_callback()
{
    clamp(inversion) ;
    outside.emit_widget(UI::INVERSION) ;
}

void
UI::Private::
scale_callback()
{
    clamp(scale) ;
    outside.emit_widget(UI::SCALE) ;
}

void
UI::Private::
wind_u_callback()
{
    clamp(wind_u) ;
    outside.emit_widget(UI::WIND_U) ;
}

void
UI::Private::
wind_v_callback()
{
    clamp(wind_v) ;
    outside.emit_widget(UI::WIND_V) ;
}

void
UI::Private::
width_res_callback()
{
    clamp(width_res) ;
    outside.emit_widget(UI::WIDTH_RES) ;
}

void
UI::Private::
height_res_callback()
{
    clamp(height_res) ;
    outside.emit_widget(UI::HEIGHT_RES) ;
}

void
UI::Private::
gap_callback()
{
    gap->value(fmodp(gap->value(), 1.0)) ;
    outside.emit_widget(UI::GAP) ;
}

void
UI::Private::
cull_toggle_callback()
{
    outside.emit_widget(UI::CULL_TOGGLE) ;
}

void
UI::Private::
ratio_angle_callback()
{
    ratio_angle->value(fmodp(ratio_angle->value(), 360.0)) ;
    outside.emit_widget(UI::RATIO_ANGLE) ;
}

void
UI::Private::
width_callback()
{
    clamp(width) ;
    outside.emit_widget(UI::WIDTH) ;
}

void
UI::Private::
height_callback()
{
    clamp(height) ;
    outside.emit_widget(UI::HEIGHT) ;
}

void
UI::Private::
slide_surface_toggle_callback()
{
    outside.emit_widget(UI::SLIDE_SURFACE_TOGGLE) ;
}

void
UI::Private::
autoquad_toggle_callback()
{
    if( outside.autoquad_mode() == UI::AUTOQUAD_STRIPS )
    {
        outside.autoquad_mode(UI::AUTOQUAD_SQUARES) ;
        outside.emit_autoquad_strips_to_squares() ;
    }
    else if( outside.autoquad_mode() == UI::AUTOQUAD_SQUARES )
    {
        outside.autoquad_mode(UI::AUTOQUAD_STRIPS) ;
        outside.emit_autoquad_squares_to_strips() ;
    }
}

void
UI::Private::
autoquad_callback()
{
    clamp(autoquad) ;

    if( autoquad->value() == 0.0 )
    {
        // turn off autoquading

        width_res->activate() ;
        height_res->activate() ;
        skew->activate() ;

        width->step(0.05) ;
        height->step(0.05) ;

        if( outside.autoquad_mode() != UI::AUTOQUAD_NONE )
        {
            previous_autoquad_mode = outside.autoquad_mode() ;
        }
        outside.autoquad_mode(UI::AUTOQUAD_NONE) ;
        outside.emit_autoquad_deactivated() ;
    }
    else
    {
        if( skew->active() )
        {
            // the previous value of autoquad was 0.0

            width_res->deactivate() ;
            height_res->deactivate() ;
            skew->deactivate() ;

            width->step(0.005) ;
            height->step(0.005) ;

            outside.autoquad_mode(previous_autoquad_mode) ;
            outside.emit_autoquad_activated() ;
        }
        else
        {
            outside.emit_widget(UI::AUTOQUAD) ;
        }
    }
}

//////////////////////////////////////////////////
// values
//////////////////////////////////////////////////

bool
UI::
cull_toggle() const
{
    return bool(m->cull_toggle->value()) ;
}

void
UI::
cull_toggle( bool a )
{
    m->cull_toggle->value(a) ;
}

bool
UI::
slide_surface_toggle() const
{
    return bool(m->slide_surface_toggle->value()) ;
}

void
UI::
slide_surface_toggle( bool a )
{
    m->slide_surface_toggle->value(a) ;
}

bool
UI::
help_toggle() const
{
    return bool(m->help_toggle->value()) ;
}

void
UI::
help_toggle( bool a )
{
    m->help_toggle->value(a) ;
}

double
UI::
ratio_angle() const
{
    return m->ratio_angle->value() ;
}

void
UI::
ratio_angle( double a )
{
    m->ratio_angle->value(a) ;
}

double
UI::
width() const
{
    return m->width->value() ;
}

void
UI::
width( double a )
{
    m->width->value(a) ;
}

void
UI::
width_range( double a, double b )
{
    m->width->range(a, b) ;
}

double
UI::
height() const
{
    return m->height->value() ;
}

void
UI::
height( double a )
{
    m->height->value(a) ;
}

void
UI::
height_range( double a, double b )
{
    m->height->range(a, b) ;
}

double
UI::
gap() const
{
    return m->gap->value() ;
}

void
UI::
gap( double a )
{
    m->gap->value(a) ;
}

int
UI::
width_res() const
{
    return int(m->width_res->value()) ;
}

void
UI::
width_res( int a )
{
    m->width_res->value(double(a)) ;
}

int
UI::
height_res() const
{
    return int(m->height_res->value()) ;
}

void
UI::
height_res( int a )
{
    m->height_res->value(double(a)) ;
}

double
UI::
skew() const
{
    return m->skew->value() ;
}

void
UI::
skew( double a )
{
    m->skew->value(a) ;
}

double
UI::
inversion() const
{
    return m->inversion->value() ;
}

void
UI::
inversion( double a )
{
    m->inversion->value(a) ;
}

double
UI::
scale() const
{
    return m->scale->value() ;
}

void
UI::
scale( double a )
{
    m->scale->value(a) ;
}

double
UI::
wind_u() const
{
    return m->wind_u->value() ;
}

void
UI::
wind_u( double a )
{
    m->wind_u->value(a) ;
}

double
UI::
wind_v() const
{
    return m->wind_v->value() ;
}

void
UI::
wind_v( double a )
{
    m->wind_v->value(a) ;
}

int
UI::
autoquad() const
{
    return int(m->autoquad->value()) ;
}

void
UI::
autoquad( int a )
{
    m->autoquad->value(double(a)) ;
}

