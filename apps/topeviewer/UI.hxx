
//
// Abstract user interface
//

#ifndef apps_topeviewer_UI_hxx
#define apps_topeviewer_UI_hxx

#include <esve/components/dimn/impl/Simple_UI.hxx>
#include <esve/components/dimn/Valuator.hxx>
#include <esve/ui/extra/File_Selector.hxx>
#include <esve/types/real.hxx>
#include <vector>

/////////////////////////////////////////////////////////////
//
// UI
//
/////////////////////////////////////////////////////////////

class UI
    : public esve::components::dimn::impl::Simple_UI
{
private:
    typedef
    esve::components::dimn::Valuator<esve::types::real>
    m_Valuator ;

    typedef
    std::vector<m_Valuator*>
    m_Valuators ;

    UI( const UI & ) ;
    UI & operator=( const UI & ) ;

    m_Valuators m_valuators ;
    esve::ui::extra::File_Selector* m_file_selector ;

public:
    typedef esve::types::real real ;

    // file format depends on this ordering!
    enum Valuator_ID
    {
        SLIDE_COLOR,
        MIN_LENGTH,
        MAX_LENGTH,
        TUBE_RADIUS,
        CUT_EDGES_MIN,
        CUT_EDGES_MAX,
        BALL_RADIUS,
        CUT_BALLS_MIN,
        CUT_BALLS_MAX,
        CAMERA_ZPOS,
        INVERSION,
        CAMERA_FOV // determines size
    } ;

    typedef m_Valuator Valuator ;

    typedef m_Valuators::const_iterator Valuators_const_iterator ;

    UI( esve::ui::base::Display & ) ;

    Valuators_const_iterator valuators_begin() const
    {
        return m_valuators.begin() ;
    }

    Valuators_const_iterator valuators_end() const
    {
        return m_valuators.end() ;
    }

    Valuator & valuator( Valuator_ID a ) const
    {
        return *m_valuators[a] ;
    }

    // convenience methods

    esve::types::real inversion() const
    {
        return valuator(INVERSION).value() ;
    }

    void inversion( esve::types::real a )
    {
        valuator(INVERSION).value(a) ;
    }

    void min_length( esve::types::real a )
    {
        valuator(MIN_LENGTH).value(a) ;
    }

    void min_length_range( esve::types::real a, esve::types::real b )
    {
        valuator(MIN_LENGTH).range(a, b) ;
    }

    esve::types::real max_length() const
    {
        return valuator(MAX_LENGTH).value() ;
    }

    void max_length( esve::types::real a )
    {
        valuator(MAX_LENGTH).value(a) ;
    }

    void max_length_range( esve::types::real a, esve::types::real b )
    {
        valuator(MAX_LENGTH).range(a, b) ;
    }

    esve::types::real slide_color() const
    {
        return valuator(SLIDE_COLOR).value() ;
    }

    void slide_color( esve::types::real a )
    {
        valuator(SLIDE_COLOR).value(a) ;
    }

    esve::types::real cut_edges_min() const
    {
        return valuator(CUT_EDGES_MIN).value() ;
    }

    void cut_edges_min( esve::types::real a )
    {
        valuator(CUT_EDGES_MIN).value(a) ;
    }

    esve::types::real cut_edges_max() const
    {
        return valuator(CUT_EDGES_MAX).value() ;
    }

    void cut_edges_max( esve::types::real a )
    {
        valuator(CUT_EDGES_MAX).value(a) ;
    }

    esve::types::real cut_balls_min() const
    {
        return valuator(CUT_BALLS_MIN).value() ;
    }

    void cut_balls_min( esve::types::real a )
    {
        valuator(CUT_BALLS_MIN).value(a) ;
    }

    esve::types::real cut_balls_max() const
    {
        return valuator(CUT_BALLS_MAX).value() ;
    }

    void cut_balls_max( esve::types::real a )
    {
        valuator(CUT_BALLS_MAX).value(a) ;
    }

    esve::types::real tube_radius() const
    {
        return valuator(TUBE_RADIUS).value() ;
    }

    void tube_radius( esve::types::real a )
    {
        valuator(TUBE_RADIUS).value(a) ;
    }

    esve::types::real ball_radius() const
    {
        return valuator(BALL_RADIUS).value() ;
    }

    void ball_radius( esve::types::real a )
    {
        valuator(BALL_RADIUS).value(a) ;
    }

    esve::types::real camera_zpos() const
    {
        return valuator(CAMERA_ZPOS).value() ;
    }

    void camera_zpos( esve::types::real a )
    {
        valuator(CAMERA_ZPOS).value(a) ;
    }

    esve::types::real field_of_view() const
    {
        return valuator(CAMERA_FOV).value() ;
    }

    void field_of_view( esve::types::real a )
    {
        valuator(CAMERA_FOV).value(a) ;
    }

    const std::string & filename() const
    {
        return m_file_selector->value() ;
    }

    void filename( const std::string & a )
    {
        m_file_selector->value(a) ;
    }

    ~UI() ;
} ;

#endif

