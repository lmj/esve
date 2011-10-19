//
// complex numbers.
//
// The reason esve has its own complex class is because it came "for
// free" as a cut-and-paste (with regexp substitutions) from
// quaternions.  This provided a further verification of the quat
// class.
//
// Another reason is that esve::math::complex guarantees
// representation for OpenGL, on the hardly-fathomable chance that a
// machine's std::complex uses polar representation or something.
//
// Yet another reason is that it disallows conversions, which I have
// spurned ever since I crippled an inner loop by accidentally using a
// float-constructible class when a regular float would have sufficed.
//

#ifndef esve_math_complex_hxx
#define esve_math_complex_hxx

#if defined(USE_STD_COMPLEX)

#include <complex>

namespace esve { namespace math {
namespace complex_namespace { using std::complex ; }
using complex_namespace::complex ;
}} // namespace esve::math

#elif !defined(USE_STD_COMPLEX)

#include <istream>
#include <ostream>
#include <cmath>

namespace esve { namespace math {

namespace complex_namespace {

template<typename F> class complex ;

template<typename F> F real( const complex<F> & ) ;
template<typename F> F imag( const complex<F> & ) ;
template<typename F> F norm( const complex<F> & ) ;
template<typename F> F abs( const complex<F> & ) ;

template<typename F> F arg( const complex<F> & ) ;
template<typename F> complex<F> polar( F r, F theta ) ;

template<typename F> complex<F> conj( const complex<F> & ) ;
template<typename F> complex<F> inv( const complex<F> & ) ;

template<typename F> F dot( const complex<F> &, const complex<F> & ) ;
template<typename F> F dot( const complex<F> &, F ) ;
template<typename F> F dot( F, const complex<F> & ) ;

template<typename F> complex<F> exp( const complex<F> & ) ;
template<typename F> complex<F> log( const complex<F> & ) ;

template<typename F> complex<F> cos( const complex<F> & ) ;
template<typename F> complex<F> sin( const complex<F> & ) ;
template<typename F> complex<F> tan( const complex<F> & ) ;
template<typename F> complex<F> cosh( const complex<F> & ) ;
template<typename F> complex<F> sinh( const complex<F> & ) ;
template<typename F> complex<F> tanh( const complex<F> & ) ;

template<typename F> complex<F> pow( const complex<F> &, const complex<F> & ) ;
template<typename F> complex<F> pow( const complex<F> &, unsigned int ) ;
template<typename F> complex<F> pow( const complex<F> &, int ) ;
template<typename F> complex<F> pow( const complex<F> &, F ) ;
template<typename F> complex<F> pow( F, const complex<F> & ) ;

template<typename F> complex<F> sqrt( const complex<F> & ) ;

template<typename F> complex<F> operator+( const complex<F> &,
                                           const complex<F> & ) ;
template<typename F> complex<F> operator+( const complex<F> &, F ) ;
template<typename F> complex<F> operator+( F, const complex<F> & ) ;

template<typename F> const complex<F> & operator+( const complex<F> & ) ;

template<typename F> complex<F> operator-( const complex<F> &,
                                           const complex<F> & ) ;
template<typename F> complex<F> operator-( const complex<F> &, F ) ;
template<typename F> complex<F> operator-( F, const complex<F> & ) ;

template<typename F> complex<F> operator-( const complex<F> & ) ;

template<typename F> complex<F> operator*( const complex<F> &,
                                           const complex<F> & ) ;
template<typename F> complex<F> operator*( const complex<F> &, F ) ;
template<typename F> complex<F> operator*( F, const complex<F> & ) ;

template<typename F> complex<F> operator/( const complex<F> &,
                                           const complex<F> & ) ;
template<typename F> complex<F> operator/( F, const complex<F> & ) ;
template<typename F> complex<F> operator/( const complex<F> &, F ) ;

template<typename F> bool operator==( const complex<F> &,
                                      const complex<F> & ) ;
template<typename F> bool operator==( const complex<F> &, F ) ;
template<typename F> bool operator==( F, const complex<F> & ) ;

template<typename F> bool operator!=( const complex<F> &,
                                      const complex<F> & ) ;
template<typename F> bool operator!=( const complex<F> &, F ) ;
template<typename F> bool operator!=( F, const complex<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & , const complex<F> & ) ;

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & , complex<F> & ) ;

namespace scalar_func {
template< typename F > F real( F a )  ;
template< typename F > F imag( F a )  ;
template< typename F > F norm( F a )  ;
template< typename F > F conj( F a )  ;
template< typename F > F inv( F a )  ;
template< typename F > F dot( F a, F b )  ;
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
class complex
{
public:
    typedef F value_type ;

    complex() ;
    complex( F , F ) ;
    explicit complex( F ) ;

    F real() const ;
    F imag() const ;

    complex & operator+=( const complex & ) ;
    complex & operator+=( F ) ;

    complex & operator-=( const complex & ) ;
    complex & operator-=( F ) ;

    complex & operator*=( const complex & ) ;
    complex & operator*=( F ) ;

    complex & operator/=( F ) ;
    complex & operator/=( const complex & ) ;

    const F* data() const ;

private:
    F mw ;
    F mx ;
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
F real( const complex<F> & a )
{
    return a.real() ;
}

///////////////////////////////////////////////////
// imag
///////////////////////////////////////////////////

template< typename F >
inline
F imag( const complex<F> & a )
{
    return a.imag() ;
}

///////////////////////////////////////////////////
// norm
///////////////////////////////////////////////////

template< typename F >
inline
F norm( const complex<F> & a )
{
    return
        a.real()*a.real() +
        a.imag()*a.imag() ;
}

///////////////////////////////////////////////////
// abs
///////////////////////////////////////////////////

template< typename F >
inline
F abs( const complex<F> & a )
{
    return scalar_func::sqrt(norm(a)) ;
}

///////////////////////////////////////////////////
// exp
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> exp( const complex<F> & a )
{
    const F exp_realpart_a = scalar_func::exp(a.real()) ;

    return complex<F>(exp_realpart_a*scalar_func::cos(a.imag()),
                      exp_realpart_a*scalar_func::sin(a.imag())) ;
}

///////////////////////////////////////////////////
// natural log
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> log( const complex<F> & a )
{
    return complex<F>(scalar_func::log(abs(a)),
                      scalar_func::atan2(a.imag(), a.real())) ;
}

///////////////////////////////////////////////////
// arg
///////////////////////////////////////////////////

template< typename F >
inline
F arg( const complex<F> & a )
{
    return scalar_func::atan2(a.imag(), a.real()) ;
}

///////////////////////////////////////////////////
// polar
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> polar( F r, F theta )
{
    return complex<F>(r*scalar_func::cos(theta),
                      r*scalar_func::sin(theta)) ;
}

///////////////////////////////////////////////////
// trig
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> cos( const complex<F> & a )
{
    return complex<F>(scalar_func::cos(a.real())
                      *
                      scalar_func::cosh(a.imag()),

                      -scalar_func::sin(a.real())
                      *
                      scalar_func::sinh(a.imag())) ;
}

template< typename F >
inline
complex<F> sin( const complex<F> & a )
{
    return complex<F>(scalar_func::sin(a.real())
                      *
                      scalar_func::cosh(a.imag()),

                      scalar_func::cos(a.real())
                      *
                      scalar_func::sinh(a.imag())) ;
}

template< typename F >
inline
complex<F> tan( const complex<F> & a )
{
    return sin(a)/cos(a) ;
}

template< typename F >
inline
complex<F> cosh( const complex<F> & a )
{
    return complex<F>(scalar_func::cosh(a.real())
                      *
                      scalar_func::cos(a.imag()),

                      scalar_func::sinh(a.real())
                      *
                      scalar_func::sin(a.imag())) ;
}

template< typename F >
inline
complex<F> sinh( const complex<F> & a )
{
    return complex<F>(scalar_func::sinh(a.real())
                      *
                      scalar_func::cos(a.imag()),

                      scalar_func::cosh(a.real())
                      *
                      scalar_func::sin(a.imag())) ;
}

template< typename F >
inline
complex<F> tanh( const complex<F> & a )
{
    return sinh(a)/cosh(a) ;
}

///////////////////////////////////////////////////
// pow
///////////////////////////////////////////////////

template< typename F >
complex<F> pow( const complex<F> & a, F gamma )
{
    if( a.imag() == F() )
    {
        return complex<F>(scalar_func::pow(a.real(), gamma)) ;
    }

    const complex<F> log_a = log(a) ;
    const F r = scalar_func::exp(gamma*log_a.real()) ;
    const F theta = gamma*log_a.imag() ;

    return complex<F>(r*scalar_func::cos(theta),
                      r*scalar_func::sin(theta)) ;
}

template< typename F >
complex<F> pow( const complex<F> & a, unsigned int n )
{
    complex<F> b = (n % 2) ? a : complex<F>(F(1)) ;
    complex<F> c = a ;

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
complex<F> pow( const complex<F> & a, int n )
{
    typedef unsigned int uint ;

    return n >= 0 ? pow(a, uint(n)) : inv(pow(a, uint(-n))) ;
}

template< typename F >
inline
complex<F> pow( F gamma, const complex<F> & a )
{
    return gamma == F() ? complex<F>(F()) : exp(scalar_func::log(gamma)*a) ;
}

template< typename F >
inline
complex<F> pow( const complex<F> & a, const complex<F> & b )
{
    return a == F() ? F() : exp(b*log(a)) ;
}

///////////////////////////////////////////////////
// sqrt
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> sqrt( const complex<F> & a )
{
    return pow(a, F(0.5)) ;
}

///////////////////////////////////////////////////
// conj
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> conj( const complex<F> & a )
{
    return complex<F>(a.real(),
                      -a.imag()) ;
}

///////////////////////////////////////////////////
// inv
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> inv( const complex<F> & a )
{
    const F norm_a = norm(a) ;

    return complex<F>(a.real()/norm_a,
                      -a.imag()/norm_a) ;
}

///////////////////////////////////////////////////
// dot
///////////////////////////////////////////////////

template< typename F >
inline
F dot( const complex<F> & a, const complex<F> & b )
{
    return
        a.real()*b.real() +
        a.imag()*b.imag() ;
}

template< typename F >
inline
F dot( F a, const complex<F> & b )
{
    return a*b.real() ;
}

template< typename F >
inline
F dot( const complex<F> & a, F b )
{
    return a.real()*b ;
}

///////////////////////////////////////////////////
// operator==
///////////////////////////////////////////////////

template< typename F >
inline
bool operator==( const complex<F> & a, const complex<F> & b )
{
    return
        a.real() == b.real() &&
        a.imag() == b.imag() ;
}

template< typename F >
inline
bool operator==( F a, const complex<F> & b )
{
    return
        a   == b.real() &&
        F() == b.imag() ;
}

template< typename F >
inline
bool operator==( const complex<F> & a, F b )
{
    return
        a.real() == b &&
        a.imag() == F() ;
}

///////////////////////////////////////////////////
// operator!=
///////////////////////////////////////////////////

template< typename F >
inline
bool operator!=( const complex<F> & a, const complex<F> & b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( const complex<F> & a, F b )
{
    return !(a == b) ;
}

template< typename F >
inline
bool operator!=( F a, const complex<F> & b )
{
    return !(a == b) ;
}

///////////////////////////////////////////////////
// operator+
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> operator+( const complex<F> & a, const complex<F> & b )
{
    return complex<F>(a.real() + b.real(),
                      a.imag() + b.imag()) ;
}

template< typename F >
inline
complex<F> operator+( F a, const complex<F> & b )
{
    return complex<F>(a + b.real(),
                      b.imag()) ;
}

template< typename F >
inline
complex<F> operator+( const complex<F> & a, F b )
{
    return complex<F>(a.real() + b,
                      a.imag()) ;
}

template< typename F >
inline
const complex<F> & operator+( const complex<F> & a )
{
    return a ;
}

///////////////////////////////////////////////////
// operator-
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> operator-( const complex<F> & a, const complex<F> & b )
{
    return complex<F>(a.real() - b.real(),
                      a.imag() - b.imag()) ;
}

template< typename F >
inline
complex<F> operator-( F a, const complex<F> & b )
{
    return complex<F>(a - b.real(),
                      - b.imag()) ;
}

template< typename F >
inline
complex<F> operator-( const complex<F> & a, F b )
{
    return complex<F>(a.real() - b,
                      a.imag()) ;
}

template< typename F >
inline
complex<F> operator-( const complex<F> & a )
{
    return complex<F>(-a.real(),
                      -a.imag()) ;
}

///////////////////////////////////////////////////
// operator*
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> operator*( const complex<F> & a, const complex<F> & b )
{
    return complex<F>(a.real()*b.real() - a.imag()*b.imag(),
                      a.real()*b.imag() + a.imag()*b.real()) ;
}

template< typename F >
inline
complex<F> operator*( F a, const complex<F> & b )
{
    return complex<F>(a*b.real(),
                      a*b.imag()) ;
}

template< typename F >
inline
complex<F> operator*( const complex<F> & a, F b )
{
    return complex<F>(a.real()*b,
                      a.imag()*b) ;
}

///////////////////////////////////////////////////
// operator/
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> operator/( const complex<F> & a, const complex<F> & b )
{
    const F norm_b = norm(b) ;

    return complex<F>((a.real()*b.real() + a.imag()*b.imag())/norm_b,
                      (a.imag()*b.real() - a.real()*b.imag())/norm_b) ;
}

template< typename F >
inline
complex<F> operator/( const complex<F> & a, F b )
{
    return complex<F>(a.real()/b,
                      a.imag()/b) ;
}

template< typename F >
inline
complex<F> operator/( F a, const complex<F> & b )
{
    const F t = a/norm(b) ;

    return complex<F>( t*b.real(),
                      -t*b.imag()) ;
}

///////////////////////////////////////////////////
//
// complex member functions
//
///////////////////////////////////////////////////

///////////////////////////////////////////////////
// constructors
///////////////////////////////////////////////////

template< typename F >
inline
complex<F>::
complex()
    : mw(F()),
      mx(F())
{
}

template< typename F >
inline
complex<F>::
complex( F w, F x )
    : mw(w),
      mx(x)
{
}

template< typename F >
inline
complex<F>::
complex( F w )
    : mw(w),
      mx(F())
{
}

///////////////////////////////////////////////////
// readers
///////////////////////////////////////////////////

template< typename F >
inline
F
complex<F>::
real() const
{
    return mw ;
}

template< typename F >
inline
F
complex<F>::
imag() const
{
    return mx ;
}

///////////////////////////////////////////////////
// operator+=
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> &
complex<F>::
operator+=( const complex & a )
{
    mw += a.real() ;
    mx += a.imag() ;
    return *this ;
}

template< typename F >
inline
complex<F> &
complex<F>::
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
complex<F> &
complex<F>::
operator-=( const complex & a )
{
    mw -= a.real() ;
    mx -= a.imag() ;
    return *this ;
}

template< typename F >
inline
complex<F> &
complex<F>::
operator-=( F a )
{
    mw -= a ;
    return *this ;
}

///////////////////////////////////////////////////
// operator*=
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> &
complex<F>::
operator*=( const complex & b )
{
    const F x = mw*b.imag() + mx*b.real() ;
    mw = mw*b.real() - mx*b.imag() ;
    mx = x ;
    return *this ;
}

template< typename F >
inline
complex<F> &
complex<F>::
operator*=( F a )
{
    mw *= a ;
    mx *= a ;
    return *this ;
}

///////////////////////////////////////////////////
// operator/=
///////////////////////////////////////////////////

template< typename F >
inline
complex<F> &
complex<F>::
operator/=( F a )
{
    mw /= a ;
    mx /= a ;
    return *this ;
}

template< typename F >
inline
complex<F> &
complex<F>::
operator/=( const complex & b )
{
    const F norm_b = norm(b) ;
    const F x = mx*b.real() - mw*b.imag() ;

    mw = (mw*b.real() + mx*b.imag())/norm_b ;
    mx = x/norm_b ;

    return *this ;
}

///////////////////////////////////////////////////
// data
///////////////////////////////////////////////////

template< typename F >
inline
const F*
complex<F>::
data() const
{
    return &mw ;
}

///////////////////////////////////////////////////
// streams
///////////////////////////////////////////////////

template< typename F, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & out, const complex<F> & a )
{
    out << '('
        << a.real()
        << ','
        << a.imag()
        << ')' ;

    return out ;
}

template< typename F, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & in, complex<F> & a )
{
    T_Char ch ;
    F w ;
    F x ;

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
    if( ch != ')' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    a = complex<F>(w, x) ;

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
F real( F a )
{
    return a ;
}

template< typename F >
inline
F imag( F )
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

} // namespace scalar_func

} // namespace complex_namespace

using complex_namespace::complex ;

}} // namespace esve::math

#endif // !defined(USE_STD_COMPLEX)

#endif
