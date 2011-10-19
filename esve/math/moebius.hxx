
#ifndef esve_math_moebius_hxx
#define esve_math_moebius_hxx

#include <esve/math/quat.hxx>

namespace esve { namespace math {

namespace moebius {

#if !defined(QUAT_CONSERVE_MULTIPLIES)
//
// (a*t + b)*inv(c*t + d)
//
template< typename real >
math::quat<real>
moebius( const math::quat<real> & a,
         const math::quat<real> & b,
         const math::quat<real> & c,
         const math::quat<real> & d,
         const math::quat<real> & t )
{
    typedef math::quat<real> quat ;

    // a*t + b
    const quat r(
        a.w()*t.w() - a.x()*t.x() - a.y()*t.y() - a.z()*t.z() + b.w(),
        a.w()*t.x() + a.x()*t.w() + a.y()*t.z() - a.z()*t.y() + b.x(),
        a.w()*t.y() - a.x()*t.z() + a.y()*t.w() + a.z()*t.x() + b.y(),
        a.w()*t.z() + a.x()*t.y() - a.y()*t.x() + a.z()*t.w() + b.z()) ;

    // conj(c*t + d)
    const quat s(
        c.w()*t.w() - c.x()*t.x() - c.y()*t.y() - c.z()*t.z() + d.w(),
        c.z()*t.y() - c.w()*t.x() - c.x()*t.w() - c.y()*t.z() - d.x(),
        c.x()*t.z() - c.w()*t.y() - c.y()*t.w() - c.z()*t.x() - d.y(),
        c.y()*t.x() - c.w()*t.z() - c.x()*t.y() - c.z()*t.w() - d.z()) ;

    // 1/norm(c*t + d)
    const real h =
        real(1)/norm(s) ;

    // (a*t + b)*inv(c*t + d)
    return quat(
        (r.w()*s.w() - r.x()*s.x() - r.y()*s.y() - r.z()*s.z())*h,
        (r.w()*s.x() + r.x()*s.w() + r.y()*s.z() - r.z()*s.y())*h,
        (r.w()*s.y() - r.x()*s.z() + r.y()*s.w() + r.z()*s.x())*h,
        (r.w()*s.z() + r.x()*s.y() - r.y()*s.x() + r.z()*s.w())*h) ;
}
#endif // !defined(QUAT_CONSERVE_MULTIPLIES)

#if defined(QUAT_CONSERVE_MULTIPLIES)
//
// (a*t + b)*inv(c*t + d)
//
template< typename real >
math::quat<real>
moebius( const math::quat<real> & a,
         const math::quat<real> & b,
         const math::quat<real> & c,
         const math::quat<real> & d,
         const math::quat<real> & t )
{
    return (a*t + b)*inv(c*t + d) ;
}
#endif // defined(QUAT_CONSERVE_MULTIPLIES)

} // namespace moebius

}} // namespace esve::math

#endif
