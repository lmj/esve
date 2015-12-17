
//
// I can use 'new' here frivolously since fltk supposedly doesn't
// throw exceptions.  But in any case I've given up on writing safe
// GUI code.
//

#include <esve/platform/MF_Widget.hxx>
#include <esve/platform/Representation.hxx>
#include <esve/ui/extra/Simple_UI.hxx>
#include <esve/ui/extra/Toggle.hxx>
#include <esve/ui/extra/Valuator.hxx>
#include <esve/ui/extra/File_Selector.hxx>
#include <esve/ui/extra/disclaimer.hxx>
#include <esve/ui/base/Display.hxx>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/filename.H>
#include <string>
#include <limits>
#include <list>
#include <cassert>
#include <string>
#include <memory>

using esve::platform::MF_Widget ;
using esve::platform::Representation ;

namespace esve { namespace ui { namespace extra {

/////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////

#ifdef WIN32
// strange behavior with sizes < 104
const int PANEL_WIDTH = 104 ;
const int PANEL_MARGIN = 12 ;
#else
const int PANEL_WIDTH = 100 ;
const int PANEL_MARGIN = 10 ;
#endif

const int PANEL_MIN_HEIGHT = 380 ;
const int HELP_WIDTH = 550 ;

const std::string PANEL_LABEL = " " ;

/////////////////////////////////////////////////////////////
//
// Simple_UI::Private
//
/////////////////////////////////////////////////////////////

struct Simple_UI::Private
{
    struct Valuator_impl : public Valuator
    {
        Simple_UI::Private & m ;
        Fl_Value_Input* fl_widget ;
        
        Valuator_impl( Simple_UI::Private & m_,
                       Fl_Value_Input* fl_widget_ )
            : m(m_),
              fl_widget(fl_widget_) { }
        
        Valuator_impl( const Valuator_impl & a )
            : Valuator(),
              m(a.m),
              fl_widget(a.fl_widget) { }

        double value() const
        {
            return fl_widget->value() ;
        }

        Valuator & value( double a )
        {
            fl_widget->value(a) ;
            fl_widget->redraw() ;
            valuator_callback(*this) ;
            return *this ;
        }

        Valuator & step( double a )
        {
            fl_widget->step(a) ;
            
            // force decimal display to reflect step
            const double save = fl_widget->value() ;
            fl_widget->value(a) ;
            fl_widget->redraw() ;
            fl_widget->value(save) ;
            fl_widget->redraw() ;
            
            valuator_callback(*this) ;
            return *this ;
        }

        Valuator & range( double min, double max )
        {
            fl_widget->range(min, max) ;
            fl_widget->redraw() ;
            valuator_callback(*this) ;
            return *this ;
        }
        
    private:
        Valuator_impl & operator=( const Valuator_impl & a ) ;
    } ;

    struct Toggle_impl : public Toggle
    {
        Simple_UI::Private & m ;
        std::string label ;
        Fl_Light_Button* fl_widget ;
        
        Toggle_impl( Simple_UI::Private & m_,
                     const std::string & label_,
                     Fl_Light_Button* fl_widget_ )
            : m(m_),
              label(label_),
              fl_widget(fl_widget_) { }

        Toggle_impl( const Toggle_impl & a )
            : Toggle(),
              m(a.m),
              label(a.label),
              fl_widget(a.fl_widget) { }

        bool value() const
        {
            return fl_widget->value() ;
        }

        Toggle & value( bool a )
        {
            fl_widget->value(a) ;
            fl_widget->redraw() ;
            toggle_callback(*this) ;
            return *this ;
        }
        
    private:
        Toggle_impl & operator=( const Toggle_impl & a ) ;
    } ;

    struct File_Selector_impl : public File_Selector
    {
        Simple_UI::Private & m ;
        
        File_Selector_impl( Simple_UI::Private & m_ )
            : m(m_) { }

        File_Selector_impl( const File_Selector_impl & a )
            : File_Selector(),
              m(a.m) { }

        const std::string & value() const
        {
            return m.file_data.filename ;
        }

        File_Selector & value( const std::string & a )
        {
            m.file_data.filename = a ;
            m.file_data.fl_file_chooser->value(
                m.file_data.filename.c_str()) ;
            file_selector_callback(*this) ;
            return *this ;
        }

    private:
        File_Selector_impl & operator=( const File_Selector_impl & a ) ;
    } ;

    struct Help_Data
    {
        Fl_Text_Display* fl_text_display ;
        Fl_Button* fl_button ;
        std::auto_ptr<Fl_Text_Buffer> fl_text_buffer ;
        std::string button_label ;
        std::string text ;
        
        Help_Data()
            : fl_text_display(0),
              fl_button(0),
              fl_text_buffer(0),
              button_label(""),
              text("") { }
        
    private:
        Help_Data( const Help_Data & ) ;
        Help_Data & operator=( const Help_Data & ) ;
    } ;
    
    struct Widget_Placement
    {
        int widget_x ;
        int widget_y ;
        int widget_w ;
        int widget_h ;
        int label_h ;
        int widget_spacing ;
        
        Widget_Placement()
            : widget_x(PANEL_MARGIN),
              widget_y(2),
              widget_w(80),
              widget_h(20),
              label_h(12),
              widget_spacing(5) { }
    } ;

    struct Camera_Data
    {
        ui::base::Display & display ;
        int x, y, w, h ;
        Fl_Window* fl_window ;
        bool is_fullscreen ;
        
        Camera_Data( ui::base::Display & display_ )
            : display(display_),
              x(0),
              y(0),
              w(0),
              h(0),
              fl_window(0),
              is_fullscreen(false) { }
        
    private:
        Camera_Data( const Camera_Data & ) ;
        Camera_Data & operator=( const Camera_Data & ) ;
    } ;

    struct File_Chooser_Data
    {
        std::string filename ;
        std::string button_label ;
        std::string display_label ;
        std::string initial_directory ;
        std::string filter ;
        std::auto_ptr<Fl_File_Chooser> fl_file_chooser ;
        std::auto_ptr<File_Selector_impl> file_selector ;
        Fl_Button* fl_button ;
        
        File_Chooser_Data()
            : filename(""),
              button_label(""),
              display_label(""),
              initial_directory(""),
              filter(""),
              fl_file_chooser(0),
              file_selector(0),
              fl_button(0) { }
        
    private:
        File_Chooser_Data( const File_Chooser_Data & ) ;
        File_Chooser_Data & operator=( const File_Chooser_Data & ) ;
    } ;

    struct Panel : public Fl_Window
    {
        Simple_UI::Private & m ;
        const std::string m_label ;
        
        Panel( int x, int y, const std::string & l,
               Simple_UI::Private & m_ )
            : Fl_Window(x, y, ""),
              m(m_),
              m_label(l)
        {
            Fl_Window::label(m_label.c_str()) ;
        }

        int handle( int fl_args ) ;
    } ;

    typedef
    std::list<Valuator_impl>
    Valuators ;

    typedef
    std::list<Toggle_impl>
    Toggles ;

    Simple_UI & outside ;

    std::list<std::string> labels ;
    Widget_Placement place ;
    Camera_Data camera_data ;
    Valuators valuators ;
    Toggles toggles ;
    Help_Data help_data ;
    File_Chooser_Data file_data ;
    std::auto_ptr<Panel> panel ;
    Catch_Function catch_function ;

    Private( Simple_UI & outside_, ui::base::Display & ) ;
    ~Private() ;

    bool help_showing()
    {
        return panel->w() == PANEL_WIDTH + HELP_WIDTH ;
    }

    void finish_create_widget( Fl_Widget* ) ;

    // callbacks

    void help_toggle_callback() ;

    void file_button_callback()
    {
        file_data.fl_file_chooser->show() ;
    }

    // I don't understand why fltk allows values outside the range
    static void clamp( Fl_Valuator* v )
    {
        v->value(v->clamp(v->value())) ;
    }

    static void valuator_callback( Valuator_impl & valuator )
    {
        clamp(valuator.fl_widget) ;
        valuator.fl_widget->redraw() ;
        valuator.m.outside.emit_valuator(valuator) ;
    }
    
    static void file_selector_callback( File_Selector_impl & fs )
    {
        if( fs.m.file_data.fl_file_chooser->value()
            &&
            !fl_filename_isdir(fs.m.file_data.fl_file_chooser->value()) )
        {
            fs.m.file_data.filename =
                fs.m.file_data.fl_file_chooser->value() ;
            fs.m.outside.emit_file_selector(*fs.m.file_data.file_selector) ;
            fs.m.file_data.fl_file_chooser->hide() ;
        }
    }

    static void toggle_callback( Toggle_impl & toggle )
    {
        toggle.m.outside.emit_toggle(toggle) ;
    }
    
    static void valuator_callback_fl( Fl_Widget* , void* data ) ;
    static void file_selector_callback_fl( Fl_File_Chooser* , void* data ) ;
    static void toggle_callback_fl( Fl_Widget* , void* data ) ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Simple_UI::Private::
Private( Simple_UI & outside_, ui::base::Display & display_ )
    : outside(outside_),
      labels(),
      place(),
      camera_data(display_),
      valuators(),
      toggles(),
      help_data(),
      file_data(),
      panel(),
      catch_function(0)
{
}

Simple_UI::Private::
~Private()
{
}

//
// system entry points: handle() and callbacks
//

int
Simple_UI::Private::Panel::
handle( int fl_args )
try
{
    int ret = Fl_Window::handle(fl_args) ;
            
    switch( fl_args )
    {
    case FL_KEYDOWN:
    case FL_KEYUP:
        {
            m.camera_data.fl_window->handle(fl_args) ;
            ret = 1 ;
        }
        break ;
    case FL_UNFOCUS:
        {
            m.camera_data.display.emit_key_release_all() ;
            ret = 1 ;
        }
        break ;
    }
    
    return ret ;
}
catch( std::exception & e )
{
    if( m.catch_function )
    {
        (*m.catch_function)(m.outside, e) ;
    }
    else
    {
        throw ;
    }

    return 0 ;
}

void
Simple_UI::Private::
valuator_callback_fl( Fl_Widget* , void* data )
{
    Valuator_impl* valuator = static_cast<Valuator_impl*>(data) ;

    try
    {
        valuator_callback(*valuator) ;
    }
    catch( std::exception & e )
    {
        if( valuator->m.catch_function )
        {
            (*valuator->m.catch_function)(valuator->m.outside, e) ;
        }
        else
        {
            throw ;
        }
    }
}

void
Simple_UI::Private::
file_selector_callback_fl( Fl_File_Chooser* , void* data )
{
    File_Selector_impl* file_selector =
        static_cast<File_Selector_impl*>(data) ;

    try
    {
        file_selector_callback(*file_selector) ;
    }
    catch( std::exception & e )
    {
        if( file_selector->m.catch_function )
        {
            (*file_selector->m.catch_function)(file_selector->m.outside, e) ;
        }
        else
        {
            throw ;
        }
    }
}

void
Simple_UI::Private::
toggle_callback_fl( Fl_Widget* , void* data )
{
    Toggle_impl* toggle = static_cast<Toggle_impl*>(data) ;

    try
    {
        toggle_callback(*toggle) ;
    }
    catch( std::exception & e )
    {
        if( toggle->m.catch_function )
        {
            (*toggle->m.catch_function)(toggle->m.outside, e) ;
        }
        else
        {
            throw ;
        }
    }
}
    
//////////////////////////////////////////////////
//
// Simple_UI
//
//////////////////////////////////////////////////

Simple_UI::
Simple_UI( ui::base::Display & display )
    : m(new Private(*this, display))
{
    m->panel = std::auto_ptr<Private::Panel>(
        new Private::Panel(PANEL_WIDTH,
                           PANEL_MIN_HEIGHT,
                           PANEL_LABEL,
                           *m)) ;
    m->panel->end() ;
    m->panel->size_range(m->panel->w(), m->panel->h(),
                         m->panel->w(), m->panel->h()) ;
    m->panel->hide() ;

    m->camera_data.fl_window =
        &Representation::rep(display) ;
    m->camera_data.fl_window->show() ;
    m->panel->hide() ;
    m->panel->set_non_modal() ;
    m->panel->show() ;

    // We may have changed the OpenGL context by fiddling with the
    // representation.  Reinitialize for good measure.
    display.reinitialize() ;
}

Simple_UI::
~Simple_UI()
{
    // children of m->panel are automatically deleted
}

Simple_UI::Catch_Function
Simple_UI::
catch_function() const
{
    return m->catch_function ;
}

void
Simple_UI::
catch_function( Catch_Function a )
{
    m->catch_function = a ;
}

////////////////////////////////////////////////////////////
// help window
////////////////////////////////////////////////////////////

void
Simple_UI::
create_help( const std::string & text,
             const std::string & label )
{
    assert(m->help_data.fl_text_display == 0
           &&
           "Only one help dialog allowed") ;

    if( m->help_data.fl_text_display != 0 )
    {
        return ;
    }
    
    m->place.widget_y += m->place.widget_spacing ;

    m->help_data.button_label = label ;
    m->help_data.fl_text_display =
        new Fl_Text_Display(PANEL_WIDTH,
                            0,
                            HELP_WIDTH,
                            m->panel->h()) ;
    m->help_data.fl_text_buffer =
        std::auto_ptr<Fl_Text_Buffer>(new Fl_Text_Buffer()) ;
    m->help_data.text = text ;
    m->help_data.fl_text_buffer->text(m->help_data.text.c_str()) ;
    m->help_data.fl_text_display->buffer(m->help_data.fl_text_buffer.get()) ;
    m->panel->add(*m->help_data.fl_text_display) ;
    m->help_data.fl_text_display->hide() ;

    m->help_data.fl_button =
        new MF_Widget<Fl_Button, Simple_UI::Private>(
            m->place.widget_x,
            m->place.widget_y,
            m->place.widget_w,
            m->place.widget_h,
            m->help_data.button_label,
            *m,&Simple_UI::Private::help_toggle_callback) ;
    m->help_data.fl_button->align(FL_ALIGN_CENTER) ;
    m->help_data.fl_button->labelsize(12) ;
    m->help_data.fl_button->box(FL_ENGRAVED_BOX) ;

    m->finish_create_widget(m->help_data.fl_button) ;
}

void
Simple_UI::Private::
help_toggle_callback()
{
    if( help_showing() )
    {
        help_data.fl_text_display->hide() ;
        panel->resize(panel->x(), panel->y(),
                      PANEL_WIDTH, panel->h()) ;
        panel->size_range(panel->w(), panel->h(),
                          panel->w(), panel->h()) ;
        panel->label(PANEL_LABEL.c_str()) ;
        panel->redraw() ;
    }
    else
    {
        panel->resize(panel->x(), panel->y(),
                      PANEL_WIDTH + HELP_WIDTH, panel->h()) ;

        // I have been unable to make the window resizable with the
        // displayed text.  Apparently non_modal is the reason.
        // So, might as well make it official:
        panel->size_range(panel->w(), panel->h(),
                          panel->w(), panel->h()) ;

        help_data.fl_text_display->show() ;
        panel->redraw() ;
    }
}

void
Simple_UI::Private::
finish_create_widget( Fl_Widget* widget )
{
    panel->add(widget) ;

    place.widget_y += place.widget_h ;

    if( place.widget_y > panel->h() - 10 )
    {
        int panel_height = place.widget_y + 10 ;

        if( help_showing() )
        {
            panel->resize(panel->x(),
                          panel->y(),
                          PANEL_WIDTH + HELP_WIDTH,
                          panel_height) ;
        }
        else
        {
            panel->resize(panel->x(),
                          panel->y(),
                          PANEL_WIDTH,
                          panel_height) ;
        }

        if( help_data.fl_text_display )
        {
            help_data.fl_text_display->resize(help_data.fl_text_display->x(),
                                              help_data.fl_text_display->y(),
                                              help_data.fl_text_display->w(),
                                              panel_height) ;
        }

        panel->size_range(panel->w(), panel->h(),
                          panel->w(), panel->h()) ;

        // I have no idea why this is necessary, but the panel height
        // is bugged without it.
        panel->hide() ;
        panel->show() ;
    }

    panel->redraw() ;
    camera_data.fl_window->redraw() ;
}

////////////////////////////////////////////////////////////
// file chooser
////////////////////////////////////////////////////////////

File_Selector &
Simple_UI::
create_file_selector( const std::string & initial_value,
                      const std::string & label,
                      const std::string & selector_label,
                      const std::string & initial_directory,
                      const std::string & filter )
{
    assert(m->file_data.file_selector.get() == 0
           &&
           "Only one file selector allowed") ;

    if( m->file_data.file_selector.get() != 0 )
    {
        return *m->file_data.file_selector ;
    }

    m->place.widget_y += m->place.widget_spacing ;

    m->file_data.filename = initial_value ;
    m->file_data.button_label = label ;
    m->file_data.display_label = selector_label ;
    m->file_data.initial_directory = initial_directory ;
    m->file_data.filter = filter ;

    m->file_data.fl_file_chooser = std::auto_ptr<Fl_File_Chooser>(
        new Fl_File_Chooser(
            m->file_data.initial_directory.c_str(),
            m->file_data.filter.c_str(),
            Fl_File_Chooser::SINGLE,
            m->file_data.display_label.c_str())) ;
    m->file_data.fl_file_chooser->preview(0) ;
    m->file_data.fl_file_chooser->hide() ;

    m->file_data.fl_button =
        new MF_Widget<Fl_Button, Simple_UI::Private>(
            m->place.widget_x,
            m->place.widget_y,
            m->place.widget_w,
            m->place.widget_h,
            m->file_data.button_label,
            *m,&Simple_UI::Private::file_button_callback) ;
    m->file_data.fl_button->align(FL_ALIGN_CENTER) ;
    m->file_data.fl_button->labelsize(12) ;
    m->file_data.fl_button->box(FL_ENGRAVED_BOX) ;

    m->finish_create_widget(m->file_data.fl_button) ;

    m->file_data.file_selector = std::auto_ptr<Private::File_Selector_impl>(
        new Private::File_Selector_impl(*m)) ;

    m->file_data.fl_file_chooser->callback(
        &Private::file_selector_callback_fl,
        static_cast<void*>(m->file_data.file_selector.get())) ;

    Private::file_selector_callback(*m->file_data.file_selector) ;

    return *m->file_data.file_selector ;
}

////////////////////////////////////////////////////////////
// labels
////////////////////////////////////////////////////////////

void
Simple_UI::
create_label( const std::string & label )
{
    m->labels.push_back(label) ;

    m->place.widget_y += m->place.widget_spacing ;
    m->place.widget_y += m->place.label_h ;

    Fl_Box* box= new Fl_Box(
        m->place.widget_x,
        m->place.widget_y,
        m->place.widget_w,
        m->place.widget_h,
        m->labels.back().c_str()) ;
    box->align(FL_ALIGN_TOP) ;
    box->labelsize(12) ;
    m->panel->add(box) ;
    m->panel->redraw() ;
}

////////////////////////////////////////////////////////////
// valuators
////////////////////////////////////////////////////////////

Valuator &
Simple_UI::
create_valuator( double init, const std::string & label )
{
    if( label != "" )
    {
        create_label(label) ;
    }

    Fl_Value_Input* fl_widget =
        new Fl_Value_Input(m->place.widget_x,
                           m->place.widget_y,
                           m->place.widget_w,
                           m->place.widget_h) ;

    m->valuators.push_back(Private::Valuator_impl(
        *m,
        fl_widget)) ;

    fl_widget->callback(&Private::valuator_callback_fl,
                        &m->valuators.back()) ;
    fl_widget->align(FL_ALIGN_TOP) ;
    fl_widget->labelsize(12) ;
    fl_widget->step(0.1) ;
    fl_widget->range(-std::numeric_limits<double>::max(),
                     std::numeric_limits<double>::max()) ;

    // fltk glitch. force it to show decimals.
    fl_widget->value(1) ;
    fl_widget->value(0) ;
    fl_widget->value(init) ;

    m->finish_create_widget(fl_widget) ;

    Private::valuator_callback(m->valuators.back()) ;

    return m->valuators.back() ;
}

////////////////////////////////////////////////////////////
// toggles
////////////////////////////////////////////////////////////

Toggle &
Simple_UI::
create_toggle( bool init, const std::string & label )
{
    m->place.widget_y += m->place.widget_spacing ;

    m->toggles.push_back(Private::Toggle_impl(
        *m,
        label,
        0 // must initialize with string label data
        )) ;

    Fl_Light_Button* fl_widget =
        new Fl_Light_Button(m->place.widget_x,
                            m->place.widget_y,
                            m->place.widget_w,
                            m->place.widget_h,
                            m->toggles.back().label.c_str()) ;

    m->toggles.back().fl_widget = fl_widget ;

    fl_widget->callback(&Private::toggle_callback_fl,
                        &m->toggles.back()) ;
    fl_widget->align(FL_ALIGN_CENTER) ;
    fl_widget->box(FL_ENGRAVED_BOX) ;
    fl_widget->labelsize(12) ;
    fl_widget->value(init) ;

    m->finish_create_widget(fl_widget) ;

    Private::toggle_callback(m->toggles.back()) ;

    return m->toggles.back() ;
}

/////////////////////////////////////////////////
// panel toggle
/////////////////////////////////////////////////

void
Simple_UI::
toggle_modal_visible()
{
    if( m->panel->shown() )
    {
        m->panel->hide() ;
    }
    else
    {
        m->panel->show() ;
        m->camera_data.fl_window->show() ;
    }
}

void
Simple_UI::
toggle_display_fullscreen()
{
    if( m->camera_data.is_fullscreen )
    {
        m->camera_data.fl_window->fullscreen_off(m->camera_data.x,
                                                 m->camera_data.y,
                                                 m->camera_data.w,
                                                 m->camera_data.h) ;
        m->camera_data.fl_window->size_range(100, 100, 0, 0) ;
    }
    else
    {
        m->camera_data.x = m->camera_data.fl_window->x() ;
        m->camera_data.y = m->camera_data.fl_window->y() ;
        m->camera_data.w = m->camera_data.fl_window->w() ;
        m->camera_data.h = m->camera_data.fl_window->h() ;

        // win32 quirks.  by hiding and resizing we can make the
        // border disappear everywhere but the bottom, however there
        // is now a gap at the bottom of the screen.

        m->camera_data.fl_window->fullscreen() ;
    }

    m->camera_data.fl_window->show() ;
    m->camera_data.is_fullscreen = !m->camera_data.is_fullscreen ;

    // OpenGL context is probably destroyed.  Re-initialize.
    m->camera_data.display.reinitialize() ;
}

//////////////////////////////////////////////////////////////
//
// disclaimer()
//
//////////////////////////////////////////////////////////////

const std::string DISCLAIMER =
"\n\
The user interface elements (windows, input fields) were created with\n\
the fltk library (http://www.fltk.org).\n\
"
;

namespace disclaimer {

const std::string & disclaimer()
{
    return DISCLAIMER ;
}

} // namespace disclaimer

}}} // namespace esve::ui::extra

