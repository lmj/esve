
#include <esve/viewers/dim3/Canned_Viewer_Base.hxx>
#include <esve/components/dimn/Show_FPS.hxx>
#include <esve/ui/extra/Modal_Tie.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/kernel/Driver_Handler.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/components/dimn/Command_Line.hxx>

namespace esve { namespace viewers { namespace dim3 {

using types::real ;

const real DEFAULT_SENSITIVITY = 0.75 ;

struct Canned_Viewer_Base::Private
{
    struct Canned_Handler
        : public ui::base::Keyboard_Handler,
          public kernel::Driver_Handler
    {
        Canned_Viewer_Base::Private & m ;

        Canned_Handler( Canned_Viewer_Base::Private & m_ )
            : m(m_) { }

        bool handle_key_push( Key key, const Keyboard & )
        {
            bool handled = false ;

            switch( key )
            {
            case 'e':
                m.outside.stars_active(!m.outside.stars_active()) ;
                handled = true ;
                break ;

            case Keyboard::ESCAPE:
            case 'q':
                {
                    m.want_to_finish = true ;
                    handled = true ;
                }
                break ;

            case 'f':
                if( m.modal_tie )
                {
                    m.modal_tie->toggle_display_fullscreen() ;
                    handled = true ;
                }
                break ;

            case 'z':
                if( m.modal_tie )
                {
                    m.modal_tie->toggle_modal_visible() ;
                    handled = true ;
                }
                break ;

            default:
                ;
            }

            return handled ;
        }

        bool handle_key_release( Key , const Keyboard & )
        {
            return false ;
        }

        bool handle_driver_start()
        {
            return false ;
        }

        bool handle_driver_check_finished()
        {
            return m.want_to_finish ;
        }

        bool handle_driver_finish()
        {
            return false ;
        }
    } ;

    Canned_Viewer_Base & outside ;
    ui::extra::Modal_Tie* modal_tie ;
    components::dimn::Command_Line command_line ;
    Canned_Handler canned_handler ;
    components::dimn::Show_FPS show_fps ;
    bool want_to_finish ;
    real sensitivity ;

    Private( Canned_Viewer_Base & outside_,
             int argc,
             char** argv ) ;
    ~Private() ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Canned_Viewer_Base::Private::
Private( Canned_Viewer_Base & outside_,
         int argc,
         char** argv )
    : outside(outside_),
      modal_tie(0),
      command_line(argc, argv, "s:f:"),
      canned_handler(*this),
      show_fps(),
      want_to_finish(false),
      sensitivity(DEFAULT_SENSITIVITY)
{
}

Canned_Viewer_Base::Private::
~Private()
{
}

Canned_Viewer_Base::
Canned_Viewer_Base( int argc, char** argv )
    : super(),
      m(new Private(*this, argc, argv))
{
    super::add_handler(m->canned_handler) ;

    if( m->command_line.option('f') )
    {
        super::peek_kernel().add_update_receiver(m->show_fps) ;
        m->show_fps.sampling_interval(
            std::atof(m->command_line.option_argument('f').c_str())) ;
    }
    if( m->command_line.option('s') )
    {
        m->sensitivity =
            std::atof(m->command_line.option_argument('s').c_str()) ;
    }
}

Canned_Viewer_Base::
~Canned_Viewer_Base()
{
}

void
Canned_Viewer_Base::
modal_tie( ui::extra::Modal_Tie & a )
{
    m->modal_tie = &a ;
}

real
Canned_Viewer_Base::
sensitivity() const
{
    return m->sensitivity ;
}

Canned_Viewer_Base::Command_Line_Arguments_iterator
Canned_Viewer_Base::
arguments_begin() const
{
    return m->command_line.arguments_begin() ;
}

Canned_Viewer_Base::Command_Line_Arguments_iterator
Canned_Viewer_Base::
arguments_end() const
{
    return m->command_line.arguments_end() ;
}

}}} // namespace esve::viewers::dim3
