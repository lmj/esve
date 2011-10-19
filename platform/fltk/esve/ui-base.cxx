
#include <esve/platform/Representation.hxx>
#include <esve/ui/base/Display.hxx>
#include <esve/ui/base/Display_Details.hxx>
#include <esve/ui/base/Mouse.hxx>
#include <esve/ui/base/Keyboard.hxx>
#include <esve/ui/base/End_Condition.hxx>
#include <esve/message/impl/Compute_Sender.hxx>
#include <esve/message/impl/Draw_Sender.hxx>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <cassert>
#include <string>
#include <map>
#include <list>

/////////////////////////////////////////////////////////////
//
// Toolkit_Windows
//
// Since there is no way to mark a window to be shown later, we need a
// workaround to avoid a virtual call during show() inside the
// constructor.
//
// Record all windows and show() them upon takeover().
//
/////////////////////////////////////////////////////////////

namespace {

typedef std::list<Fl_Gl_Window*> Toolkit_Windows ;
Toolkit_Windows g_toolkit_windows ;

void show_toolkit_windows()
{
    for( Toolkit_Windows::iterator i = g_toolkit_windows.begin() ;
         i != g_toolkit_windows.end() ;
         ++i )
    {
        (*i)->show() ;
    }
}

} // anon namespace

namespace esve { namespace kernel {

void private__add_startup_hook( void (*hook)() ) ;
void private__remove_startup_hook( void (*hook)() ) ;

}} // namespace esve::kernel

namespace esve { namespace ui { namespace base {

/////////////////////////////////////////////////////////////
//
// Display::Private
//
/////////////////////////////////////////////////////////////

struct Display::Private
{
    struct Keymap
        : private std::map<int, Keyboard::Key>
    {
        typedef std::map<int, Keyboard::Key> m_Base ;
    
        using m_Base::const_iterator ;
        using m_Base::find ;
        using m_Base::end ;

        Keymap() ;
    } ;

    struct Toolkit_Window : public Fl_Gl_Window
    {
        Display::Private & m ;

        Toolkit_Window( int w,
                        int h,
                        const std::string & l,
                        Display::Private & m_ ) ;

        int handle( int ) ;

        void draw() ;

        ~Toolkit_Window() ;
    } ;

    struct Own_Display_Details
        : public Display_Details
    {
        typedef Display_Details super ;
        
        Display::Private & m ;
        mutable Display::Rectangle m_rectangle ;

        Own_Display_Details( Display::Private & m_,
                             const Display::Rectangle & rectangle )
            : m(m_),
              m_rectangle(rectangle) { }

        const std::string & label() const
        {
            return m.label ;
        }
        
        void label( const std::string & label )
        {
            m.label = label ;
            m.toolkit_window.label(m.label.c_str()) ;
        }

        void make_current()
        {
            // crashes if not visible
            if( m.toolkit_window.visible() )
            {
                m.toolkit_window.make_current() ;
            }
        }

        const Display::Rectangle & rectangle() const
        {
            m_rectangle.width = m.toolkit_window.w() ;
            m_rectangle.height = m.toolkit_window.h() ;
            return m_rectangle ;
        }

        void reshape( const Display::Rectangle & rectangle )
        {
            glViewport(0,
                       0,
                       GLsizei(rectangle.width),
                       GLsizei(rectangle.height)) ;
        }

        // hack protected status
        using super::call_reshape ;
    } ;

    struct Own_Compute_Sender : public message::impl::Compute_Sender
    {
        using message::impl::Compute_Sender::call_send_compute ;
    } ;

    struct Own_Draw_Sender : public message::impl::Draw_Sender
    {
        using message::impl::Draw_Sender::call_send_draw ;
        using message::impl::Draw_Sender::call_send_draw_initialize ;
    } ;

    Display & outside ;

    // fltk insanely stores the label's pointer.
    std::string label ;

    Toolkit_Window toolkit_window ;

    Own_Display_Details display_details ;
    Own_Compute_Sender compute_sender ;
    Own_Draw_Sender draw_sender ;
    Catch_Function catch_function ;
    bool need_initialize ;
    bool first_draw ;
    static const Keymap KEYMAP ;

    Private( const std::string & ,
             const Display::Rectangle & ,
             Display & ) ;

    ~Private() ;

    static const Fl_Gl_Window & rep( const Display & display )
    {
        return display.m->toolkit_window ;
    }

    static Fl_Gl_Window & rep( Display & display )
    {
        return display.m->toolkit_window ;
    }

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Display::Private::
Private( const std::string & label_,
         const Display::Rectangle & rectangle,
         Display & outside_ )
    : outside(outside_),
      label(label_),
      toolkit_window(rectangle.width,
                     rectangle.height,
                     label,
                     *this),
      display_details(*this, rectangle),
      compute_sender(),
      draw_sender(),
      catch_function(0),
      need_initialize(true),
      first_draw(true)
{
}

Display::Private::
~Private()
{
}

Display::Private::
Keymap::
Keymap()
    : m_Base()
{
    (*this)[FL_Enter]      = Keyboard::ENTER ;
    (*this)[FL_Escape]     = Keyboard::ESCAPE ;
    (*this)[FL_Meta_L]     = Keyboard::META_LEFT ;
    (*this)[FL_Meta_R]     = Keyboard::META_RIGHT ;
    (*this)[FL_Alt_L]      = Keyboard::ALT_LEFT ;
    (*this)[FL_Alt_R]      = Keyboard::ALT_RIGHT ;
    (*this)[FL_Control_L]  = Keyboard::CTRL_LEFT ;
    (*this)[FL_Control_R]  = Keyboard::CTRL_RIGHT ;
    (*this)[FL_Shift_L]    = Keyboard::SHIFT_LEFT ;
    (*this)[FL_Shift_R]    = Keyboard::SHIFT_RIGHT ;
    (*this)[FL_BackSpace]  = Keyboard::BACKSPACE ;
    (*this)[FL_Tab]        = Keyboard::TAB ;
    (*this)[FL_Left]       = Keyboard::LEFT_ARROW ;
    (*this)[FL_Right]      = Keyboard::RIGHT_ARROW ;
    (*this)[FL_Up]         = Keyboard::UP_ARROW ;
    (*this)[FL_Down]       = Keyboard::DOWN_ARROW ;
}

const Display::Private::Keymap
Display::Private::
KEYMAP ;

Display::Private::
Toolkit_Window::
Toolkit_Window( int width,
                int height,
                const std::string & label,
                Display::Private & m_ )
    : Fl_Gl_Window(width, height, label.c_str()),
      m(m_)
{
    Fl_Gl_Window::size_range(100, 100, 0, 0) ;
    mode(FL_RGB|FL_DOUBLE|FL_DEPTH) ;
    end() ;

    if( g_toolkit_windows.size() == 0 )
    {
        kernel::private__add_startup_hook(&show_toolkit_windows) ;
    }

    g_toolkit_windows.push_back(this) ;
}

Display::Private::
Toolkit_Window::
~Toolkit_Window()
{
    g_toolkit_windows.remove(this) ;

    if( g_toolkit_windows.size() == 0 )
    {
        kernel::private__remove_startup_hook(&show_toolkit_windows) ;
    }
}

void
Display::Private::
Toolkit_Window::
draw()
try
{
    if( !Fl_Gl_Window::valid() )
    {
        Own_Display_Details::
            call_reshape(m.outside.peek_display_details(),
                         Display::Rectangle(this->w(), this->h())) ;
        Fl_Gl_Window::valid(1) ;

        m.need_initialize = true ;
    }

    if( m.first_draw )
    {
        // some generic clear
        glClearColor(0, 0, 0, 0) ;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

        m.first_draw = false ;
    }

    if( m.need_initialize )
    {
        Own_Draw_Sender::call_send_draw_initialize(
            m.outside.peek_draw_sender()) ;

        m.need_initialize = false ;
    }

    Own_Compute_Sender::call_send_compute(m.outside.peek_compute_sender()) ;

    Own_Draw_Sender::call_send_draw(m.outside.peek_draw_sender()) ;
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
}

int
Display::Private::
Toolkit_Window::
handle( int fl_args )
try
{
    typedef Mouse::Button Button ;
    typedef Mouse::Position Position ;

    const int fl_ret = Fl_Gl_Window::handle(fl_args) ;
    int ret = 0 ;

    switch( fl_args )
    {
    case FL_FOCUS:
        {
            Fl::focus(this) ;
            ret = 1 ;
        }
        break ;

    case FL_UNFOCUS:
        {
            m.outside.emit_key_release_all() ;
            ret = 1 ;
        }
        break ;

    case FL_DRAG:
    case FL_MOVE:
        {
            m.outside.emit_mouse_move(Position(Fl::event_x_root(),
                                               Fl::event_y_root())) ;

            ret = 1 ;
        }
        break ;

    case FL_PUSH:
        {
            Fl::pushed(this) ;
        }
        // fall through

    case FL_RELEASE:
        {
            Button button = Mouse::Button() ;

            switch( Fl::event_button() )
            {
            case FL_LEFT_MOUSE:
                button = Mouse::LEFT ;
                break ;
            case FL_MIDDLE_MOUSE:
                button = Mouse::MIDDLE ;
                break ;
            case FL_RIGHT_MOUSE:
                button = Mouse::RIGHT ;
                break ;
            default:
                assert(!"Unknown mouse button") ;
                break ;
            }

            if( fl_args == FL_PUSH )
            {
                m.outside.emit_mouse_push(button,
                                          Position(Fl::event_x_root(),
                                                   Fl::event_y_root())) ;
            }
            else
            {
                m.outside.emit_mouse_release(button,
                                             Position(Fl::event_x_root(),
                                                      Fl::event_y_root())) ;
            }

            ret = 1 ;
        }
        break ;

    case FL_KEYDOWN:
    case FL_KEYUP:
        {
            enum { PUSH, RELEASE } action ;
            bool found_key = false ;
            Keyboard::Key key = Keyboard::Key() ;

            if( fl_args == FL_KEYDOWN )
            {
                action = PUSH ;
            }
            else
            {
                action = RELEASE ;
            }

            if( Fl::event_key() >= 0 &&
                Fl::event_key() < Keyboard::NUM_ASCII_KEYS )
            {
                key = Keyboard::Key(Fl::event_key()) ;
                found_key = true ;
            }
            else
            {
                Keymap::const_iterator found = KEYMAP.find(Fl::event_key()) ;

                if( found != KEYMAP.end() )
                {
                    key = (*found).second ;
                    found_key = true ;
                }
            }

            if( found_key )
            {
                switch( action )
                {
                case PUSH:
                    m.outside.emit_key_push(key) ;
                    break ;

                case RELEASE:
                    m.outside.emit_key_release(key) ;
                    break ;
                }
            }
            ret = 1 ;
        }
        break ;

    default:
        {
        }
        break ;
    }

    return fl_ret || ret ;
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

/////////////////////////////////////////////////////////////
//
// Display
//
/////////////////////////////////////////////////////////////

Display::
Display( const std::string & label,
         const Rectangle & rectangle )
    : m(new Private(label,
                    rectangle,
                    *this))
{
}

Display::
~Display()
{
}

message::Compute_Sender &
Display::
peek_compute_sender()
{
    return m->compute_sender ;
}

message::Draw_Sender &
Display::
peek_draw_sender()
{
    return m->draw_sender ;
}

const Display_Details &
Display::
peek_display_details() const
{
    return m->display_details ;
}

Display_Details &
Display::
peek_display_details()
{
    return m->display_details ;
}

void
Display::
update( double )
{
    m->toolkit_window.redraw() ;
}

void
Display::
update()
{
    m->toolkit_window.redraw() ;
}

void
Display::
reinitialize()
{
    m->need_initialize = true ;
    m->toolkit_window.redraw() ;
}

Display::Catch_Function
Display::
catch_function() const
{
    return m->catch_function ;
}

void
Display::
catch_function( Catch_Function a )
{
    m->catch_function = a ;
}

/////////////////////////////////////////////////////////////
//
// End_Condition
//
/////////////////////////////////////////////////////////////

End_Condition::
End_Condition()
    : kernel::Driver_Handler()
{
}

End_Condition::
~End_Condition()
{
}

bool
End_Condition::
handle_driver_start()
{
    return false ;
}

bool
End_Condition::
handle_driver_check_finished()
{
    // end when no displays are showing
    
    for( Fl_Window* p = Fl::first_window() ;
         p != 0 ;
         p = Fl::next_window(p) )
    {
        if( dynamic_cast<Fl_Gl_Window*>(p) )
        {
            // a display is showing; do not end the app
            return false ;
        }
    }

    // no displays showing
    return true ;
}

bool
End_Condition::
handle_driver_finish()
{
    return false ;
}

}}} // namespace esve::ui::base

/////////////////////////////////////////////////////////////
//
// Representation
//
/////////////////////////////////////////////////////////////

namespace esve { namespace platform {

const Fl_Gl_Window &
Representation::
rep( const ui::base::Display & display )
{
    return ui::base::Display::Private::rep(display) ;
}

Fl_Gl_Window &
Representation::
rep( ui::base::Display & display )
{
    return ui::base::Display::Private::rep(display) ;
}

}} // namespace esve::platform
