
//
// I can use 'new' here frivolously since fltk supposedly doesn't
// throw exceptions.  But in any case I've given up on writing safe
// GUI code.
//

#include "UI.hxx"
#include "help/help_text.hxx"
#include <esve/platform/Representation.hxx>
#include <esve/platform/MF_Widget.hxx>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <vector>
#include <sstream>

using esve::platform::MF_Widget ;
using esve::ui::base::Display ;
using esve::platform::Representation ;

const int HELP_HEIGHT = 400 ;
const int HELP_WIDTH = 500 ;

//////////////////////////////////////////////
//
// UI::Private
//
//////////////////////////////////////////////

struct Help_Data
{
    std::auto_ptr<Fl_Text_Buffer> buffer ;
    std::auto_ptr<Fl_Window> window ;
    Fl_Text_Display* display ;
    Fl_Button* button ;

    Help_Data()
        : buffer(0),
          window(0),
          display(0),
          button(0) { }

private:
    Help_Data( const Help_Data & ) ;
    Help_Data & operator=( const Help_Data & ) ;
} ;

struct UI::Private
{
    UI & outside ;
    Fl_Window* camera ;
    std::vector<double> coeffs_vec ;
    Help_Data help_data ;
    std::auto_ptr<Fl_Window> window ;

    std::string function_string ;
    Fl_Output* function_string_output ;
    void redraw_function_string() ;

    void help_construct() ;
    void help_callback() ;

    Fl_Counter* order ;
    void order_callback() ;

    Fl_Counter* coeff_num ;
    void coeff_num_callback() ;

    Fl_Value_Input* coeff ;
    void coeff_callback() ;

    Fl_Value_Input* realcurves_epsilon ;
    void realcurves_epsilon_callback() ;

    Fl_Value_Input* width_res ;
    void width_res_callback() ;

    Fl_Value_Input* height_res ;
    void height_res_callback() ;

    Fl_Value_Input* plane_size ;
    void plane_size_callback() ;

    Fl_Value_Input* plane_fade ;
    void plane_fade_callback() ;

    Fl_Value_Input* color_scale ;
    void color_scale_callback() ;

    Fl_Value_Input* refz_scale ;
    void refz_scale_callback() ;

    Fl_Light_Button* axes_toggle ;
    void axes_toggle_callback() ;

    Private( UI &, Fl_Window* ) ;
    ~Private() ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

UI::Private::
Private( UI & outside_,
         Fl_Window* camera_ )
    : outside(outside_),
      camera(camera_),
      coeffs_vec(),
      help_data(),
      window(0),
      function_string(),
      function_string_output(0),
      order(0),
      coeff_num(0),
      coeff(0),
      realcurves_epsilon(0),
      width_res(0),
      height_res(0),
      plane_size(0),
      plane_fade(0),
      color_scale(0),
      refz_scale(0),
      axes_toggle(0)
{
}

UI::Private::
~Private()
{
}

//////////////////////////////////////////////
// constructor
//////////////////////////////////////////////

UI::
UI( Display & display )
    : m(new Private(*this,
                    &Representation::rep(display)))
{
    m->camera->hide() ;
    m->camera->resize(100, 0, 500, 480-24) ;

    const double max = std::numeric_limits<double>::max() ;

    m->window = std::auto_ptr<Fl_Window>(
        new Fl_Window(600, 480, "polynomialviewer")) ;
    m->window->end() ;
    m->window->add_resizable(*m->camera) ;

    Fl_Group* panel = new Fl_Group(0, 0, 100, 480) ;
    panel->end() ;
    panel->resizable(0) ;
    m->window->add(panel) ;

    m->help_construct() ;

    m->help_data.button = new MF_Widget<Fl_Button, UI::Private>(
        10, 10, 80, 20,
        "help",
        *m,&UI::Private::help_callback) ;
    m->help_data.button->align(FL_ALIGN_CENTER) ;
    m->help_data.button->labelsize(12) ;
    m->help_data.button->box(FL_ENGRAVED_BOX) ;
    panel->add(m->help_data.button) ;

    m->order = new MF_Widget<Fl_Counter, UI::Private>(
        10, 50, 80, 20,
        "order",
        *m,&UI::Private::order_callback) ;
    m->order->align(FL_ALIGN_TOP) ;
    m->order->labelsize(12) ;
    m->order->type(FL_SIMPLE_COUNTER) ;
    m->order->step(1) ;
    m->order->value(0) ;
    m->order->range(0, max) ;
    m->order->when(FL_WHEN_RELEASE) ;
    m->order->box(FL_ENGRAVED_BOX) ;
    panel->add(m->order) ;

    m->coeff_num = new MF_Widget<Fl_Counter, UI::Private>(
        10, 90, 80, 20,
        "coefficient",
        *m,&UI::Private::coeff_num_callback) ;
    m->coeff_num->when(FL_WHEN_RELEASE) ;// to avoid fltk bug
    m->coeff_num->align(FL_ALIGN_TOP) ;
    m->coeff_num->labelsize(12) ;
    m->coeff_num->type(FL_SIMPLE_COUNTER) ;
    m->coeff_num->step(1) ;
    m->coeff_num->value(0) ;
    m->coeff_num->range(0, m->order->value()) ;
    m->coeff_num->box(FL_ENGRAVED_BOX) ;
    panel->add(m->coeff_num) ;

    m->coeff = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 110, 80, 20,
        "",
        *m,&UI::Private::coeff_callback) ;
    m->coeff->step(0.001) ;
    m->coeff->range(-max, max) ;
    panel->add(m->coeff) ;

    m->realcurves_epsilon = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 150, 80, 20,
        "epsilon",
        *m,&UI::Private::realcurves_epsilon_callback) ;
    m->realcurves_epsilon->align(FL_ALIGN_TOP) ;
    m->realcurves_epsilon->labelsize(12) ;
    m->realcurves_epsilon->step(0.0005) ;
    m->realcurves_epsilon->range(0, max) ;
    panel->add(m->realcurves_epsilon) ;

    m->refz_scale = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 190, 80, 20,
        "scale Re{f(z)}",
        *m,&UI::Private::refz_scale_callback) ;
    m->refz_scale->align(FL_ALIGN_TOP) ;
    m->refz_scale->labelsize(12) ;
    m->refz_scale->step(0.001) ;
    m->refz_scale->soft(0) ;
    m->refz_scale->range(0, max) ;
    m->refz_scale->value(1.0) ;
    panel->add(m->refz_scale) ;

    m->color_scale = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 230, 80, 20,
        "scale color",
        *m,&UI::Private::color_scale_callback) ;
    m->color_scale->align(FL_ALIGN_TOP) ;
    m->color_scale->labelsize(12) ;
    m->color_scale->step(0.001) ;
    m->color_scale->soft(0) ;
    m->color_scale->range(0, max) ;
    panel->add(m->color_scale) ;

    Fl_Box* res_label = new Fl_Box(
        10, 270, 80, 20, "resolution") ;
    res_label->align(FL_ALIGN_TOP) ;
    res_label->labelsize(12) ;
    panel->add(res_label) ;

    m->function_string_output = new Fl_Output(100, 480 - 23, 500, 20) ;
    m->function_string_output->textsize(10) ;
    m->window->add(m->function_string_output) ;

    m->width_res = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 270, 80, 20,
        "",
        *m,&UI::Private::width_res_callback) ;
    m->width_res->align(FL_ALIGN_TOP) ;
    m->width_res->labelsize(12) ;
    m->width_res->step(2) ;
    m->width_res->soft(0) ;
    m->width_res->range(1, max) ;
    panel->add(m->width_res) ;

    m->height_res = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 290, 80, 20,
        "",
        *m,&UI::Private::height_res_callback) ;
    m->height_res->align(FL_ALIGN_TOP) ;
    m->height_res->labelsize(12) ;
    m->height_res->step(2) ;
    m->height_res->soft(0) ;
    m->height_res->range(1, max) ;
    panel->add(m->height_res) ;

    m->plane_size = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 330, 80, 20,
        "plane size",
        *m,&UI::Private::plane_size_callback) ;
    m->plane_size->align(FL_ALIGN_TOP) ;
    m->plane_size->labelsize(12) ;
    m->plane_size->step(0.001) ;
    m->plane_size->soft(0) ;
    m->plane_size->range(0, max) ;
    m->plane_size->value(0.75) ;
    panel->add(m->plane_size) ;

    m->plane_fade = new MF_Widget<Fl_Value_Input, UI::Private>(
        10, 370, 80, 20,
        "plane fade",
        *m,&UI::Private::plane_fade_callback) ;
    m->plane_fade->align(FL_ALIGN_TOP) ;
    m->plane_fade->labelsize(12) ;
    m->plane_fade->step(0.001) ;
    m->plane_fade->soft(0) ;
    m->plane_fade->range(0, 1) ;
    m->plane_fade->value(0.20) ;
    panel->add(m->plane_fade) ;

    m->axes_toggle = new MF_Widget<Fl_Light_Button, UI::Private>(
        10, 400, 80, 20,
        "axes  ",
        *m,&UI::Private::axes_toggle_callback) ;
    m->axes_toggle->align(FL_ALIGN_CENTER) ;
    m->axes_toggle->labelsize(12) ;
    m->axes_toggle->box(FL_ENGRAVED_BOX) ;
    m->axes_toggle->value(1) ;
    panel->add(m->axes_toggle) ;

    // invariant: coeffs_vec.size() >= order->value() + 1
    m->coeffs_vec.resize(int(m->order->value()) + 1) ;

    m->window->show() ;
    m->camera->show() ;
}

UI::
~UI()
{
    m->window->remove(m->camera) ;

    // children of m->window are automatically deleted
}

//////////////////////////////////////////////
// help_construct()
//////////////////////////////////////////////

void
UI::Private::
help_construct()
{
    help_data.window = std::auto_ptr<Fl_Window>(
        new Fl_Window(HELP_WIDTH,
                      HELP_HEIGHT,
                      "polynomialviewer help")) ;

    help_data.display =
        new Fl_Text_Display(0,
                            0,
                            HELP_WIDTH,
                            HELP_HEIGHT) ;

    help_data.buffer = std::auto_ptr<Fl_Text_Buffer>(new Fl_Text_Buffer()) ;

    help_data.buffer->text(help_text().c_str()) ;

    help_data.display->buffer(help_data.buffer.get()) ;

    help_data.window->size_range(100, 100, 0, 0) ;
    help_data.window->add_resizable(*help_data.display) ;
    help_data.window->hide() ;
}

//////////////////////////////////////////////
// values
//////////////////////////////////////////////

const double*
UI::
coeffs_begin() const
{
    return &m->coeffs_vec[0] ;
}

const double*
UI::
coeffs_end() const
{
    return &m->coeffs_vec[int(m->order->value())] + 1 ;
}

void
UI::
coeffs( const double* begin, const double* end )
{
    m->coeffs_vec.clear() ;
    for( ; begin != end ; ++begin )
    {
        m->coeffs_vec.push_back(*begin) ;
    }
    m->order->value(double(m->coeffs_vec.size() - 1)) ;
    m->coeff_num->range(0, m->order->value()) ;
    m->coeff_num->value(double(m->order->value())) ;
    m->coeff->value(m->coeffs_vec[int(m->order->value())]) ;
    m->redraw_function_string() ;

    m->coeff_callback() ;
}

double
UI::
realcurves_epsilon() const
{
    return m->realcurves_epsilon->value() ;
}

void
UI::
realcurves_epsilon( double a )
{
    m->realcurves_epsilon->value(a) ;
    m->realcurves_epsilon_callback() ;
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
    m->width_res_callback() ;
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
    m->height_res_callback() ;
}

double
UI::
plane_size() const
{
    return m->plane_size->value() ;
}

void
UI::
plane_size( double a )
{
    m->plane_size->value(a) ;
    m->plane_size_callback() ;
}

double
UI::
plane_fade() const
{
    return m->plane_fade->value() ;
}

void
UI::
plane_fade( double a )
{
    m->plane_fade->value(a) ;
    m->plane_fade_callback() ;
}

double
UI::
color_scale() const
{
    return m->color_scale->value() ;
}

void
UI::
color_scale( double a )
{
    m->color_scale->value(a) ;
    m->color_scale_callback() ;
}

double
UI::
refz_scale() const
{
    return m->refz_scale->value() ;
}

void
UI::
refz_scale( double a )
{
    m->refz_scale->value(a) ;
    m->refz_scale_callback() ;
}

bool
UI::
axes_toggle() const
{
    return bool(m->axes_toggle->value()) ;
}

void
UI::
axes_toggle( bool a )
{
    m->axes_toggle->value(int(a)) ;
    m->axes_toggle_callback() ;
}

//////////////////////////////////////////////
// callbacks
//////////////////////////////////////////////

namespace {

// I don't understand why fltk allows values outside the range
void clamp( Fl_Valuator* v )
{
    v->value(v->clamp(v->value())) ;
}

} // anon namespace

void
UI::Private::
help_callback()
{
    help_data.window->show() ;
}

void
UI::Private::
order_callback()
{
    clamp(order) ;

    if( coeffs_vec.size() <
        std::vector<double>::size_type(order->value() + 1) )
    {
        coeffs_vec.resize(
            std::vector<double>::size_type(order->value() + 1)) ;
    }

    coeff_num->range(0, order->value()) ;
    if( coeff_num->value() > order->value() )
    {
        coeff_num->value(order->value()) ;
        coeff->value(coeffs_vec[int(order->value())]) ;
    }

    redraw_function_string() ;
    outside.emit_widget(UI::COEFFS) ;
}

void
UI::Private::
coeff_num_callback()
{
    clamp(coeff_num) ;
    coeff->value(coeffs_vec[int(coeff_num->value())]) ;
}

void
UI::Private::
coeff_callback()
{
    clamp(coeff) ;
    coeffs_vec[int(coeff_num->value())] = coeff->value() ;
    redraw_function_string() ;
    outside.emit_widget(UI::COEFFS) ;
}

void
UI::Private::
realcurves_epsilon_callback()
{
    clamp(realcurves_epsilon) ;
    outside.emit_widget(UI::REALCURVES_EPSILON) ;
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
plane_size_callback()
{
    clamp(plane_size) ;
    outside.emit_widget(UI::PLANE_SIZE) ;
}

void
UI::Private::
plane_fade_callback()
{
    clamp(plane_fade) ;
    outside.emit_widget(UI::PLANE_FADE) ;
}

void
UI::Private::
color_scale_callback()
{
    clamp(color_scale) ;
    outside.emit_widget(UI::COLOR_SCALE) ;
}

void
UI::Private::
refz_scale_callback()
{
    clamp(refz_scale) ;
    outside.emit_widget(UI::REFZ_SCALE) ;
}

void
UI::Private::
axes_toggle_callback()
{
    outside.emit_widget(UI::AXES_TOGGLE) ;
}

//////////////////////////////////////////////
// util
//////////////////////////////////////////////

void
UI::Private::
redraw_function_string()
{
    // redraw function string

    std::stringstream out ;

    out << "f(z) = " << coeffs_vec[0] ;

    for( int i = 1 ; i != int(order->value()) + 1 ; ++i )
    {
        if( coeffs_vec[i] >= 0 )
        {
            out << " + " << coeffs_vec[i] ;
        }
        else
        {
            out << " - " << -coeffs_vec[i] ;
        }

        if( i == 1 )
        {
            out << "z" ;
        }
        else
        {
            out << "z^" << i ;
        }
    }

    function_string = out.str() ;
    function_string_output->value(function_string.c_str()) ;
    function_string_output->redraw() ;
}

