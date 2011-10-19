
#include <esve/viewers/dim4/Simple_Viewer.hxx>
#include <esve/viewers/dim4/impl/Auto_Widgets.hxx>
#include <esve/viewers/dim4/Canned_Viewer.hxx>
#include <esve/viewers/dim3/Default_Initializer.hxx>
#include <esve/components/dimn/impl/Simple_UI.hxx>
#include <esve/components/dimn/Command_Line.hxx>
#include <esve/engine/dim3/Camera.hxx>
#include <esve/ui/extra/disclaimer.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Draw_Sender.hxx>
#include <iostream>
#include <cstdlib>

namespace esve { namespace viewers { namespace dim4 {

const std::string HELP_TEXT =
"\
Dragging the left mouse button in the camera window rotates the\n\
object in 3D. Likewise the right mouse button rotates in 4D.\n\
\n\
Click on a number field then drag left/right to modify it, or use the\n\
keyboard.\n\
\n\
Each mouse button changes the selected value at a different rate; left\n\
button is slowest and right button is fastest.\n\
\n\
Keyboard functions:\n\
q --- quit the application\n\
e --- toggle stars\n\
r --- reset position\n\
f --- toggle full screen\n\
z --- toggle panel\n\
a, s, d, w --- rotate stars\n\
\n\
Closing the camera window will also exit the application.\n\
\n\
Mouse sensitivity may be adjusted with the \"-s\" command-line option.\n\
Default is 0.75 (measured in milliradians per pixel).\n\
\n\
The 'c' key toggles \"Hopf rotations,\" explained in README.4d.\n\
\n\
The stars represent real astronomical data.\n\
" ;

////////////////////////////////////////////////////////////////////
//
// Simple_Viewer::Private
//
////////////////////////////////////////////////////////////////////

struct Simple_Viewer::Private : public Canned_Viewer
{
    typedef Canned_Viewer super ;

    struct Own_Initializer
        : public dim3::Default_Initializer
    {
        Simple_Viewer::Private & m ;

        Own_Initializer( Simple_Viewer::Private & m_ )
            : m(m_) { }
        
        void draw_initialize()
        {
            m.outside.initialize() ;
        }

        void base_draw_initialize()
        {
            Default_Initializer::draw_initialize() ;
        }
    } ;

    Simple_Viewer & outside ;
    components::dimn::impl::Simple_UI ui ;
    impl::Auto_Widgets auto_widgets ;
    Own_Initializer initializer ;
    std::string help_text ;

    Private( int argc,
             char** argv,
             const std::string & label,
             Simple_Viewer & outside_ ) ;

    ~Private() ;
} ;

//
// Simple_Viewer is meant to have a minimal main(), so catch here.
//

Simple_Viewer::Private::
Private( int argc,
         char** argv,
         const std::string & label,
         Simple_Viewer & outside_ )
try
    : super(argc, argv),
      outside(outside_),
      ui(super::create_camera(label)),
      auto_widgets(outside_, *this, *this),
      initializer(*this),
      help_text(HELP_TEXT + ui::extra::disclaimer::disclaimer())
{
    super::create_light() ;
    super::modal_tie(ui) ;
    super::peek_kernel().add_emitter(ui) ;

    super::add_handler(auto_widgets) ;
    super::add_handler(outside) ;

    super::peek_draw_initializer().remove_all() ;
    super::peek_draw_initializer().add(initializer) ;
}
catch( components::dimn::Command_Line::Error & e )
{
    std::cerr << e.what() << std::endl ;
    std::exit(1) ;
}

Simple_Viewer::Private::
~Private()
{
}

////////////////////////////////////////////////////////////////////
//
// Simple_Viewer
//
////////////////////////////////////////////////////////////////////

Simple_Viewer::
Simple_Viewer( int argc,
               char** argv,
               const std::string & label )
    : m(new Private(argc, argv, label, *this))
{
}

Simple_Viewer::
~Simple_Viewer()
{
}

void
Simple_Viewer::
initialize()
{
    m->initializer.base_draw_initialize() ;
}

Simple_Viewer::Valuator &
Simple_Viewer::
create_scaling_valuator( const std::string & label )
{
    return m->auto_widgets.create_scaling_valuator(label) ;
}

Simple_Viewer::Valuator &
Simple_Viewer::
create_inversion_valuator( const std::string & label )
{
    return m->auto_widgets.create_inversion_valuator(label) ;
}

void
Simple_Viewer::
create_label( const std::string & label )
{
    m->ui.create_label(label) ;
}

Simple_Viewer::Valuator &
Simple_Viewer::
create_valuator( real initial_value, const std::string & label )
{
    return m->ui.create_valuator(initial_value, label) ;
}

Simple_Viewer::Complex_Valuator &
Simple_Viewer::
create_valuator( const complex & initial_value,
                 const std::string & label )
{
    return m->ui.create_valuator(initial_value, label) ;
}

Simple_Viewer::Pure_Valuator &
Simple_Viewer::
create_valuator( const pure & initial_value,
                 const std::string & label )
{
    return m->ui.create_valuator(initial_value, label) ;
}

Simple_Viewer::Quat_Valuator &
Simple_Viewer::
create_valuator( const quat & initial_value,
                 const std::string & label )
{
    return m->ui.create_valuator(initial_value, label) ;
}

Simple_Viewer::Toggle &
Simple_Viewer::
create_toggle( bool initial_value, const std::string & label )
{
    return m->ui.create_toggle(initial_value, label) ;
}

Simple_Viewer::File_Selector &
Simple_Viewer::
create_file_selector( const std::string & initial_value,
                      const std::string & label,
                      const std::string & selector_label,
                      const std::string & initial_directory,
                      const std::string & filter )
{
    return m->ui.create_file_selector(initial_value,
                                      label,
                                      selector_label,
                                      initial_directory,
                                      filter) ;
}

void
Simple_Viewer::
create_help( const std::string & text, const std::string & label )
{
    m->ui.create_help(text, label) ;
}

int
Simple_Viewer::
takeover()
{
    return m->takeover() ;
}

const std::string &
Simple_Viewer::
help_text() const
{
    return m->help_text ;
}

void
Simple_Viewer::
add_geom( engine::dim3::Geom & a )
{
    m->add_geom(a) ;
}

void
Simple_Viewer::
remove_geom( engine::dim3::Geom & a )
{
    m->remove_geom(a) ;
}

void
Simple_Viewer::
add_geom( engine::dim4::Geom & a )
{
    m->add_geom(a) ;
}

void
Simple_Viewer::
remove_geom( engine::dim4::Geom & a )
{
    m->remove_geom(a) ;
}

void
Simple_Viewer::
add_handler( kernel::Handler & a )
{
    m->add_handler(a) ;
}

void
Simple_Viewer::
remove_handler( kernel::Handler & a )
{
    m->remove_handler(a) ;
}

void
Simple_Viewer::
add_handler( components::dimn::Motion_Handler & a )
{
    m->add_handler(a) ;
}

void
Simple_Viewer::
remove_handler( components::dimn::Motion_Handler & a )
{
    m->remove_handler(a) ;
}

Simple_Viewer::Catch_Function
Simple_Viewer::
catch_function() const
{
    return m->ui.catch_function() ;
}

void
Simple_Viewer::
catch_function( Catch_Function a )
{
    m->ui.catch_function(a) ;
}

}}} // namespace esve::viewers::dim4
