//
// misc math functions
//

#ifndef esve_math_misc_hxx
#define esve_math_misc_hxx

#include <esve/math/constants.hxx>
#include <cmath>

namespace esve { namespace math {

namespace misc {

//
// correctly mods negative numbers
//
template< typename F >
inline
F fmodp( F a, F n = F(1) )
{
    const F tmp = std::fmod(a, n) ;
    return tmp >= 0 ? tmp : tmp + n ;
}

template< typename F >
F round( F a )
{
    F n ;
    const F frac = std::modf(a, &n) ;
    return frac >= F(0.5) ? n + F(1) : n ;
}

template< typename F >
inline
F deg2rad( F d )
{
    return d*F(constants::PI)/F(180) ;
}

template< typename F >
inline
F rad2deg( F r )
{
    return r*F(180)/F(constants::PI) ;
}

} // namespace misc

}} // namespace esve::math

#endif
