
#include <esve/viewers/dim4/Surface_Viewer.hxx>
#include <esve/geom/dim4/specs/Polar_Annulus.hxx>
#include <algorithm>

using esve::viewers::dim4::Surface_Viewer ;
using esve::geom::dim4::specs::Polar_Annulus ;

////////////////////////////////////////////////////////////
//
// help
//
////////////////////////////////////////////////////////////

const std::string HELP =
"\n"
"The complex function\n"
"\n"
"      f(z) = z^p - r.\n"
"\n"
"for real p and real r.\n"
"\n"
"The 'power' parameter corresponds to p and the 'root radius'\n"
"parameter corresponds to r.\n"
"\n"
"The 'inversion' parameter is the reciprocal of the point at infinity.\n"
"\n"
;

////////////////////////////////////////////////////////////
//
// Monomial
//
////////////////////////////////////////////////////////////

struct Monomial : public Polar_Annulus
{
    real scale_fz ;
    real power ;
    real root_radius ;
    real scale_color ;

    Monomial()
        : Polar_Annulus(0.1, 1.0),
          scale_fz(1.0),
          power(3.0),
          root_radius(0.0),
          scale_color(0.7) { }

    quat surface( const complex & ,
                  const complex & domain ) const
    {
        const complex fz =
            pow(domain, power) - root_radius ;

        return quat(scale_fz*fz.imag(),
                    domain.real(),
                    domain.imag(),
                    scale_fz*fz.real()) ;
    }

    rgba color( const complex & ,
                const complex & domain,
                const quat & ) const
    {
        return
            rgba::from_hsva(
                std::min(
                    abs(domain)*scale_color,
                    real(0.7)),
                0.8,
                0.8,
                1.0) ;
    }
} ;

////////////////////////////////////////////////////////////
//
// Viewer
//
////////////////////////////////////////////////////////////

struct Viewer : public Surface_Viewer<Monomial>
{
    Viewer( int argc, char** argv )
        : Surface_Viewer<Monomial>(argc, argv, "monomial")
    {
        create_help(HELP + help_text()) ;
        create_scaling_valuator().value(1) ;
        create_resolution_valuator().value(30, 200) ;

        create_label("domain") ;

        create_valuator(&Monomial::inner_radius,
                        &Monomial::inner_radius,
                        CHANGES_DOMAIN).step(0.001).range(0.0001, MAX_REAL) ;

        create_valuator(&Monomial::outer_radius,
                        &Monomial::outer_radius,
                        CHANGES_DOMAIN).step(0.001).range(0.0001, MAX_REAL) ;

        create_valuator(&Monomial::scale_fz,
                        CHANGES_SURFACE,
                        "scale f(z)").step(0.001).range(0, MAX_REAL) ;

        create_valuator(&Monomial::power,
                        CHANGES_SURFACE,
                        "power").step(0.01) ;

        create_valuator(&Monomial::root_radius,
                        CHANGES_DOMAIN,
                        "root radius").step(0.001).range(0, MAX_REAL) ;

        create_valuator(&Monomial::scale_color,
                        CHANGES_COLOR,
                        "scale color").step(0.005).range(0, MAX_REAL) ;

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

