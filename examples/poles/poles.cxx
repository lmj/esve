
#include <esve/viewers/dim4/Surface_Viewer.hxx>
#include <esve/geom/dim4/specs/Disc_With_Two_Holes.hxx>
#include <cmath>
#include <algorithm>

using esve::viewers::dim4::Surface_Viewer ;
using esve::geom::dim4::specs::Disc_With_Two_Holes ;

////////////////////////////////////////////////////////////
//
// help
//
////////////////////////////////////////////////////////////

const std::string HELP =
"\n"
"The complex function\n"
"\n"
"    f(z) = 1/[(z + r)(z - r)]\n"
"\n"
"where the real number r is the 'separation' parameter.\n"
"\n"
"The 'inversion' parameter is the reciprocal of the point at infinity.\n"
"\n"
;

////////////////////////////////////////////////////////////
//
// Poles
//
////////////////////////////////////////////////////////////

class Poles : public Disc_With_Two_Holes
{
private:
    real m_scale_fz ;
    real m_scale_color ;

public:
    //////////////////////////////////////////////////////////
    // surface description
    //////////////////////////////////////////////////////////

    Poles()
        : Disc_With_Two_Holes(
              Circle(complex(0, 0), 2.5),
              Circle(complex(1, 0), 0.25),
              Circle(complex(-1, 0), 0.25)),
          m_scale_fz(1),
          m_scale_color(0.2) { }

    quat surface( const complex & unit_square,
                  const complex & domain ) const
    {
        const complex fz =
            real(1)
            /
            ((domain - hole0().center())
             *
             (domain - hole1().center())) ;

        return quat(m_scale_fz*fz.imag(),
                    domain.real(),
                    domain.imag(),
                    m_scale_fz*fz.real()) ;
    }

    rgba color( const complex & unit_square,
                const complex & domain,
                const quat & surface ) const
    {
        // color roots
        return
            rgba::from_hsva(
                std::min(
                    std::abs(
                        m_scale_color
                        *
                        std::sqrt(surface.w()*surface.w()
                                  +
                                  surface.z()*surface.z())),
                    real(0.7)),
                0.8,
                0.8,
                1.0) ;
    }

    //////////////////////////////////////////////////////////
    // UI values
    //////////////////////////////////////////////////////////

    ///////////////////////////////////
    // disc radius
    
    real disc_radius() const
    {
        return disc().radius() ;
    }

    void disc_radius( real a )
    {
        disc(Circle(disc().center(), a)) ;
    }

    ///////////////////////////////////
    // hole radius
    
    real hole_radius() const
    {
        return hole0().radius() ;
    }

    void hole_radius( real a )
    {
        hole0(Circle(hole0().center(), a)) ;
        hole1(Circle(hole1().center(), a)) ;
    }

    ///////////////////////////////////
    // separation
    
    real separation() const
    {
        return hole0().center().real() ;
    }

    void separation( real a )
    {
        hole0(Circle(complex(a, 0), hole0().radius())) ;
        hole1(Circle(complex(-a, 0), hole1().radius())) ;
    }

    ///////////////////////////////////
    // scale f(z)
    
    real scale_fz() const
    {
        return m_scale_fz ;
    }

    void scale_fz( real a )
    {
        m_scale_fz = a ;
    }

    ///////////////////////////////////
    // scale color
    
    real scale_color() const
    {
        return m_scale_color ;
    }

    void scale_color( real a )
    {
        m_scale_color = a ;
    }
} ;

////////////////////////////////////////////////////////////
//
// Viewer
//
////////////////////////////////////////////////////////////

struct Viewer : public Surface_Viewer<Poles>
{
    Viewer( int argc, char** argv )
        : Surface_Viewer<Poles>(argc, argv, "poles")
    {
        create_help(HELP + help_text()) ;
        create_scaling_valuator().value(0.75) ;
        create_resolution_valuator().value(120, 120) ;

        create_valuator(&Poles::disc_radius,
                        &Poles::disc_radius,
                        CHANGES_DOMAIN,
                        "domain radius").range(0, MAX_REAL).step(0.005) ;

        create_valuator(&Poles::hole_radius,
                        &Poles::hole_radius,
                        CHANGES_DOMAIN_CLIP,
                        "hole radius").range(0, MAX_REAL).step(0.001) ;

        create_valuator(&Poles::separation,
                        &Poles::separation,
                        CHANGES_DOMAIN,
                        "separation").range(0, MAX_REAL).step(0.002) ;

        create_valuator(&Poles::scale_fz,
                        &Poles::scale_fz,
                        CHANGES_SURFACE,
                        "scale f(z)").range(0, MAX_REAL).step(0.0025) ;

        create_valuator(&Poles::scale_color,
                        &Poles::scale_color,
                        CHANGES_COLOR,
                        "scale color").range(0, MAX_REAL).step(0.001) ;

        create_inversion_valuator().value(0) ;
        create_hide_back_toggle() ;
    }
} ;

////////////////////////////////////////////////////////////
//
// main
//
////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    return Viewer(argc, argv).takeover() ;
}
