
#ifndef test_common_hxx
#define test_common_hxx

#include <esve/math/complex.hxx>
#include <esve/math/quat.hxx>
#include <esve/math/moebius.hxx>
#include <iostream>
#include <cstdlib>
#include <cmath>

typedef long double real ;
typedef esve::math::complex<real> complex ;
typedef esve::math::pure<real> pure ;
typedef esve::math::quat<real> quat ;

const int TRIALS = 1000 ;

const real EPSILON = 1e-5 ;

// between -1 and 1
inline
real rand_real()
{
    return real(2.0*(double(std::rand())/RAND_MAX) - 1.0) ;
}

inline
complex rand_complex()
{
    return complex(rand_real(),
                   rand_real()) ;
}

inline
quat rand_quat()
{
    return quat(rand_real(),
                rand_real(),
                rand_real(),
                rand_real()) ;
}

inline
pure rand_pure()
{
    return pure(rand_real(),
                rand_real(),
                rand_real()) ;
}

inline
bool within( const complex & a, const complex & b, real epsilon )
{
    return
        std::abs(a.real() - b.real()) < epsilon &&
        std::abs(a.imag() - b.imag()) < epsilon ;
}

inline
bool within( const complex & a, const real & b, real epsilon )
{
    return within(complex(a), complex(b), epsilon) ;
}

inline
bool within( const real & a, const complex & b, real epsilon )
{
    return within(complex(a), complex(b), epsilon) ;
}

inline
bool within( const quat & a, const quat & b, real epsilon )
{
    return
        std::abs(a.w() - b.w()) < epsilon &&
        std::abs(a.x() - b.x()) < epsilon &&
        std::abs(a.y() - b.y()) < epsilon &&
        std::abs(a.z() - b.z()) < epsilon ;
}

inline bool within( const quat & a, const pure & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const quat & a, const real & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const pure & a, const quat & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const pure & a, const pure & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const pure & a, const real & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const real & a, const quat & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const real & a, const pure & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

inline bool within( const real & a, const real & b, real epsilon )
{
    return within(quat(a), quat(b), epsilon) ;
}

template< typename scalar >
scalar factorial( unsigned int x )
{
    scalar result = scalar(1) ;

    for( unsigned int t = 2 ; t <= x ; ++t )
    {
        result *= scalar(t) ;
    }

    return result ;
}

extern int g_assertion_count ;

#define show(a) { std::cout << (a) << " <== " << #a << std::endl ; }

#define assert_close(a, b) \
    if( !within((a), (b), EPSILON) ) \
    { \
        std::cout \
            << "Assertion failed. Not within " \
            << EPSILON \
            << ":" \
            << std::endl ; \
        show(a) ; \
        show(b) ; \
        std::cout << __FILE__ << ":" << __LINE__ << std::endl ; \
        std::exit(1) ; \
    } \
    else \
    { \
        g_assertion_count += 1 ; \
    } \

#define assert_equal(a, b) \
    if( (a) != (b) ) \
    { \
        std::cout \
            << "Assertion failed. Not equal:" \
            << std::endl ; \
        show(a) ; \
        show(b) ; \
        std::cout << __FILE__ << ":" << __LINE__ << std::endl ; \
        std::exit(1) ; \
    } \
    else \
    { \
        g_assertion_count += 1 ; \
    } \

#endif
