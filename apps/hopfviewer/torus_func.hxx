//
// Mathematical functions for the torus.
//

#ifndef apps_hopfviewer_torus_func_hxx
#define apps_hopfviewer_torus_func_hxx

#include <esve/math/constants.hxx>
#include <esve/math/misc.hxx>
#include <cmath>

namespace torus_func {

/////////////////////////////////////////////////////////////
//
// computing the torus points.
//
// order of operations:
// 1. start with a unit square domain [0,1],[0,1]
// 2. skew
// 3. stretch
// 4. rotate
// 5. color
// 6. apply torus function
//
/////////////////////////////////////////////////////////////

//
// skew.
//
// Skew lifts the right-hand edge of the domain vertically by some factor.
//
template< typename complex >
inline
complex skew( const complex & z, typename complex::value_type skew_factor )
{
    return complex(z.real(),
                   skew_factor*z.real() + z.imag()) ;
}

//
// stretch factor.
//
// For winding (u,v) (that is, slope v/u), shrink the width and
// stretch the height as such:
//
template< typename complex >
inline
complex stretch_factor( const complex & winding )
{
    typedef typename complex::value_type value_type ;

    const value_type s = abs(winding) ;
    return complex(value_type(1)/s, s) ;
}

//
// stretch.
//
template< typename complex >
inline
complex stretch( const complex & z, const complex & stretch_factor )
{
    return complex(stretch_factor.real()*z.real(),
                   stretch_factor.imag()*z.imag()) ;
}

//
// rotation factor.
//
// For winding (u,v), rotate the domain clockwise so that the left
// edge lies on the vector (u,v)
//
template< typename complex >
inline
complex rotation_factor( const complex & winding )

{
    const complex rotation = complex(winding.imag(), -winding.real()) ;
    return rotation/abs(rotation) ;
}

//
// rotate.
//
template< typename complex >
inline
complex rotate( const complex & z, const complex & rotation_factor )
{
    return rotation_factor*z ;
}

//
// color.
//
// Coloring is done such that a single Hopf fiber has the same color.
// Parallel fibers increase in hue and are scaled to match on round
// trip.
//
template< typename complex, typename rgba >
inline
rgba color( const complex & z )
{
    using esve::math::misc::fmodp ;

    typedef typename complex::value_type value_type ;
    typedef typename rgba::value_type color_value_type ;
    typedef typename rgba::from_hsva from_hsva ;

    const value_type u = fmodp(z.real(), value_type(1)) ;
    const value_type v = fmodp(z.imag(), value_type(1)) ;
    const value_type u1 = u > v ? u : u + 1 ;
    return from_hsva(color_value_type(u1 - v),
                     color_value_type(0.85),
                     color_value_type(0.85),
                     color_value_type(1.0)) ;
}

//
// torus function.
//
// Operates on the domain [0,2pi],[0,2pi]
//
// r1 and r2 are the radii of the generating circles.
//
template< typename complex, typename quat >
inline
quat torus( const complex & z,
            typename complex::value_type r1,
            typename complex::value_type r2 )
{
    return quat(r1*std::cos(z.real()),
                r1*std::sin(z.real()),
                r2*std::cos(z.imag()),
                r2*std::sin(z.imag())) ;
}

//
// finally, create the OpenGL vertex.
//
// Vertex structure is:
//     color
//     normal
//     transformed_point
//     point
//
template< typename complex, typename Vertex >
inline
Vertex torus_vertex( const complex & z,
                     typename complex::value_type r1,
                     typename complex::value_type r2,
                     typename complex::value_type skew_factor,
                     const complex & stretch_factor,
                     const complex & rotation_factor )
{
    using esve::math::constants::TWO_PI ;

    typedef typename complex::value_type value_type ;

    typedef typename Vertex::Color Color ;
    typedef typename Vertex::Normal Normal ;
    typedef typename Vertex::Transformed_Point Transformed_Point ;
    typedef typename Vertex::Point Point ;

    const complex fz = rotate(
                              stretch(
                                      skew(
                                           z,
                                           skew_factor
                                           ),
                                      stretch_factor
                                      ),
                              rotation_factor
                              ) ;

    return Vertex(color<complex, Color>(fz),
                  Normal(),
                  Transformed_Point(),
                  torus<complex, Point>(value_type(TWO_PI)*fz, r1, r2)) ;
}

/////////////////////////////////////////////////////////////
//
// parameterization by squares.
//
// Given the above operations, the skew parameter is sufficient to
// make a rectangular grid on the torus, offsetting the radii ratio and
// the winding.
//
// Consider a torus with radii r1 and r2 as a transformation on the
// domain:
//
//     f(z1 + z2 i) = (r1/r2) z1 + (r2/r1) z2 i.
//
// regularized_slope(r1,r2,u,v) gives the pre-image of this
// transformation for the slope v/u.
//
// Likewise regularized_skew(r1,r2,u,v) gives the pre-image of the
// skew amount needed to form a grid perpendicular to the slope v/u.
//
// Both formulas below are derived from elementary plane geometry.
//
/////////////////////////////////////////////////////////////

template< typename real >
inline
real regularized_slope( real r1, real r2, real u, real v )
{
    return u*u*r1/r2 + v*v*r2/r1 ;
}

template< typename real >
real regularized_skew( real r1, real r2, real u, real v )
{
    const real p = real(1)/(r1*r1*u*u + r2*r2*v*v) ;
    const real q = real(1)/(u*u + v*v) ;

    const real a = r1*r1*p - q ;
    const real b = r2*r2*p - q ;

    const real d = a*a*u*u + b*b*v*v ;

    const real skew = std::sqrt(d*q) ;

    if( r1 > r2 )
    {
        return -skew ;
    }

    return skew ;
}

} // namespace torus_func

#endif

