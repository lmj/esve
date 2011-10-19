
#include <esve/components/dimn/impl/Simple_UI.hxx>
#include <esve/components/dimn/Valuator.hxx>
#include <esve/ui/extra/Simple_UI.hxx>
#include <esve/ui/extra/Valuator.hxx>
#include <esve/ui/extra/Valuator_Handler.hxx>
#include <esve/ui/extra/Toggle_Handler.hxx>
#include <esve/ui/extra/File_Selector_Handler.hxx>
#include <esve/kernel/Caching_Node.hxx>
#include <esve/util/auto_ptr_vector.hxx>
#include <cassert>

namespace esve { namespace components { namespace dimn { namespace impl {

using types::real ;
using types::complex ;
using types::pure ;
using types::quat ;

typedef Valuator<real> Real_Valuator ;
typedef Valuator<complex> Complex_Valuator ;
typedef Valuator<pure> Pure_Valuator ;
typedef Valuator<quat> Quat_Valuator ;

namespace {

struct Real_Valuator_impl : public Real_Valuator
{
    ui::extra::Valuator & re ;

    Real_Valuator_impl( ui::extra::Valuator & re_ )
        : re(re_) { }

    real value() const
    {
        return re.value() ;
    }

    Real_Valuator & value( real a )
    {
        re.value(a) ;
        return *this ;
    }

    Real_Valuator & step( real a )
    {
        re.step(a) ;
        return *this ;
    }

    Real_Valuator &
    range( real min, real max )
    {
        re.range(min, max) ;
        return *this ;
    }
} ;

struct Complex_Valuator_impl : public Complex_Valuator
{
    ui::extra::Valuator & re ;
    ui::extra::Valuator & im ;

    Complex_Valuator_impl( ui::extra::Valuator & re_,
                           ui::extra::Valuator & im_ )
        : re(re_),
          im(im_) { }

    complex value() const
    {
        return complex(re.value(),
                       im.value()) ;
    }

    Complex_Valuator & value( const complex & a )
    {
        re.value(a.real()) ;
        im.value(a.imag()) ;
        return *this ;
    }

    Complex_Valuator & value( real a, real b )
    {
        re.value(a) ;
        im.value(b) ;
        return *this ;
    }

    Complex_Valuator & step( const complex & a )
    {
        re.step(a.real()) ;
        im.step(a.imag()) ;
        return *this ;
    }

    Complex_Valuator & step( real a, real b )
    {
        re.step(a) ;
        im.step(b) ;
        return *this ;
    }

    Complex_Valuator &
    range( const complex & lower_left_corner,
           const complex & upper_right_corner )
    {
        re.range(lower_left_corner.real(),
                 upper_right_corner.real()) ;

        im.range(lower_left_corner.imag(),
                 upper_right_corner.imag()) ;

        return *this ;
    }
} ;

struct Pure_Valuator_impl : public Pure_Valuator
{
    ui::extra::Valuator & x ;
    ui::extra::Valuator & y ;
    ui::extra::Valuator & z ;

    Pure_Valuator_impl( ui::extra::Valuator & x_,
                        ui::extra::Valuator & y_,
                        ui::extra::Valuator & z_ )
        : x(x_),
          y(y_),
          z(z_) { }

    pure value() const
    {
        return pure(x.value(),
                    y.value(),
                    z.value()) ;
    }

    Pure_Valuator & value( const pure & a )
    {
        x.value(a.x()) ;
        y.value(a.y()) ;
        z.value(a.z()) ;
        return *this ;
    }

    Pure_Valuator & step( const pure & a )
    {
        x.step(a.x()) ;
        y.step(a.y()) ;
        z.step(a.z()) ;
        return *this ;
    }

    Pure_Valuator &
    range( const pure & min_corner,
           const pure & max_corner )
    {
        x.range(min_corner.x(),
                max_corner.x()) ;

        y.range(min_corner.y(),
                max_corner.y()) ;
        
        z.range(min_corner.z(),
                max_corner.z()) ;

        return *this ;
    }
} ;

struct Quat_Valuator_impl : public Quat_Valuator
{
    ui::extra::Valuator & w ;
    ui::extra::Valuator & x ;
    ui::extra::Valuator & y ;
    ui::extra::Valuator & z ;

    Quat_Valuator_impl( ui::extra::Valuator & w_,
                        ui::extra::Valuator & x_,
                        ui::extra::Valuator & y_,
                        ui::extra::Valuator & z_ )
        : w(w_),
          x(x_),
          y(y_),
          z(z_) { }

    quat value() const
    {
        return quat(w.value(),
                    x.value(),
                    y.value(),
                    z.value()) ;
    }

    Quat_Valuator & value( const quat & a )
    {
        w.value(a.w()) ;
        x.value(a.x()) ;
        y.value(a.y()) ;
        z.value(a.z()) ;
        return *this ;
    }

    Quat_Valuator & step( const quat & a )
    {
        w.step(a.w()) ;
        x.step(a.x()) ;
        y.step(a.y()) ;
        z.step(a.z()) ;
        return *this ;
    }

    Quat_Valuator &
    range( const quat & min_corner,
           const quat & max_corner )
    {
        w.range(min_corner.w(),
                max_corner.w()) ;
        
        x.range(min_corner.x(),
                max_corner.x()) ;
        
        y.range(min_corner.y(),
                max_corner.y()) ;
        
        z.range(min_corner.z(),
                max_corner.z()) ;

        return *this ;
    }
} ;

} // anon namespace

struct Simple_UI::Private
{
    typedef
    util::auto_ptr_vector<Real_Valuator_impl>
    Real_Valuators ;

    typedef
    util::auto_ptr_vector<Complex_Valuator_impl>
    Complex_Valuators ;

    typedef
    util::auto_ptr_vector<Pure_Valuator_impl>
    Pure_Valuators ;

    typedef
    util::auto_ptr_vector<Quat_Valuator_impl>
    Quat_Valuators ;

    struct Translator
        : public ui::extra::Valuator_Handler,
          public ui::extra::Toggle_Handler,
          public ui::extra::File_Selector_Handler
    {
        Simple_UI::Private & m ;

        Translator( Simple_UI::Private & m_ )
            : m(m_) { }

        bool handle_valuator( const ui::extra::Valuator & ) ;
        bool handle_toggle( const ui::extra::Toggle & ) ;
        bool handle_file_selector( const ui::extra::File_Selector & ) ;
    } ;

    struct Own_Simple_UI
        : public ui::extra::Simple_UI
    {
        components::dimn::impl::Simple_UI::Private & m ;
        
        Own_Simple_UI( ui::base::Display & display,
                       components::dimn::impl::Simple_UI::Private & m_ )
            : ui::extra::Simple_UI(display),
              m(m_) { }
    } ;

    static void base_catch_function( kernel::Catcher &,
                                     std::exception & ) ;

    //
    // ui ----> cache ----> translator ----> outside
    //

    Own_Simple_UI ui ;
    kernel::Caching_Node cache ;
    Translator translator ;
    Simple_UI & outside ;

    Real_Valuators real_valuators ;
    Complex_Valuators complex_valuators ;
    Pure_Valuators pure_valuators ;
    Quat_Valuators quat_valuators ;

    Catch_Function catch_function ;

    Private( ui::base::Display & , Simple_UI & ) ;
    ~Private() ;

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

Simple_UI::Private::
Private( ui::base::Display & display,
         Simple_UI & outside_ )
    : ui(display, *this),
      cache(false),
      translator(*this),
      outside(outside_),
      real_valuators(),
      complex_valuators(),
      pure_valuators(),
      quat_valuators(),
      catch_function(0)
{
    ui.add_handler(cache) ;
    cache.add_handler(translator) ;
    ui.catch_function(&base_catch_function) ;
}

Simple_UI::Private::
~Private()
{
}

Simple_UI::
Simple_UI( ui::base::Display & display )
    : m(new Private(display, *this))
{
}

Simple_UI::
~Simple_UI()
{
}

Real_Valuator &
Simple_UI::
create_valuator( real initial_value,
                 const std::string & label )
{
    m->cache.start_caching() ;

    if( label != "" )
    {
        m->ui.create_label(label) ;
    }

    ui::extra::Valuator & re = m->ui.create_valuator(initial_value) ;

    m->real_valuators.push_back(std::auto_ptr<Real_Valuator_impl>(
        new Real_Valuator_impl(re))) ;

    m->cache.stop_caching() ;

    return *m->real_valuators.back() ;
}

Complex_Valuator &
Simple_UI::
create_valuator( const complex & initial_value,
                 const std::string & label )
{
    m->cache.start_caching() ;

    if( label != "" )
    {
        m->ui.create_label(label) ;
    }

    ui::extra::Valuator & re = m->ui.create_valuator(initial_value.real()) ;
    ui::extra::Valuator & im = m->ui.create_valuator(initial_value.imag()) ;

    m->complex_valuators.push_back(std::auto_ptr<Complex_Valuator_impl>(
        new Complex_Valuator_impl(re, im))) ;

    m->cache.stop_caching() ;

    return *m->complex_valuators.back() ;
}

Pure_Valuator &
Simple_UI::
create_valuator( const pure & initial_value,
                 const std::string & label )
{
    m->cache.start_caching() ;

    if( label != "" )
    {
        m->ui.create_label(label) ;
    }

    ui::extra::Valuator & x = m->ui.create_valuator(initial_value.x()) ;
    ui::extra::Valuator & y = m->ui.create_valuator(initial_value.y()) ;
    ui::extra::Valuator & z = m->ui.create_valuator(initial_value.z()) ;

    m->pure_valuators.push_back(std::auto_ptr<Pure_Valuator_impl>(
        new Pure_Valuator_impl(x, y, z))) ;

    m->cache.stop_caching() ;

    return *m->pure_valuators.back() ;
}

Quat_Valuator &
Simple_UI::
create_valuator( const quat & initial_value,
                 const std::string & label )
{
    m->cache.start_caching() ;

    if( label != "" )
    {
        m->ui.create_label(label) ;
    }

    ui::extra::Valuator & w = m->ui.create_valuator(initial_value.w()) ;
    ui::extra::Valuator & x = m->ui.create_valuator(initial_value.x()) ;
    ui::extra::Valuator & y = m->ui.create_valuator(initial_value.y()) ;
    ui::extra::Valuator & z = m->ui.create_valuator(initial_value.z()) ;

    m->quat_valuators.push_back(std::auto_ptr<Quat_Valuator_impl>(
        new Quat_Valuator_impl(w, x, y, z))) ;

    m->cache.stop_caching() ;

    return *m->quat_valuators.back() ;
}

bool
Simple_UI::Private::Translator::
handle_toggle( const ui::extra::Toggle & toggle )
{
    return m.outside.emit_toggle(toggle) ;
}

bool
Simple_UI::Private::Translator::
handle_file_selector( const ui::extra::File_Selector & file_selector )
{
    return m.outside.emit_file_selector(file_selector) ;
}

bool
Simple_UI::Private::Translator::
handle_valuator( const ui::extra::Valuator & valuator )
{
    for( Private::Real_Valuators::const_iterator i =
             m.real_valuators.begin() ;
         i != m.real_valuators.end() ;
         ++i )
    {
        if( &(**i).re == &valuator )
        {
            return m.outside.emit_valuator(**i) ;
        }
    }

    for( Private::Complex_Valuators::const_iterator i =
             m.complex_valuators.begin() ;
         i != m.complex_valuators.end() ;
         ++i )
    {
        if( &(**i).re == &valuator
            ||
            &(**i).im == &valuator )
        {
            return m.outside.emit_valuator(**i) ;
        }
    }

    for( Private::Pure_Valuators::const_iterator i =
             m.pure_valuators.begin() ;
         i != m.pure_valuators.end() ;
         ++i )
    {
        if( &(**i).x == &valuator
            ||
            &(**i).y == &valuator
            ||
            &(**i).z == &valuator )
        {
            return m.outside.emit_valuator(**i) ;
        }
    }

    for( Private::Quat_Valuators::const_iterator i =
             m.quat_valuators.begin() ;
         i != m.quat_valuators.end() ;
         ++i )
    {
        if( &(**i).w == &valuator
            ||
            &(**i).x == &valuator
            ||
            &(**i).y == &valuator
            ||
            &(**i).z == &valuator )
        {
            return m.outside.emit_valuator(**i) ;
        }
    }

    assert(!"handle_valuator() logical error") ;
    return false ;
}

void
Simple_UI::
create_label( const std::string & label )
{
    m->ui.create_label(label) ;
}

ui::extra::File_Selector &
Simple_UI::
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
Simple_UI::
create_help( const std::string & text,
             const std::string & label )
{
    m->ui.create_help(text, label) ;
}

ui::extra::Toggle &
Simple_UI::
create_toggle( bool initial_value,
               const std::string & label )
{
    return m->ui.create_toggle(initial_value, label) ;
}

void
Simple_UI::
toggle_modal_visible()
{
    m->ui.toggle_modal_visible() ;
}

void
Simple_UI::
toggle_display_fullscreen()
{
    m->ui.toggle_display_fullscreen() ;
}

void
Simple_UI::Private::
base_catch_function( kernel::Catcher & ui_, std::exception & e )
{
    Own_Simple_UI* ui = dynamic_cast<Own_Simple_UI*>(&ui_) ;
    assert(ui && "base_catch_function() logical error") ;

    if( ui->m.catch_function )
    {
        (*ui->m.catch_function)(ui->m.outside, e) ;
    }
    else
    {
        throw ;
    }
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

}}}} // namespace esve::components::dimn::impl
