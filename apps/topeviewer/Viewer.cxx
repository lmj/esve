//
// Note we are ignoring the messages emitted by widget creation in
// UI's constructor.  Until C++ starts supporting named parameters
// (i.e. never), it is much clearer to initialize widgets individually
// in default_parameters().
//

#include "Viewer.hxx"
#include "Tope_File.hxx"
#include <esve/engine/dim3/Transform.hxx>
#include <esve/engine/dim3/Frame.hxx>
#include <esve/engine/dim3/Camera_Details.hxx>
#include <esve/ui/base/Display_Details.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/math/misc.hxx>
#include <string>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <iostream>

//////////////////////////////////////////////////
// using
//////////////////////////////////////////////////

using esve::engine::dim4::Transform ;
using esve::components::dimn::Valuator ;
using esve::engine::dim3::Camera_Details ;
using esve::math::misc::fmodp ;
using esve::types::real ;
using esve::types::pure ;
using esve::types::quat ;

//////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////

const double FAR_CLIP = 20.0 ;
const double NEAR_CLIP = 0.05 ;
const double LENGTH_FUDGE = 0.0001 ;
const double INITIAL_LENGTHS_INTERVAL = 0.2 ;

//////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////

Viewer::
Viewer( int argc, char** argv )
    : super(argc, argv),
      initialize_super(*this),
      tope(super::arguments_begin() == super::arguments_end()
           ?
           "" // Default_Reader accepts empty string
           :
           *super::arguments_begin()),
      camera(super::create_camera("topeviewer")),
      ui(camera),
      tie(ui, tope),
      clipper(camera, tope),
      initial_file(true)
{
    super::create_light() ;
    super::modal_tie(ui) ;

    // handle tree
    super::peek_kernel().add_emitter(ui) ;
    super::add_handler(*this) ;
    super::add_handler(tie) ;

    // draw, compute, frame tree
    super::add_geom(tope) ;

    // compute tree
    super::peek_compute_sender().add(clipper) ;

    // clip
    camera.peek_camera_details().near_clip(NEAR_CLIP) ;
    camera.peek_camera_details().far_clip(FAR_CLIP) ;
    tope.initial_min_z(-10) ;

    // tie some UI values
    tie.tie(ui.valuator(UI::BALL_RADIUS),
            &Tope_Geom::ball_radius,
            &Tope_Geom::ball_radius) ;
    tie.tie(ui.valuator(UI::MIN_LENGTH),
            &Tope_Geom::min_length,
            &Tope_Geom::min_length) ;
    tie.tie(ui.valuator(UI::MAX_LENGTH),
            &Tope_Geom::max_length,
            &Tope_Geom::max_length) ;
    tie.tie(ui.valuator(UI::CUT_EDGES_MIN),
            &Tope_Geom::cut_edges_min,
            &Tope_Geom::cut_edges_min ) ;
    tie.tie(ui.valuator(UI::CUT_EDGES_MAX),
            &Tope_Geom::cut_edges_max,
            &Tope_Geom::cut_edges_max) ;
    tie.tie(ui.valuator(UI::CUT_BALLS_MIN),
            &Tope_Geom::cut_balls_min,
            &Tope_Geom::cut_balls_min) ;
    tie.tie(ui.valuator(UI::CUT_BALLS_MAX),
            &Tope_Geom::cut_balls_max,
            &Tope_Geom::cut_balls_max) ;
    tie.tie(ui.valuator(UI::TUBE_RADIUS),
            &Tope_Geom::tube_radius,
            &Tope_Geom::tube_radius) ;

    default_parameters() ;
}

Viewer::
~Viewer()
{
}

Viewer::
Initialize_Super::
Initialize_Super( Viewer & viewer )
{
    // seems messy for stars to first appear then disappear after loading
    viewer.super::stars_active(false) ;
}

//////////////////////////////////////////////////
// handle()
//////////////////////////////////////////////////

bool
Viewer::
handle_key_push( Key key, const Keyboard & )
{
    switch( key )
    {
    case Keyboard::ENTER:
        write_next_config() ;
        return false ;

    case Keyboard::Key(' '):
        read_next_config() ;
        return true ;
        
    // tube stuff

    case Keyboard::Key('['):
        if( tope.tube_wrap_res() > 3 )
        {
            tope.tube_wrap_res(tope.tube_wrap_res() - 1) ;
        }
        return true ;

    case Keyboard::Key(']'):
        tope.tube_wrap_res(tope.tube_wrap_res() + 1) ;
        return true ;

#if 0
    // not worth it to go greater than 1

    case Keyboard::Key('-'):
        if( tope.tube_length_res() > 1 )
        {
            tope.tube_length_res(tope.tube_length_res() - 1) ;
        }
        return true ;

    case Keyboard::Key('='):
        tope.tube_length_res(tope.tube_length_res() + 1) ;
        return true ;
#endif

    default:
        ;
    }

    return false ;
}

bool
Viewer::
handle_key_release( Key, const Keyboard & )
{
    return false ;
}

bool
Viewer::
handle_valuator( const Valuator<real> & valuator )
{
    bool handled = false ;

    if( &valuator == &ui.valuator(UI::INVERSION) )
    {
        super::inversion(ui.inversion()) ;
        handled = true ;
    }
    else if( &valuator == &ui.valuator(UI::SLIDE_COLOR) )
    {
        ui.slide_color(fmodp(ui.slide_color(), real(1))) ;
        tope.slide_color(ui.slide_color()) ;
        handled = true ;
    }
    else if( &valuator == &ui.valuator(UI::CAMERA_ZPOS) )
    {
        camera.peek_frame().peek_transform().translation(pure(
            camera.peek_frame().peek_transform().translation().x(),
            camera.peek_frame().peek_transform().translation().y(),
            ui.camera_zpos())) ;
        handled = true ;
    }
    else if( &valuator == &ui.valuator(UI::CAMERA_FOV) )
    {
        Camera_Details::Perspective_Projection proj =
            camera.peek_camera_details().perspective_projection_data() ;
        proj.field_of_view = ui.field_of_view() ;
        camera.peek_camera_details().perspective_projection(proj) ;
        handled = true ;
    }

    return handled ;
}

bool
Viewer::
handle_file_selector( const File_Selector & fs )
{
    read_file(fs.value()) ;
    return true ;
}

//////////////////////////////////////////////////
// ui parameters
//////////////////////////////////////////////////

void
Viewer::
default_parameters()
{
    tope.tube_wrap_res(12) ;
    tope.tube_length_res(1) ;

    super::home_transform(Transform()) ;
    super::rotation(quat(1), quat(1)) ;

    super::stars_active(true) ;

    ui.filename(tope.filename()) ;
    
    ui.slide_color(0.0) ;

    // min/max length computed in read_file()

    ui.tube_radius(0.0) ;
    ui.cut_edges_min(0.0) ;
    ui.cut_edges_max(100.0) ;
    ui.ball_radius(0.0) ;
    ui.cut_balls_min(ui.cut_edges_min()) ;
    ui.cut_balls_max(ui.cut_edges_max()) ;

    ui.camera_zpos(5.0) ;
    ui.inversion(1.0) ;
    ui.field_of_view(45) ;
}

//////////////////////////////////////////////////
// file/configs read/write
//////////////////////////////////////////////////

void
Viewer::
read_file( const std::string & filename )
{
    if( initial_file )
    {
        // skip re-read of initial file
        initial_file = false ;
    }
    else
    {
        try
        {
            tope.read(filename) ;
        }
        catch( Tope_File::Read_Error & e )
        {
            std::cerr << e.what() << std::endl ;
            return ;
        }
    }

    const Tope_Geom::Edge_Length_Interval & interval =
        tope.edge_length_interval() ;

    ui.min_length_range(
        double(0),
        double(interval.largest_length + LENGTH_FUDGE)) ;

    ui.max_length_range(
        double(0),
        double(interval.largest_length + LENGTH_FUDGE)) ;

    if( tope.has_configs() )
    {
        std::istringstream config_stream(tope.current_config()) ;
        read_config(config_stream) ;
    }
    else
    {
        // no configs present -- retain the current parameters
        // except for min_length, max_length, and transforms
        
        ui.min_length(interval.smallest_length - LENGTH_FUDGE) ;
        
        ui.max_length(std::min(double(interval.smallest_length
                                      +
                                      INITIAL_LENGTHS_INTERVAL),
                               double(interval.largest_length))
                      +
                      LENGTH_FUDGE) ;
        
        super::home_transform(Transform()) ;
        super::rotation(quat(1), quat(1)) ;
    }
    
    camera.peek_display_details().label(tope.filename()) ;
    super::stop_motion() ;
}

void
Viewer::
write_config( std::ostream & out )
{
    out.precision(20) ;

    out << super::rotation().a() << " "
        << super::rotation().d() << " " ;

    out << int(super::stars_active()) << " " ;

    for( UI::Valuators_const_iterator i = ui.valuators_begin() ;
         i != ui.valuators_end() ;
         ++i )
    {
        out << (**i).value() << " " ;
    }
}

void
Viewer::
read_config( std::istream & in )
{
    quat a ;
    quat d ;

    in >> a >> d ;
    super::rotation(a, d) ;

    int stars_active ;
    in >> stars_active ;
    super::stars_active(bool(stars_active)) ;

    for( UI::Valuators_const_iterator i = ui.valuators_begin() ;
         i != ui.valuators_end() ;
         ++i )
    {
        double param ;
        in >> param ;
        (**i).value(param) ;
    }

    assert(in.fail() == false && "Tope file config format error") ;

    super::stop_motion() ;
    super::home_transform(super::rotation()) ;
}

void
Viewer::
read_next_config()
{
    if( tope.has_configs() )
    {
        tope.next_config() ;
        std::istringstream config(tope.current_config()) ;
        read_config(config) ;
    }
}

void
Viewer::
write_next_config()
{
    try
    {
        std::ostringstream config ;
        write_config(config) ;
        tope.add_config(config.str()) ;
        super::home_transform(super::rotation()) ;
    }
    catch( Tope_File::Write_Error & e )
    {
        std::cerr << e.what() << std::endl ;
    }
}

