
#ifndef platform_fltk_esve_platform_MF_Widget_hxx
#define platform_fltk_esve_platform_MF_Widget_hxx

#include <string>

class Fl_Widget ;

namespace esve { namespace platform {

//////////////////////////////////////////////////////////////
//
// MF_Widget
//
// Define a widget whose callback is a member function.
// (convenience only)
//
//////////////////////////////////////////////////////////////

template< typename T_Widget, typename T_Target >
class MF_Widget
    : public T_Widget
{
private:
    typedef T_Widget super ;
    typedef T_Target m_Target ;
    typedef void (m_Target::*m_Function)(void) ;

    MF_Widget( const MF_Widget & ) ;
    MF_Widget & operator=( const MF_Widget & ) ;

    static void m_widget_callback( Fl_Widget*, void* data ) ;

    m_Target & m_target ;
    m_Function m_function ;
    const std::string m_label ;

public:
    typedef m_Target Target ;
    typedef m_Function Function ;

    MF_Widget( int x, int y, int w, int h,
               const std::string & n,
               Target & target,
               Function function ) ;

    ~MF_Widget() ;
} ;

template< typename T_Widget, typename T_Target >
MF_Widget<T_Widget, T_Target>::
MF_Widget( int x, int y, int w, int h,
           const std::string & l,
           Target & target,
           Function function )
    : super(x, y, w, h, ""),
      m_target(target),
      m_function(function),
      m_label(l)
{
    super::callback(&m_widget_callback) ;
    super::user_data(this) ;
    super::label(m_label.c_str()) ;
}

template< typename T_Widget, typename T_Target >
MF_Widget<T_Widget, T_Target>::
~MF_Widget()
{
}

template< typename T_Widget, typename T_Target >
void
MF_Widget<T_Widget, T_Target>::
m_widget_callback( Fl_Widget*, void* data )
{
    MF_Widget* widget = static_cast<MF_Widget*>(data) ;
    ((widget->m_target).*(widget->m_function))() ;
}

}} // namespace esve::platform

#endif

