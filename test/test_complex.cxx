//
// A complete or near-complete test of complex.hxx.
//

#include "common.hxx"
#include <sstream>
#include <limits>

void test_complex()
{
    using namespace esve::math::complex_namespace::scalar_func ;
    using ::real ;

    for( int n = 0 ; n != TRIALS ; ++n ) for( int g = -5 ; g <= 5 ; ++g )
    {
        unsigned int h = abs(g) ;

        const complex a = rand_complex() ;
        const complex b = rand_complex() ;
        const complex c = rand_complex() ;
        const complex d = rand_complex() ;
        const complex t = rand_complex() ;
        const real r = rand_real() ;
        const real s = rand_real() ;

        //template<typename F> F norm( const complex<F> & ) ;

        assert_close(norm(a),
                     a.real()*a.real() +
                     a.imag()*a.imag()) ;

        //template<typename F> complex<F> conj( const complex<F> & ) ;

        assert_equal(conj(a), complex(a.real(), -a.imag())) ;

        //template<typename F> complex<F> inv( const complex<F> & ) ;

        assert_close(a*inv(a), real(1)) ;
        assert_close(inv(a)*a, real(1)) ;

        //template<typename F> F dot( const complex<F> &, const complex<F> & ) ;
        //template<typename F> F dot( F, const complex<F> & ) ;
        //template<typename F> F dot( const complex<F> &, F ) ;

        assert_close(dot(a, b), (b*conj(a) + a*conj(b))/real(2)) ;

        assert_close(dot(a, s), dot(complex(a), complex(s))) ;
        assert_close(dot(r, b), dot(complex(r), complex(b))) ;
        assert_close(dot(r, s), dot(complex(r), complex(s))) ;


        //template<typename F> F abs( const complex<F> & ) ;

        assert_close(abs(a), sqrt(norm(a))) ;

        //template<typename F> complex<F> exp( const complex<F> & ) ;
        //template<typename F> complex<F> log( const complex<F> & ) ;

        assert_close(exp(log(a)), a) ;
        assert_close(log(exp(a)), a) ;

        //template<typename F> complex<F> pow( const complex<F> &, F ) ;
        //template<typename F> complex<F> pow( const complex<F> &, unsigned int ) ;
        //template<typename F> complex<F> pow( const complex<F> &, int ) ;
        //template<typename F> complex<F> pow( F, const complex<F> & ) ;

        assert_close(pow(a, s), exp(s*log(a))) ;
        assert_close(pow(a, g), pow(complex(a), real(g))) ;
        assert_close(pow(a, h), pow(complex(a), real(h))) ;

        assert_close(pow(abs(r), a), exp(log(abs(r))*a)) ;

        //template<typename F> complex<F> cos( const complex<F> & ) ;
        //template<typename F> complex<F> sin( const complex<F> & ) ;
        //template<typename F> complex<F> cosh( const complex<F> & ) ;
        //template<typename F> complex<F> sinh( const complex<F> & ) ;

        {
            const complex i = complex(0, 1) ;

            assert_close(cos(a), (exp(i*a) + exp(-i*a))/real(2)) ;
            assert_close(sin(a), inv(i)*(exp(i*a) - exp(-i*a))/real(2)) ;
            assert_close(cosh(a), (exp(a) + exp(-a))/real(2)) ;
            assert_close(sinh(a), (exp(a) - exp(-a))/real(2)) ;

            assert_close(cos(i),
                         (exp(abs(i)) + exp(-abs(i)))/real(2)) ;
            assert_close(sin(i),
                         (i/abs(i))*(exp(abs(i)) - exp(-abs(i)))/real(2)) ;

            assert_close(cosh(i), (exp(i) + exp(-i))/real(2)) ;
            assert_close(sinh(i), (exp(i) - exp(-i))/real(2)) ;
        }

        {
            complex exp_a = complex(0) ;
            complex cos_a = complex(0) ;
            complex sin_a = complex(0) ;
            complex cosh_a = complex(0) ;
            complex sinh_a = complex(0) ;

            for( unsigned int n = 0 ; n <= 16 ; ++n )
            {
                const complex t = pow(a, n)/factorial<real>(n) ;

                exp_a += t ;

                switch( n % 4 )
                {
                case 0:
                    cos_a += t ;
                    cosh_a += t ;
                    break ;
                case 1:
                    sin_a += t ;
                    sinh_a += t ;
                    break ;
                case 2:
                    cos_a -= t ;
                    cosh_a += t ;
                    break ;
                case 3:
                    sin_a -= t ;
                    sinh_a += t ;
                    break ;
                }
            }

            assert_close(exp_a, exp(a)) ;
            assert_close(cos_a, cos(a)) ;
            assert_close(sin_a, sin(a)) ;
            assert_close(cosh_a, cosh(a)) ;
            assert_close(sinh_a, sinh(a)) ;

            assert_close(exp(complex(0, 1)*r*a),
                         cos(r*a) + complex(0, 1)*sin(r*a)) ;
        }

        //template<typename F> complex<F> sqrt( const complex<F> & ) ;

        assert_close(sqrt(a), pow(a, real(0.5))) ;
        assert_close(sqrt(a), exp(real(0.5)*log(a))) ;

        //template<typename F> bool operator==( const complex<F> &,
        //                                      const complex<F> & ) ;
        //template<typename F> bool operator==( const complex<F> &,
        //                                      const complex<F> & ) ;
        //template<typename F> bool operator==( const complex<F> &, F ) ;
        //template<typename F> bool operator==( F, const complex<F> & ) ;
        //template<typename F> bool operator!=( const complex<F> &,
        //                                      const complex<F> & ) ;
        //template<typename F> bool operator!=( const complex<F> &,
        //                                      const complex<F> & ) ;
        //template<typename F> bool operator!=( const complex<F> &, F ) ;
        //template<typename F> bool operator!=( F, const complex<F> & ) ;

        {
            complex b = a ;
            assert_equal((a == b), true) ;
            assert_equal((a != b), false) ;
        }
        {
            complex a = complex(r) ;
            assert_equal((a == r), true) ;
            assert_equal((r == a), true) ;
            assert_equal((a != r), false) ;
            assert_equal((r != a), false) ;
        }

        //template<typename F> complex<F> operator+( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator+( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator+( F, const complex<F> & ) ;
        //template<typename F> complex<F> operator+( const complex<F> &, F ) ;
        //template<typename F> const complex<F> & operator+( const complex<F> & ) ;

        assert_close(a + b, complex(a.real() + b.real(),
                                    a.imag() + b.imag())) ;
        assert_close(a + r, complex(a) + complex(r)) ;
        assert_close(r + a, complex(r) + complex(a)) ;
        assert_equal(a, +a) ;

        //template<typename F> complex<F> operator-( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator-( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator-( F, const complex<F> & ) ;
        //template<typename F> complex<F> operator-( const complex<F> &, F ) ;
        //template<typename F> complex<F> operator-( const complex<F> & ) ;

        assert_close(a - b, complex(a.real() - b.real(),
                                    a.imag() - b.imag())) ;
        assert_close(a - r, complex(a) - complex(r)) ;
        assert_close(r - a, complex(r) - complex(a)) ;
        assert_close(complex(0) - a, -a) ;

        //template<typename F> complex<F> operator*( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator*( const complex<F> &,
        //                                        const complex<F> & ) ;
        //template<typename F> complex<F> operator*( F, const complex<F> & ) ;
        //template<typename F> complex<F> operator*( const complex<F> &, F ) ;

        assert_close(
            a*b,
            complex(a.real()*b.real() - a.imag()*b.imag(),
                    a.real()*b.imag() + a.imag()*b.real())) ;

        assert_close(a*r, complex(a)*complex(r)) ;
        assert_close(r*a, complex(r)*complex(a)) ;

        //template<typename F> complex<F> operator/( const complex<F> &, F ) ;
        //template<typename F> complex<F> operator/( F, const complex<F> & ) ;
        //template<typename F> complex<F> operator/( const complex<F> &, F ) ;

        assert_close(a/b, a*conj(b)/norm(b)) ;
        assert_close(a/r, complex(a.real()/r, a.imag()/r)) ;
        assert_close(r/a, r*conj(a)/norm(a)) ;

        //namespace scalar_func {
        //template< typename F > F realpart( F a )  ;
        //template< typename F > F purepart( F a )  ;
        //template< typename F > F norm( F a )  ;
        //template< typename F > F conj( F a )  ;
        //template< typename F > F inv( F a )  ;
        //template< typename F > F dot( F a, F b )  ;
        //using std::abs ;
        //using std::exp ;
        //using std::log ;
        //using std::cos ;
        //using std::sin ;
        //using std::cosh ;
        //using std::sinh ;
        //using std::pow ;
        //using std::sqrt ;
        //} // namespace scalar_func

        assert_close(norm(r), r*r) ;
        assert_close(conj(r), r) ;
        assert_close(inv(r), real(1)/r) ;
        assert_close(dot(r, s), r*s) ;

        //complex() ;
        //complex( F w, F x, F y, F z ) ;
        //explicit complex( F ) ;
        // compiler writes memberwise copy and assign

        assert_close(complex(), complex(0, 0)) ;
        assert_close(a, complex(a.real(), a.imag())) ;
        assert_close(r, complex(r)) ;

        // skip:
        //F w() const ;
        //F x() const ;
        //F y() const ;
        //F z() const ;
        //void w( F ) ;
        //void x( F ) ;
        //void y( F ) ;
        //void z( F ) ;

        //complex & operator+=( const complex & ) ;
        //complex & operator+=( F ) ;

        {
            complex c = a ;
            c += b ;
            assert_close(a + b, c) ;
        }
        {
            complex c = a ;
            c += r ;
            assert_close(a + r, c) ;
        }

        //complex & operator-=( const complex & ) ;
        //complex & operator-=( F ) ;

        {
            complex c = a ;
            c -= b ;
            assert_close(a - b, c) ;
        }
        {
            complex c = a ;
            c -= r ;
            assert_close(a - r, c) ;
        }

        //complex & operator*=( const complex & ) ;
        //complex & operator*=( F ) ;

        {
            complex c = a ;
            c *= b ;
            assert_close(a*b, c) ;
        }
        {
            complex c = a ;
            c *= r ;
            assert_close(a*r, c) ;
        }

        //complex & operator/=( F ) ;
        //complex & operator/=( const complex<F> & ) ;

        {
            complex c = a ;
            c /= r ;
            assert_close(a/r, c) ;
        }
        {
            complex c = a ;
            c /= b ;
            assert_close(a/b, c) ;
        }

        //const F* data() const ;

        assert_equal(reinterpret_cast<const real*>(&a), a.data()) ;

        // streams
        {
            complex a = rand_complex() ;
            complex b ;

            std::ostringstream out ;
            out.precision(std::numeric_limits<real>::digits10 + 1) ;

            out << a ;
            std::istringstream in(out.str()) ;
            in >> b ;

            assert_close(a, b) ;
        }
    }
}



