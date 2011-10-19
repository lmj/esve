//
// quaternions.
//
// A quaternion whose real part is zero is called a 'pure quaternion',
// or a 'pure', and is represented here by the 'pure' class.
//
// This leads to a naming conflict in the analogy with complex
// numbers.  The <complex> header declares
//
//     template<typename F> F real( const complex<F> & ) ;
//     template<typename F> F imag( const complex<F> & ) ;
//
// A function named 'pure' would conflict with the constructor for the
// pure class, and it would be wrong to construct a pure from a
// quaternion due to the resulting loss of data.  Therefore we need
// new names,
//
//     template<typename F> F       realpart( const quat<F> & ) ;
//     template<typename F> pure<F> purepart( const quat<F> & ) ;
//
// instead of just 'real' and 'pure' as one might initially expect.
//
// quat(w, x, y, z) constructs a quaternion with w as the real part.
// Note, however, that the real part appears last in the data layout
// (for OpenGL vertex arrays).
//
// I have disallowed as many conversions as possible, because
// conversions are stupid.
//
// For machines whose float multiply is relatively more expensive,
// defining QUAT_CONSERVE_MULTIPLIES may give better performance.
//

#ifndef esve_math_quat_hxx
#define esve_math_quat_hxx

#include <istream>
#include <ostream>
#include <cmath>

namespace esve { namespace math {

namespace quat_namespace {

template<typename F> class quat ;
template<typename F> class pure ;

template<typename F> F realpart( const quat<F> & ) ;
template<typename F> F realpart( const pure<F> & ) ;

template<typename F> const pure<F>   purepart( const quat<F> & ) ;
template<typename F> const pure<F> & purepart( const pure<F> & ) ;

template<typename F> F norm( const quat<F> & ) ;
template<typename F> F norm( const pure<F> & ) ;

template<typename F> F abs( const quat<F> & ) ;
template<typename F> F abs( const pure<F> & ) ;

template<typename F> quat<F> conj( const quat<F> & ) ;
template<typename F> pure<F> conj( const pure<F> & ) ;

template<typename F> quat<F> inv( const quat<F> & ) ;
template<typename F> pure<F> inv( const pure<F> & ) ;

template<typename F> F dot( const quat<F> &, const quat<F> & ) ;
template<typename F> F dot( const quat<F> &, const pure<F> & ) ;
template<typename F> F dot( const pure<F> &, const quat<F> & ) ;
template<typename F> F dot( const pure<F> &, const pure<F> & ) ;

template<typename F> F dot( const quat<F> &, F ) ;
template<typename F> F dot( const pure<F> &, F ) ;
template<typename F> F dot( F, const quat<F> & ) ;
template<typename F> F dot( F, const pure<F> & ) ;

template<typename F> pure<F> cross( const quat<F> &, const quat<F> & ) ;
template<typename F> pure<F> cross( const quat<F> &, const pure<F> & ) ;
template<typename F> pure<F> cross( const pure<F> &, const quat<F> & ) ;
template<typename F> pure<F> cross( const pure<F> &, const pure<F> & ) ;

template<typename F> pure<F> cross( const quat<F> &, F ) ;
template<typename F> pure<F> cross( const pure<F> &, F ) ;
template<typename F> pure<F> cross( F, const quat<F> & ) ;
template<typename F> pure<F> cross( F, const pure<F> & ) ;

template<typename F> quat<F> exp( const quat<F> & ) ;
template<typename F> quat<F> exp( const pure<F> & ) ;

template<typename F> quat<F> log( const quat<F> & ) ;
template<typename F> quat<F> log( const pure<F> & ) ;

template<typename F> quat<F> cos( const quat<F> & ) ;
template<typename F> quat<F> cos( const pure<F> & ) ;
template<typename F> quat<F> sin( const quat<F> & ) ;
template<typename F> quat<F> sin( const pure<F> & ) ;
template<typename F> quat<F> tan( const quat<F> & ) ;
template<typename F> quat<F> tan( const pure<F> & ) ;
template<typename F> quat<F> cosh( const quat<F> & ) ;
template<typename F> quat<F> cosh( const pure<F> & ) ;
template<typename F> quat<F> sinh( const quat<F> & ) ;
template<typename F> quat<F> sinh( const pure<F> & ) ;
template<typename F> quat<F> tanh( const quat<F> & ) ;
template<typename F> quat<F> tanh( const pure<F> & ) ;

template<typename F> quat<F> pow( const quat<F> &, unsigned int ) ;
template<typename F> quat<F> pow( const quat<F> &, int ) ;
template<typename F> quat<F> pow( const quat<F> &, F ) ;
template<typename F> quat<F> pow( F, const quat<F> & ) ;
template<typename F> quat<F> pow( const pure<F> &, unsigned int ) ;
template<typename F> quat<F> pow( const pure<F> &, int ) ;
template<typename F> quat<F> pow( const pure<F> &, F ) ;
template<typename F> quat<F> pow( F, const pure<F> & ) ;

template<typename F> quat<F> sqrt( const quat<F> & ) ;
template<typename F> quat<F> sqrt( const pure<F> & ) ;

template<typename F> quat<F> operator+( const quat<F> &, const quat<F> & ) ;
template<typename F> quat<F> operator+( const quat<F> &, const pure<F> & ) ;
template<typename F> quat<F> operator+( const pure<F> &, const quat<F> & ) ;
template<typename F> pure<F> operator+( const pure<F> &, const pure<F> & ) ;

template<typename F> quat<F> operator+( const quat<F> &, F ) ;
template<typename F> quat<F> operator+( const pure<F> &, F ) ;
template<typename F> quat<F> operator+( F, const quat<F> & ) ;
template<typename F> quat<F> operator+( F, const pure<F> & ) ;

template<typename F> const quat<F> & operator+( const quat<F> & ) ;
template<typename F> const pure<F> & operator+( const pure<F> & ) ;

template<typename F> quat<F> operator-( const quat<F> &, const quat<F> & ) ;
template<typename F> quat<F> operator-( const quat<F> &, const pure<F> & ) ;
template<typename F> quat<F> operator-( const pure<F> &, const quat<F> & ) ;
template<typename F> pure<F> operator-( const pure<F> &, const pure<F> & ) ;

template<typename F> quat<F> operator-( const quat<F> &, F ) ;
template<typename F> quat<F> operator-( const pure<F> &, F ) ;
template<typename F> quat<F> operator-( F, const quat<F> & ) ;
template<typename F> quat<F> operator-( F, const pure<F> & ) ;

template<typename F> quat<F> operator-( const quat<F> & ) ;
template<typename F> pure<F> operator-( const pure<F> & ) ;

template<typename F> quat<F> operator*( const quat<F> &, const quat<F> & ) ;
template<typename F> quat<F> operator*( const quat<F> &, const pure<F> & ) ;
template<typename F> quat<F> operator*( const pure<F> &, const quat<F> & ) ;
template<typename F> quat<F> operator*( const pure<F> &, const pure<F> & ) ;

template<typename F> quat<F> operator*( const quat<F> &, F ) ;
template<typename F> pure<F> operator*( const pure<F> &, F ) ;
template<typename F> quat<F> operator*( F, const quat<F> & ) ;
template<typename F> pure<F> operator*( F, const pure<F> & ) ;

template<typename F> quat<F> operator/( const quat<F> &, F ) ;
template<typename F> pure<F> operator/( const pure<F> &, F ) ;

template<typename F> bool operator==( const quat<F> &, const quat<F> & ) ;
template<typename F> bool operator==( const quat<F> &, const pure<F> & ) ;
template<typename F> bool operator==( const pure<F> &, const quat<F> & ) ;
template<typename F> bool operator==( const pure<F> &, const pure<F> & ) ;

template<typename F> bool operator==( const quat<F> &, F ) ;
template<typename F> bool operator==( const pure<F> &, F ) ;
template<typename F> bool operator==( F, const quat<F> & ) ;
template<typename F> bool operator==( F, const pure<F> & ) ;

template<typename F> bool operator!=( const quat<F> &, const quat<F> & ) ;
template<typename F> bool operator!=( const quat<F> &, const pure<F> & ) ;
template<typename F> bool operator!=( const pure<F> &, const quat<F> & ) ;
template<typename F> bool operator!=( const pure<F> &, const pure<F> & ) ;

template<typename F> bool operator!=( const quat<F> &, F ) ;
template<typename F> bool operator!=( const pure<F> &, F ) ;
template<typename F> bool operator!=( F, const quat<F> & ) ;
template<typename F> bool operator!=( F, const pure<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & , const quat<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & , const pure<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & , quat<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & , pure<F> & ) ;

namespace scalar_func {
template< typename F > F realpart( F a )  ;
template< typename F > F purepart( F a )  ;
template< typename F > F norm( F a )  ;
template< typename F > F conj( F a )  ;
template< typename F > F inv( F a )  ;
template< typename F > F dot( F a, F b )  ;
template< typename F > F cross( F a, F b )  ;
using std::abs ;
using std::exp ;
using std::log ;
using std::cos ;
using std::sin ;
using std::cosh ;
using std::sinh ;
using std::pow ;
using std::sqrt ;
using std::atan2 ;
} // namespace scalar_func

template< typename F >
class quat
{
public:
    typedef F value_type ;

    quat() ;
    quat( F w, F x, F y, F z ) ;
    quat( F w, const pure<F> & ) ;
    explicit quat( const pure<F> & ) ;
    explicit quat( F ) ;

    F w() const ;
    F x() const ;
    F y() const ;
    F z() const ;

    void w( F ) ;
    void x( F ) ;
    void y( F ) ;
    void z( F ) ;

    quat & operator+=( const quat & ) ;
    quat & operator+=( const pure<F> & ) ;
    quat & operator+=( F ) ;

    quat & operator-=( const quat & ) ;
    quat & operator-=( const pure<F> & ) ;
    quat & operator-=( F ) ;

    quat & operator*=( const quat & ) ;
    quat & operator*=( const pure<F> & ) ;
    quat & operator*=( F ) ;

    quat & operator/=( F ) ;

    const F* data() const ;

private:
    F mx ;
    F my ;
    F mz ;
    F mw ;
} ;

template< typename F >
class pure
{
public:
    typedef F value_type ;

    pure() ;
    pure( F x, F y, F z ) ;

    F w() const ;
    F x() const ;
    F y() const ;
    F z() const ;

    void x( F ) ;
    void y( F ) ;
    void z( F ) ;

    pure & operator+=( const pure & ) ;
    pure & operator-=( const pure & ) ;
    pure & operator*=( F ) ;
    pure & operator/=( F ) ;

    const F* data() const ;

private:
    F mx ;
    F my ;
    F mz ;
} ;

///////////////////////////////////////////////////
//
// nonmember functions
//
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// realpart
///////////////////////////////////////////////////

template< typename F >
inline
F realpart( const quat<F> & a )
{
    return a.w() ;
}

template< typename F >
inline
F realpart( const pure<F> & a )
{
    return F() ;
}

///////////////////////////////////////////////////
// purepart
///////////////////////////////////////////////////

template< typename F >
inline
const pure<F> purepart( const quat<F> & a )
{
    return pure<F>(a.x(), a.y(), a.z()) ;
}

template< typename F >
inline
const pure<F> & purepart( const pure<F> & a )
{
    return a ;
}

///////////////////////////////////////////////////
// norm
///////////////////////////////////////////////////

template< typename F >
inline
F norm( const quat<F> & a )
{
    return
        a.w()*a.w() +
        a.x()*a.x() +
        a.y()*a.y() +
        a.z()*a.z() ;
}

template< typename F >
inline
F norm( const pure<F> & a )
{
    return
        a.x()*a.x() +
        a.y()*a.y() +
        a.z()*a.z() ;
}

///////////////////////////////////////////////////
// abs
///////////////////////////////////////////////////

template< typename F >
inline
F abs( const quat<F> & a )
{
    return scalar_func::sqrt(norm(a)) ;
}

template< typename F >
inline
F abs( const pure<F> & a )
{
    return scalar_func::sqrt(norm(a)) ;
}

///////////////////////////////////////////////////
// exp
///////////////////////////////////////////////////

template< typename F >
quat<F> exp( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::exp(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;
    const F exp_realpart_a = scalar_func::exp(realpart(a)) ;

    return
        quat<F>(exp_realpart_a
                *
                scalar_func::cos(abs_purepart_a),

                (
                 exp_realpart_a
                 *
                 scalar_func::sin(abs_purepart_a)
                 /
                 abs_purepart_a
                 )
                *
                purepart_a) ;
}

template< typename F >
inline
quat<F> exp( const pure<F> & a )
{
    return exp(quat<F>(a)) ;
}

///////////////////////////////////////////////////
// natural log
///////////////////////////////////////////////////

template< typename F >
quat<F> log( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::log(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;

    return
        quat<F>(scalar_func::log(abs(a)),

                (scalar_func::atan2(abs_purepart_a, realpart(a))
                 /
                 abs_purepart_a)
                *
                purepart_a) ;
}

template< typename F >
inline
quat<F> log( const pure<F> & a )
{
    return log(quat<F>(a)) ;
}

///////////////////////////////////////////////////
// trig
///////////////////////////////////////////////////

template< typename F >
quat<F> cos( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::cos(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;

    // (exp(u*a) + exp(-u*a))/2
    return quat<F>(scalar_func::cos(realpart(a))
                   *
                   scalar_func::cosh(abs_purepart_a),

                   (
                    -scalar_func::sin(realpart(a))
                    *
                    scalar_func::sinh(abs_purepart_a)
                    /
                    abs_purepart_a
                    )
                   *
                   purepart_a) ;
}

template< typename F >
quat<F> sin( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::sin(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;

    // inv(u)*(exp(u*a) - exp(-u*a))/2
    return quat<F>(scalar_func::sin(realpart(a))
                   *
                   scalar_func::cosh(abs_purepart_a),

                   (
                    scalar_func::cos(realpart(a))
                    *
                    scalar_func::sinh(abs_purepart_a)
                    /
                    abs_purepart_a
                    )
                   *
                   purepart_a) ;
}

template< typename F >
quat<F> tan( const quat<F> & a )
{
    return sin(a)*inv(cos(a)) ;
}

template< typename F >
quat<F> cosh( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::cosh(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;

    // (exp(a) + exp(-a))/2
    return quat<F>(scalar_func::cosh(realpart(a))
                   *
                   scalar_func::cos(abs_purepart_a),

                   (
                    scalar_func::sinh(realpart(a))
                    *
                    scalar_func::sin(abs_purepart_a)
                    /
                    abs_purepart_a
                    )
                   *
                   purepart_a) ;
}

template< typename F >
quat<F> sinh( const quat<F> & a )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::sinh(realpart(a))) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;

    // (exp(a) - exp(-a))/2
    return quat<F>(scalar_func::sinh(realpart(a))
                   *
                   scalar_func::cos(abs_purepart_a),

                   (
                    scalar_func::cosh(realpart(a))
                    *
                    scalar_func::sin(abs_purepart_a)
                    /
                    abs_purepart_a
                    )
                   *
                   purepart_a) ;
}

template< typename F >
quat<F> tanh( const quat<F> & a )
{
    return sinh(a)*inv(cosh(a)) ;
}

template< typename F >
inline
quat<F> cos( const pure<F> & a )
{
    return cos(quat<F>(a)) ;
}

template< typename F >
inline
quat<F> sin( const pure<F> & a )
{
    return sin(quat<F>(a)) ;
}

template< typename F >
inline
quat<F> tan( const pure<F> & a )
{
    return tan(quat<F>(a)) ;
}

template< typename F >
inline
quat<F> cosh( const pure<F> & a )
{
    return cosh(quat<F>(a)) ;
}

template< typename F >
inline
quat<F> sinh( const pure<F> & a )
{
    return sinh(quat<F>(a)) ;
}

template< typename F >
inline
quat<F> tanh( const pure<F> & a )
{
    return tanh(quat<F>(a)) ;
}

///////////////////////////////////////////////////
// pow
///////////////////////////////////////////////////

template< typename F >
quat<F> pow( const quat<F> & a, F gamma )
{
    const pure<F> purepart_a = purepart(a) ;

    if( purepart_a == pure<F>() )
    {
        return quat<F>(scalar_func::pow(realpart(a), gamma)) ;
    }

    const F abs_purepart_a = abs(purepart_a) ;
    const F theta = scalar_func::atan2(abs_purepart_a, realpart(a)) ;
    const F pow_abs_a_gamma = scalar_func::pow(abs(a), gamma) ;

    return
        quat<F>(scalar_func::cos(gamma*theta)
                *
                pow_abs_a_gamma,

                (scalar_func::sin(gamma*theta)
                 *
                 pow_abs_a_gamma
                 /
                 abs_purepart_a)
                *
                purepart_a) ;
}

template< typename F >
quat<F> pow( const quat<F> & a, unsigned int n )
{
    quat<F> b = (n % 2) ? a : quat<F>(F(1)) ;
    quat<F> c = a ;

    while( n >>= 1 )
    {
        c = c*c ;
        if( n % 2 == 1 )
        {
            b = c*b ;
        }
    }

    return b ;
}

template< typename F >
inline
quat<F> pow( const quat<F> & a, int n )
{
    typedef unsigned int uint ;

    return n >= 0 ? pow(a, uint(n)) : inv(pow(a, uint(-n))) ;
}

template< typename F >
inline
quat<F> pow( F gamma, const quat<F> & a )
{
    return gamma == F() ? quat<F>(F()) : exp(scalar_func::log(gamma)*a) ;
}

template< typename F >
inline
quat<F> pow( const pure<F> & a, F r )
{
    return pow(quat<F>(a), r) ;
}

template< typename F >
quat<F> pow( const pure<F> & a, unsigned int n )
{
    switch( n % 4 )
    {
    case 0:
        return quat<F>(scalar_func::pow(norm(a), int(n/2))) ;
    case 1:
        return quat<F>(a*scalar_func::pow(norm(a), int(n/2))) ;
    case 2:
        return quat<F>(-scalar_func::pow(norm(a), int(n/2))) ;
    case 3:
        return quat<F>(a*(-scalar_func::pow(norm(a), int(n/2)))) ;
    }

    return quat<F>() ;
}

template< typename F >
quat<F> pow( const pure<F> & a, int n )
{
    typedef unsigned int uint ;

    if( n >= 0 )
    {
        return pow(a, uint(n)) ;
    }

    switch( (-n) % 4 )
    {
    case 0:
        return quat<F>(scalar_func::pow(norm(a), int(n/2))) ;
    case 1:
        return quat<F>(a*(-scalar_func::pow(norm(a), int(n/2) - 1))) ;
    case 2:
        return quat<F>(-scalar_func::pow(norm(a), int(n/2))) ;
    case 3:
        return quat<F>(a*(scalar_func::pow(norm(a), int(n/2) - 1))) ;
    }

    return quat<F>() ;
}

template< typename F >
inline
quat<F> pow( F gamma, const pure<F> & a )
{
    return pow(gamma, quat<F>(a)) ;
}

///////////////////////////////////////////////////
// sqrt
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> sqrt( const quat<F> & a )
{
    return pow(a, F(0.5)) ;
}

template< typename F >
inline
quat<F> sqrt( const pure<F> & a )
{
    return pow(quat<F>(a), F(0.5)) ;
}

///////////////////////////////////////////////////
// conj
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> conj( const quat<F> & a )
{
    return quat<F>( a.w(),
                   -a.x(),
                   -a.y(),
                   -a.z()) ;
}

template< typename F >
inline
pure<F> conj( const pure<F> & a )
{
    return pure<F>(-a.x(),
                   -a.y(),
                   -a.z()) ;
}

///////////////////////////////////////////////////
// inv
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> inv( const quat<F> & a )
{
    const F neg_norm_a =
        -(a.w()*a.w() +
          a.x()*a.x() +
          a.y()*a.y() +
          a.z()*a.z()) ;

    return quat<F>(-a.w()/neg_norm_a,
                    a.x()/neg_norm_a,
                    a.y()/neg_norm_a,
                    a.z()/neg_norm_a) ;
}

template< typename F >
inline
pure<F> inv( const pure<F> & a )
{
    const F neg_norm_a =
        -(a.x()*a.x() +
          a.y()*a.y() +
          a.z()*a.z()) ;

    return pure<F>(a.x()/neg_norm_a,
                   a.y()/neg_norm_a,
                   a.z()/neg_norm_a) ;
}

///////////////////////////////////////////////////
// dot
///////////////////////////////////////////////////

template< typename F >
inline
F dot( const quat<F> & a, const quat<F> & b )
{
    return
        a.w()*b.w() +
        a.x()*b.x() +
        a.y()*b.y() +
        a.z()*b.z() ;
}

template< typename F >
inline
F dot( const pure<F> & a, const quat<F> & b )
{
    return
        a.x()*b.x() +
        a.y()*b.y() +
        a.z()*b.z() ;
}

template< typename F >
inline
F dot( const quat<F> & a, const pure<F> & b )
{
    return
        a.x()*b.x() +
        a.y()*b.y() +
        a.z()*b.z() ;
}

template< typename F >
inline
F dot( const pure<F> & a, const pure<F> & b )
{
    return
        a.x()*b.x() +
        a.y()*b.y() +
        a.z()*b.z() ;
}

template< typename F >
inline
F dot( F a, const quat<F> & b )
{
    return a*b.w() ;
}

template< typename F >
inline
F dot( const quat<F> & a, F b )
{
    return a.w()*b ;
}

template< typename F >
inline
F dot( F, const pure<F> & )
{
    return F() ;
}

template< typename F >
inline
F dot( const pure<F> &, F )
{
    return F() ;
}

///////////////////////////////////////////////////
// cross
///////////////////////////////////////////////////

template< typename F >
inline
pure<F> cross( const quat<F> & a, const quat<F> & b )
{
    return pure<F>(a.w()*b.x() - a.x()*b.w() + a.y()*b.z() - a.z()*b.y(),
                   a.w()*b.y() - a.y()*b.w() + a.z()*b.x() - a.x()*b.z(),
                   a.w()*b.z() - a.z()*b.w() + a.x()*b.y() - a.y()*b.x()) ;
}

template< typename F >
inline
pure<F> cross( const quat<F> & a, const pure<F> & b )
{
    return pure<F>(a.w()*b.x() + a.y()*b.z() - a.z()*b.y(),
                   a.w()*b.y() + a.z()*b.x() - a.x()*b.z(),
                   a.w()*b.z() + a.x()*b.y() - a.y()*b.x()) ;
}

template< typename F >
inline
pure<F> cross( const pure<F> & a, const quat<F> & b )
{
    return pure<F>(a.y()*b.z() - a.x()*b.w() - a.z()*b.y(),
                   a.z()*b.x() - a.y()*b.w() - a.x()*b.z(),
                   a.x()*b.y() - a.z()*b.w() - a.y()*b.x()) ;
}

template< typename F >
inline
pure<F> cross( const pure<F> & a, const pure<F> & b )
{
    return pure<F>(a.y()*b.z() - a.z()*b.y(),
                   a.z()*b.x() - a.x()*b.z(),
                   a.x()*b.y() - a.y()*b.x()) ;
}

template< typename F >
inline
pure<F> cross( F a, const quat<F> & b )
{
    return pure<F>(a*b.x(),
                   a*b.y(),
                   a*b.z()) ;
}

template< typename F >
inline
pure<F> cross( const quat<F> & a, F b )
{
    return pure<F>(-a.x()*b,
                   -a.y()*b,
                   -a.z()*b) ;
}

template< typename F >
inline
pure<F> cross( F a, const pure<F> & b )
{
    return pure<F>(a*b.x(),
                   a*b.y(),
                   a*b.z()) ;
}

template< typename F >
inline
pure<F> cross( const pure<F> & a, F b )
{
    return pure<F>(-a*b.x(),
                   -a*b.y(),
                   -a*b.z()) ;
}

///////////////////////////////////////////////////
// operator==
///////////////////////////////////////////////////

template< typename F >
inline
bool operator==( const quat<F> & a, const quat<F> & b )
{
    return
        a.w() == b.w() &&
        a.x() == b.x() &&
        a.y() == b.y() &&
        a.z() == b.z() ;
}

template< typename F >
inline
bool operator==( const quat<F> & a, const pure<F> & b )
{
    return
        a.w() == F() &&
        a.x() == b.x() &&
        a.y() == b.y() &&
        a.z() == b.z() ;
}

template< typename F >
inline
bool operator==( const pure<F> & a, const quat<F> & b )
{
    return
        F()   == b.w() &&
        a.x() == b.x() &&
        a.y() == b.y() &&
        a.z() == b.z() ;
}

template< typename F >
inline
bool operator==( const pure<F> & a, const pure<F> & b )
{
    return
        a.x() == b.x() &&
        a.y() == b.y() &&
        a.z() == b.z() ;
}

template< typename F >
inline
bool operator==( F a, const quat<F> & b )
{
    return
        a   == b.w() &&
        F() == b.x() &&
        F() == b.y() &&
        F() == b.z() ;
}

template< typename F >
inline
bool operator==( F a, const pure<F> & b )
{
    return
        a   == F() &&
        F() == b.x() &&
        F() == b.y() &&
        F() == b.z() ;
}

template< typename F >
inline
bool operator==( const quat<F> & a, F b )
{
    return
        a.w() == b &&
        a.x() == F() &&
        a.y() == F() &&
        a.z() == F() ;
}

template< typename F >
inline
bool operator==( const pure<F> & a, F b )
{
    return
        F()   == b &&
        a.x() == F() &&
        a.y() == F() &&
        a.z() == F() ;
}

///////////////////////////////////////////////////
// operator!=
///////////////////////////////////////////////////

template< typename F >
inline
bool operator!=( const quat<F> & a, const quat<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const quat<F> & a, const pure<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const pure<F> & a, const quat<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const pure<F> & a, const pure<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const quat<F> & a, F b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const pure<F> & a, F b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( F a, const quat<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( F a, const pure<F> & b )
{
    return !(a == b) ;
}

///////////////////////////////////////////////////
// operator+
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> operator+( const quat<F> & a, const quat<F> & b )
{
    return quat<F>(a.w() + b.w(),
                   a.x() + b.x(),
                   a.y() + b.y(),
                   a.z() + b.z()) ;
}

template< typename F >
inline
quat<F> operator+( const quat<F> & a, const pure<F> & b )
{
    return quat<F>(a.w(),
                   a.x() + b.x(),
                   a.y() + b.y(),
                   a.z() + b.z()) ;
}

template< typename F >
inline
quat<F> operator+( const pure<F> & a, const quat<F> & b )
{
    return quat<F>(        b.w(),
                   a.x() + b.x(),
                   a.y() + b.y(),
                   a.z() + b.z()) ;
}

template< typename F >
inline
pure<F> operator+( const pure<F> & a, const pure<F> & b )
{
    return pure<F>(a.x() + b.x(),
                   a.y() + b.y(),
                   a.z() + b.z()) ;
}

template< typename F >
inline
quat<F> operator+( F a, const quat<F> & b )
{
    return quat<F>(a + b.w(),
                       b.x(),
                       b.y(),
                       b.z()) ;
}

template< typename F >
inline
quat<F> operator+( F a, const pure<F> & b )
{
    return quat<F>(a,
                       b.x(),
                       b.y(),
                       b.z()) ;
}

template< typename F >
inline
quat<F> operator+( const quat<F> & a, F b )
{
    return quat<F>(a.w() + b,
                   a.x(),
                   a.y(),
                   a.z()) ;
}

template< typename F >
inline
quat<F> operator+( const pure<F> & a, F b )
{
    return quat<F>(b,
                   a.x(),
                   a.y(),
                   a.z()) ;
}

template< typename F >
inline
const quat<F> & operator+( const quat<F> & a )
{
    return a ;
}

template< typename F >
inline
const pure<F> & operator+( const pure<F> & a )
{
    return a ;
}

///////////////////////////////////////////////////
// operator-
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> operator-( const quat<F> & a, const quat<F> & b )
{
    return quat<F>(a.w() - b.w(),
                   a.x() - b.x(),
                   a.y() - b.y(),
                   a.z() - b.z()) ;
}

template< typename F >
inline
quat<F> operator-( const quat<F> & a, const pure<F> & b )
{
    return quat<F>(a.w(),
                   a.x() - b.x(),
                   a.y() - b.y(),
                   a.z() - b.z()) ;
}

template< typename F >
inline
quat<F> operator-( const pure<F> & a, const quat<F> & b )
{
    return quat<F>(      - b.w(),
                   a.x() - b.x(),
                   a.y() - b.y(),
                   a.z() - b.z()) ;
}

template< typename F >
inline
pure<F> operator-( const pure<F> & a, const pure<F> & b )
{
    return pure<F>(a.x() - b.x(),
                   a.y() - b.y(),
                   a.z() - b.z()) ;
}

template< typename F >
inline
quat<F> operator-( F a, const quat<F> & b )
{
    return quat<F>(a - b.w(),
                     - b.x(),
                     - b.y(),
                     - b.z()) ;
}

template< typename F >
inline
quat<F> operator-( F a, const pure<F> & b )
{
    return quat<F>(a,
                     - b.x(),
                     - b.y(),
                     - b.z()) ;
}

template< typename F >
inline
quat<F> operator-( const quat<F> & a, F b )
{
    return quat<F>(a.w() - b,
                   a.x(),
                   a.y(),
                   a.z()) ;
}

template< typename F >
inline
quat<F> operator-( const pure<F> & a, F b )
{
    return quat<F>(-b,
                   a.x(),
                   a.y(),
                   a.z()) ;
}

template< typename F >
inline
quat<F> operator-( const quat<F> & a )
{
    return quat<F>(-a.w(),
                   -a.x(),
                   -a.y(),
                   -a.z()) ;
}

template< typename F >
inline
pure<F> operator-( const pure<F> & a )
{
    return pure<F>(-a.x(),
                   -a.y(),
                   -a.z()) ;
}

///////////////////////////////////////////////////
// operator*
///////////////////////////////////////////////////

#if !defined(QUAT_CONSERVE_MULTIPLIES)
template< typename F >
inline
quat<F> operator*( const quat<F> & a, const quat<F> & b )
{
    return quat<F>(a.w()*b.w() - a.x()*b.x() - a.y()*b.y() - a.z()*b.z(),
                   a.w()*b.x() + a.x()*b.w() + a.y()*b.z() - a.z()*b.y(),
                   a.w()*b.y() - a.x()*b.z() + a.y()*b.w() + a.z()*b.x(),
                   a.w()*b.z() + a.x()*b.y() - a.y()*b.x() + a.z()*b.w()) ;
}
#endif

#if defined(QUAT_CONSERVE_MULTIPLIES)
template< typename F >
quat<F> operator*( const quat<F> & a, const quat<F> & b )
{
    const F a1 =  (a.z() - a.y())*(b.y() - b.z()) ;
    const F a2 =  (a.w() + a.x())*(b.w() + b.x()) ;
    const F a3 =  (a.w() - a.x())*(b.y() + b.z()) ;
    const F a4 =  (a.y() + a.z())*(b.w() - b.x()) ;

    const F b1 =  (a.z() - a.x())*(b.x() - b.y()) ;
    const F b2 = -(a.x() + a.z())*(b.x() + b.y()) ;
    const F b3 =  (a.w() + a.y())*(b.w() - b.z()) ;
    const F b4 =  (a.w() - a.y())*(b.w() + b.z()) ;

    return quat<F>(a1 + F(0.5)*(b1 + b2 + b3 + b4),
                   a2 + F(0.5)*(b1 + b2 - b3 - b4),
                   a3 + F(0.5)*(b1 - b2 + b3 - b4),
                   a4 + F(0.5)*(b1 - b2 - b3 + b4)) ;
}
#endif

template< typename F >
inline
quat<F> operator*( const quat<F> & a, const pure<F> & b )
{
    return quat<F>(- a.x()*b.x() - a.y()*b.y() - a.z()*b.z(),
                     a.w()*b.x() + a.y()*b.z() - a.z()*b.y(),
                     a.w()*b.y() - a.x()*b.z() + a.z()*b.x(),
                     a.w()*b.z() + a.x()*b.y() - a.y()*b.x()) ;
}

template< typename F >
inline
quat<F> operator*( const pure<F> & a, const quat<F> & b )
{
    return quat<F>(- a.x()*b.x() - a.y()*b.y() - a.z()*b.z(),
                     a.x()*b.w() + a.y()*b.z() - a.z()*b.y(),
                     a.y()*b.w() + a.z()*b.x() - a.x()*b.z(),
                     a.x()*b.y() - a.y()*b.x() + a.z()*b.w()) ;
}

template< typename F >
inline
quat<F> operator*( const pure<F> & a, const pure<F> & b )
{
    return quat<F>(- a.x()*b.x() - a.y()*b.y() - a.z()*b.z(),
                     a.y()*b.z() - a.z()*b.y(),
                     a.z()*b.x() - a.x()*b.z(),
                     a.x()*b.y() - a.y()*b.x()) ;
}

template< typename F >
inline
quat<F> operator*( F a, const quat<F> & b )
{
    return quat<F>(a*b.w(),
                   a*b.x(),
                   a*b.y(),
                   a*b.z()) ;
}

template< typename F >
inline
pure<F> operator*( F a, const pure<F> & b )
{
    return pure<F>(a*b.x(),
                   a*b.y(),
                   a*b.z()) ;
}

template< typename F >
inline
quat<F> operator*( const quat<F> & a, F b )
{
    return quat<F>(a.w()*b,
                   a.x()*b,
                   a.y()*b,
                   a.z()*b) ;
}

template< typename F >
inline
pure<F> operator*( const pure<F> & a, F b )
{
    return pure<F>(a.x()*b,
                   a.y()*b,
                   a.z()*b) ;
}

///////////////////////////////////////////////////
// operator/
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> operator/( const quat<F> & a, F b )
{
    return quat<F>(a.w()/b,
                   a.x()/b,
                   a.y()/b,
                   a.z()/b) ;
}

template< typename F >
inline
pure<F> operator/( const pure<F> & a, F b )
{
    return pure<F>(a.x()/b,
                   a.y()/b,
                   a.z()/b) ;
}

///////////////////////////////////////////////////
//
// quat member functions
//
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// constructors
///////////////////////////////////////////////////

template< typename F >
inline
quat<F>::
quat()
    : mx(F()),
      my(F()),
      mz(F()),
      mw(F())
{
}

template< typename F >
inline
quat<F>::
quat( F w, F x, F y, F z )
    : mx(x),
      my(y),
      mz(z),
      mw(w)
{
}

template< typename F >
inline
quat<F>::
quat( F w, const pure<F> & a )
    : mx(a.x()),
      my(a.y()),
      mz(a.z()),
      mw(w)
{
}

template< typename F >
inline
quat<F>::
quat( const pure<F> & a )
    : mx(a.x()),
      my(a.y()),
      mz(a.z()),
      mw(F())
{
}

template< typename F >
inline
quat<F>::
quat( F w )
    : mx(F()),
      my(F()),
      mz(F()),
      mw(w)
{
}

///////////////////////////////////////////////////
// readers
///////////////////////////////////////////////////

template< typename F >
inline
F
quat<F>::
w() const
{
    return mw ;
}

template< typename F >
inline
F
quat<F>::
x() const
{
    return mx ;
}

template< typename F >
inline
F
quat<F>::
y() const
{
    return my ;
}

template< typename F >
inline
F
quat<F>::
z() const
{
    return mz ;
}

///////////////////////////////////////////////////
// writers
///////////////////////////////////////////////////

template< typename F >
inline
void
quat<F>::
w( F a )
{
    mw = a ;
}

template< typename F >
inline
void
quat<F>::
x( F a )
{
    mx = a ;
}

template< typename F >
inline
void
quat<F>::
y( F a )
{
    my = a ;
}

template< typename F >
inline
void
quat<F>::
z( F a )
{
    mz = a ;
}

///////////////////////////////////////////////////
// operator+=
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> &
quat<F>::
operator+=( const quat & a )
{
    mw += a.w() ;
    mx += a.x() ;
    my += a.y() ;
    mz += a.z() ;
    return *this ;
}

template< typename F >
inline
quat<F> &
quat<F>::
operator+=( const pure<F> & a )
{
    mx += a.x() ;
    my += a.y() ;
    mz += a.z() ;
    return *this ;
}

template< typename F >
inline
quat<F> &
quat<F>::
operator+=( F a )
{
    mw += a ;
    return *this ;
}

///////////////////////////////////////////////////
// operator-=
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> &
quat<F>::
operator-=( const quat & a )
{
    mw -= a.w() ;
    mx -= a.x() ;
    my -= a.y() ;
    mz -= a.z() ;
    return *this ;
}

template< typename F >
inline
quat<F> &
quat<F>::
operator-=( const pure<F> & a )
{
    mx -= a.x() ;
    my -= a.y() ;
    mz -= a.z() ;
    return *this ;
}

template< typename F >
inline
quat<F> &
quat<F>::
operator-=( F a )
{
    mw -= a ;
    return *this ;
}

///////////////////////////////////////////////////
// operator*=
///////////////////////////////////////////////////

#if !defined(QUAT_CONSERVE_MULTIPLIES)
template< typename F >
inline
quat<F> &
quat<F>::
operator*=( const quat & b )
{
    const quat a = *this ;
    mw = a.w()*b.w() - a.x()*b.x() - a.y()*b.y() - a.z()*b.z() ;
    mx = a.w()*b.x() + a.x()*b.w() + a.y()*b.z() - a.z()*b.y() ;
    my = a.w()*b.y() - a.x()*b.z() + a.y()*b.w() + a.z()*b.x() ;
    mz = a.w()*b.z() + a.x()*b.y() - a.y()*b.x() + a.z()*b.w() ;
    return *this ;
}
#endif

#if defined(QUAT_CONSERVE_MULTIPLIES)
template< typename F >
quat<F> &
quat<F>::
operator*=( const quat & b )
{
    const quat a = *this ;

    const F a1 =  (a.z() - a.y())*(b.y() - b.z()) ;
    const F a2 =  (a.w() + a.x())*(b.w() + b.x()) ;
    const F a3 =  (a.w() - a.x())*(b.y() + b.z()) ;
    const F a4 =  (a.y() + a.z())*(b.w() - b.x()) ;

    const F b1 =  (a.z() - a.x())*(b.x() - b.y()) ;
    const F b2 = -(a.x() + a.z())*(b.x() + b.y()) ;
    const F b3 =  (a.w() + a.y())*(b.w() - b.z()) ;
    const F b4 =  (a.w() - a.y())*(b.w() + b.z()) ;

    mw = a1 + F(0.5)*(b1 + b2 + b3 + b4) ;
    mx = a2 + F(0.5)*(b1 + b2 - b3 - b4) ;
    my = a3 + F(0.5)*(b1 - b2 + b3 - b4) ;
    mz = a4 + F(0.5)*(b1 - b2 - b3 + b4) ;

    return *this ;
}
#endif

template< typename F >
inline
quat<F> &
quat<F>::
operator*=( const pure<F> & b )
{
    const quat a = *this ;
    mw = - a.x()*b.x() - a.y()*b.y() - a.z()*b.z() ;
    mx =   a.w()*b.x() + a.y()*b.z() - a.z()*b.y() ;
    my =   a.w()*b.y() - a.x()*b.z() + a.z()*b.x() ;
    mz =   a.w()*b.z() + a.x()*b.y() - a.y()*b.x() ;
    return *this ;
}

template< typename F >
inline
quat<F> &
quat<F>::
operator*=( F a )
{
    mw *= a ;
    mx *= a ;
    my *= a ;
    mz *= a ;
    return *this ;
}

///////////////////////////////////////////////////
// operator/=
///////////////////////////////////////////////////

template< typename F >
inline
quat<F> &
quat<F>::
operator/=( F a )
{
    mw /= a ;
    mx /= a ;
    my /= a ;
    mz /= a ;
    return *this ;
}

///////////////////////////////////////////////////
// data
///////////////////////////////////////////////////

template< typename F >
inline
const F*
quat<F>::
data() const
{
    return &mx ;
}

///////////////////////////////////////////////////
//
// pure member functions
//
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// constructors
///////////////////////////////////////////////////

template< typename F >
inline
pure<F>::
pure()
    : mx(F()),
      my(F()),
      mz(F())
{
}

template< typename F >
inline
pure<F>::
pure( F x, F y, F z )
    : mx(x),
      my(y),
      mz(z)
{
}

///////////////////////////////////////////////////
// readers
///////////////////////////////////////////////////

template< typename F >
inline
F
pure<F>::
w() const
{
    return F() ;
}

template< typename F >
inline
F
pure<F>::
x() const
{
    return mx ;
}

template< typename F >
inline
F
pure<F>::
y() const
{
    return my ;
}

template< typename F >
inline
F
pure<F>::
z() const
{
    return mz ;
}

///////////////////////////////////////////////////
// writers
///////////////////////////////////////////////////

template< typename F >
inline
void
pure<F>::
x( F a )
{
    mx = a ;
}

template< typename F >
inline
void
pure<F>::
y( F a )
{
    my = a ;
}

template< typename F >
inline
void
pure<F>::
z( F a )
{
    mz = a ;
}

///////////////////////////////////////////////////
// operators
///////////////////////////////////////////////////

template< typename F >
inline
pure<F> &
pure<F>::
operator+=( const pure & a )
{
    mx += a.x() ;
    my += a.y() ;
    mz += a.z() ;
    return *this ;
}

template< typename F >
inline
pure<F> &
pure<F>::
operator-=( const pure & a )
{
    mx -= a.x() ;
    my -= a.y() ;
    mz -= a.z() ;
    return *this ;
}

template< typename F >
inline
pure<F> &
pure<F>::
operator*=( F a )
{
    mx *= a ;
    my *= a ;
    mz *= a ;
    return *this ;
}

template< typename F >
inline
pure<F> &
pure<F>::
operator/=( F a )
{
    mx /= a ;
    my /= a ;
    mz /= a ;
    return *this ;
}

///////////////////////////////////////////////////
// data
///////////////////////////////////////////////////

template< typename F >
inline
const F*
pure<F>::
data() const
{
    return &mx ;
}

///////////////////////////////////////////////////
// streams
///////////////////////////////////////////////////

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & out, const quat<F> & a )
{
    out << '('
        << a.w()
        << ','
        << a.x()
        << ','
        << a.y()
        << ','
        << a.z()
        << ')' ;

    return out ;
}

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & out, const pure<F> & a )
{
    out << '('
        << a.x()
        << ','
        << a.y()
        << ','
        << a.z()
        << ')' ;

    return out ;
}

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & in, quat<F> & a )
{
    T_Char ch ;
    F w ;
    F x ;
    F y ;
    F z ;

    ch = 0 ;
    in >> ch ;
    if( ch != '(' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> w >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> x >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> y >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> z >> ch ;
    if( ch != ')' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    a.w(w) ;
    a.x(x) ;
    a.y(y) ;
    a.z(z) ;

    return in ;
}

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & in, pure<F> & a )
{
    T_Char ch ;
    F x ;
    F y ;
    F z ;

    ch = 0 ;
    in >> ch ;
    if( ch != '(' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> x >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> y >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> z >> ch ;
    if( ch != ')' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    a.x(x) ;
    a.y(y) ;
    a.z(z) ;

    return in ;
}

///////////////////////////////////////////////////////////////////////
//
// scalar_func
//
// A new scalar may be introduced by adding the appropriate functions
// to scalar_func (sin, cos, exp, etc.).
//
// The separate namespace also provides the convenience of a 'using'
// directive which pulls in only these functions which do not have a
// class signature.
//
///////////////////////////////////////////////////////////////////////

namespace scalar_func {

template< typename F >
inline
F realpart( F a )
{
    return a ;
}

template< typename F >
inline
F purepart( F a )
{
    return F() ;
}

template< typename F >
inline
F norm( F a )
{
    return a*a ;
}

template< typename F >
inline
F conj( F a )
{
    return a ;
}

template< typename F >
inline
F inv( F a )
{
    return F(1)/a ;
}

template< typename F >
inline
F dot( F a, F b )
{
    return a*b ;
}

template< typename F >
inline
F cross( F a, F b )
{
    return F() ;
}

} // namespace scalar_func

} // namespace quat_namespace

using quat_namespace::quat ;
using quat_namespace::pure ;

}} // namespace esve::math

#endif

