
#include <esve/viewers/dim3/Surface_Viewer.hxx>
#include <esve/geom/dim3/specs/Regular_Spec.hxx>
#include <esve/math/misc.hxx>
#include <cmath>

using esve::viewers::dim3::Surface_Viewer ;
using esve::geom::dim3::specs::Regular_Spec ;
using esve::math::misc::fmodp ;

////////////////////////////////////////////////////////////
//
// help
//
////////////////////////////////////////////////////////////

const std::string HELP =
"\n"
"The function f(u,v) = cos(u)cos(v) with various adjustable parameters.\n"
"\n"
;

////////////////////////////////////////////////////////////
//
// Waves
//
////////////////////////////////////////////////////////////

struct Waves : public Regular_Spec
{
    complex domain_size ;
    complex bumps ;
    complex motion ;
    real amplitude ;
    real scale_color ;
    real slide_color ;

    Waves()
        : domain_size(1.0, 1.0),
          bumps(4.0, 4.0),
          motion(0.0, 0.0),
          amplitude(0.15),
          scale_color(0.25),
          slide_color(0.70) { }

    complex domain( const complex & unit_square ) const
    {
        const complex centered = real(2)*unit_square - complex(1, 1) ;

        return complex(domain_size.real()*centered.real(),
                       domain_size.imag()*centered.imag()) ;
    }

    pure surface( const complex & unit_square,
                  const complex & domain ) const
    {
        return pure(domain.real(),
                    domain.imag(),
                    amplitude
                    *
                    std::cos(bumps.real()*domain.real()*PI_2
                             +
                             motion.real())
                    *
                    std::cos(bumps.imag()*domain.imag()*PI_2
                             +
                             motion.imag())) ;
    }

    rgba color( const complex & unit_square,
                const complex & domain,
                const pure & surface ) const
    {
        return
            rgba::from_hsva(
               fmodp(unit_square.real()*unit_square.imag()*scale_color
                     +
                     slide_color),
               0.75,
               0.75,
               1.0) ;
    }
} ;

////////////////////////////////////////////////////////////
//
// Viewer
//
////////////////////////////////////////////////////////////

struct Viewer : public Surface_Viewer<Waves>
{
    Viewer( int argc, char** argv )
        : Surface_Viewer<Waves>(argc, argv, "waves")
    {
        create_help(HELP + help_text()) ;
        create_scaling_valuator().value(1.5) ;
        create_resolution_valuator().value(100, 100) ;

        create_valuator(&Waves::amplitude,
                        CHANGES_SURFACE,
                        "amplitude").step(0.001) ;

        create_valuator(&Waves::bumps,
                        CHANGES_SURFACE,
                        "bumps").step(0.005, 0.005) ;

        create_valuator(&Waves::domain_size,
                        CHANGES_DOMAIN,
                        "domain size").step(0.005, 0.005) ;

        create_valuator(&Waves::motion,
                        CHANGES_SURFACE,
                        "motion").step(0.01, 0.01) ;

        create_valuator(&Waves::scale_color,
                        CHANGES_COLOR,
                        "scale color").step(0.002) ;

        create_valuator(&Waves::slide_color,
                        CHANGES_COLOR,
                        "slide color").step(0.002) ;
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

