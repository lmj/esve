//
// A complete or near-complete test of quat.hxx.
//

#include "common.hxx"
#include <sstream>
#include <limits>

void test_quat()
{
    using namespace esve::math::quat_namespace::scalar_func ;
    using std::acos ;

    {
        const pure i = pure(1, 0, 0) ;
        const pure j = pure(0, 1, 0) ;
        const pure k = pure(0, 0, 1) ;

        assert_close(i, j*k) ;
        assert_close(j, k*i) ;
        assert_close(k, i*j) ;

        assert_close(i, -k*j) ;
        assert_close(j, -i*k) ;
        assert_close(k, -j*i) ;
    }

    {
        const quat i = quat(0, 1, 0, 0) ;
        const quat j = quat(0, 0, 1, 0) ;
        const quat k = quat(0, 0, 0, 1) ;

        assert_close(i, j*k) ;
        assert_close(j, k*i) ;
        assert_close(k, i*j) ;

        assert_close(i, -k*j) ;
        assert_close(j, -i*k) ;
        assert_close(k, -j*i) ;
    }

    for( int n = 0 ; n != TRIALS ; ++n ) for( int g = -5 ; g <= 5 ; ++g )
    {
        unsigned int h = abs(g) ;

        const quat a = rand_quat() ;
        const quat b = rand_quat() ;
        const quat c = rand_quat() ;
        const quat d = rand_quat() ;
        const quat t = rand_quat() ;
        const pure u = rand_pure() ;
        const pure v = rand_pure() ;
        const real r = rand_real() ;
        const real s = rand_real() ;

        //template<typename F> F realpart( const quat<F> & ) ;
        //template<typename F> F realpart( const pure<F> & ) ;

        assert_equal(realpart(a), a.w()) ;
        assert_equal(realpart(u), real(0)) ;

        //template<typename F> const pure<F> purepart( const quat<F> & ) ;
        //template<typename F> const pure<F> & purepart( const pure<F> & ) ;

        assert_equal(purepart(a), pure(a.x(), a.y(), a.z())) ;
        assert_equal(u, purepart(u)) ;

        //template<typename F> F norm( const quat<F> & ) ;
        //template<typename F> F norm( const pure<F> & ) ;

        assert_close(norm(a),
                     a.w()*a.w() +
                     a.x()*a.x() +
                     a.y()*a.y() +
                     a.z()*a.z()) ;
        assert_close(norm(u),
                     u.x()*u.x() +
                     u.y()*u.y() +
                     u.z()*u.z()) ;

        //template<typename F> quat<F> conj( const quat<F> & ) ;
        //template<typename F> pure<F> conj( const pure<F> & ) ;

        assert_equal(conj(a), quat(a.w(), -a.x(), -a.y(), -a.z())) ;
        assert_equal(conj(u), pure(-u.x(), -u.y(), -u.z())) ;

        //template<typename F> quat<F> inv( const quat<F> & ) ;
        //template<typename F> pure<F> inv( const pure<F> & ) ;

        assert_close(a*inv(a), real(1)) ;
        assert_close(inv(a)*a, real(1)) ;

        assert_close(u*inv(u), real(1)) ;
        assert_close(inv(u)*u, real(1)) ;

        //template<typename F> F dot( const quat<F> &, const quat<F> & ) ;
        //template<typename F> F dot( const quat<F> &, const pure<F> & ) ;
        //template<typename F> F dot( const pure<F> &, const quat<F> & ) ;
        //template<typename F> F dot( const pure<F> &, const pure<F> & ) ;
        //template<typename F> F dot( F, const quat<F> & ) ;
        //template<typename F> F dot( const quat<F> &, F ) ;
        //template<typename F> F dot( F, const pure<F> & ) ;
        //template<typename F> F dot( const pure<F> &, F ) ;

        assert_close(dot(a, b), (b*conj(a) + a*conj(b))/real(2)) ;

        assert_close(dot(a, v), dot(quat(a), quat(v))) ;
        assert_close(dot(u, b), dot(quat(u), quat(b))) ;
        assert_close(dot(u, v), dot(quat(u), quat(v))) ;
        assert_close(dot(a, s), dot(quat(a), quat(s))) ;
        assert_close(dot(r, b), dot(quat(r), quat(b))) ;
        assert_close(dot(r, s), dot(quat(r), quat(s))) ;

    //template<typename F> pure<F> cross( const quat<F> &, const quat<F> & ) ;
    //template<typename F> pure<F> cross( const quat<F> &, const pure<F> & ) ;
    //template<typename F> pure<F> cross( const pure<F> &, const quat<F> & ) ;
    //template<typename F> pure<F> cross( const pure<F> &, const pure<F> & ) ;
    //template<typename F> pure<F> cross( F, const quat<F> & ) ;
    //template<typename F> pure<F> cross( const quat<F> &, F ) ;
    //template<typename F> pure<F> cross( F, const pure<F> & ) ;
    //template<typename F> pure<F> cross( const pure<F> &, F ) ;

        assert_close(cross(a, b), (b*conj(a) - a*conj(b))/real(2)) ;

        assert_close(cross(a, v), cross(quat(a), quat(v))) ;
        assert_close(cross(u, b), cross(quat(u), quat(b))) ;
        assert_close(cross(u, v), cross(quat(u), quat(v))) ;
        assert_close(cross(a, s), cross(quat(a), quat(s))) ;
        assert_close(cross(r, b), cross(quat(r), quat(b))) ;
        assert_close(cross(r, s), cross(quat(r), quat(s))) ;

        //template<typename F> F abs( const quat<F> & ) ;
        //template<typename F> F abs( const pure<F> & ) ;

        assert_close(abs(a), sqrt(norm(a))) ;
        assert_close(abs(u), sqrt(norm(u))) ;

        //template<typename F> quat<F> exp( const quat<F> & ) ;
        //template<typename F> quat<F> exp( const pure<F> & ) ;
        //template<typename F> quat<F> log( const quat<F> & ) ;
        //template<typename F> quat<F> log( const pure<F> & ) ;

        assert_close(exp(a),
                     exp(realpart(a))*(cos(abs(purepart(a)))
                                       +
                                       ((purepart(a))/abs(purepart(a)))
                                       *
                                       sin(abs(purepart(a))))) ;

        assert_close(exp(u),
                     exp(realpart(u))*(cos(abs(purepart(u)))
                                       +
                                       ((purepart(u))/abs(purepart(u)))
                                       *
                                       sin(abs(purepart(u))))) ;

        assert_close(log(a),
                     log(abs(a))
                     +
                     (purepart(a)/abs(purepart(a)))
                     *
                     acos(dot(real(1), a)/abs(a))) ;

        assert_close(log(u),
                     log(abs(u))
                     +
                     (purepart(u)/abs(purepart(u)))
                     *
                     acos(dot(real(1), u)/abs(u))) ;

        assert_close(exp(log(a)), a) ;
        assert_close(log(exp(a)), a) ;

        assert_close(exp(log(u)), u) ;
        assert_close(log(exp(u)), u) ;

        //template<typename F> quat<F> pow( const quat<F> &, F ) ;
        //template<typename F> quat<F> pow( const quat<F> &, unsigned int ) ;
        //template<typename F> quat<F> pow( const quat<F> &, int ) ;
        //template<typename F> quat<F> pow( F, const quat<F> & ) ;
        //template<typename F> quat<F> pow( const pure<F> &, F ) ;
        //template<typename F> quat<F> pow( const pure<F> &, unsigned int ) ;
        //template<typename F> quat<F> pow( const pure<F> &, int ) ;
        //template<typename F> quat<F> pow( F, const pure<F> & ) ;

        assert_close(pow(a, s), exp(s*log(a))) ;
        assert_close(pow(a, g), pow(quat(a), real(g))) ;
        assert_close(pow(a, h), pow(quat(a), real(h))) ;
        assert_close(pow(u, s), pow(quat(u), real(s))) ;
        assert_close(pow(u, g), pow(quat(u), real(g))) ;
        assert_close(pow(u, h), pow(quat(u), real(h))) ;

        assert_close(pow(abs(r), a), exp(log(abs(r))*a)) ;
        assert_close(pow(abs(r), u), exp(log(abs(r))*u)) ;

        //template<typename F> quat<F> cos( const quat<F> & ) ;
        //template<typename F> quat<F> cos( const pure<F> & ) ;
        //template<typename F> quat<F> sin( const quat<F> & ) ;
        //template<typename F> quat<F> sin( const pure<F> & ) ;
        //template<typename F> quat<F> tan( const quat<F> & ) ;
        //template<typename F> quat<F> tan( const pure<F> & ) ;
        //template<typename F> quat<F> cosh( const quat<F> & ) ;
        //template<typename F> quat<F> cosh( const pure<F> & ) ;
        //template<typename F> quat<F> sinh( const quat<F> & ) ;
        //template<typename F> quat<F> sinh( const pure<F> & ) ;
        //template<typename F> quat<F> tanh( const quat<F> & ) ;
        //template<typename F> quat<F> tanh( const pure<F> & ) ;

        {
            pure u = purepart(a)/abs(purepart(a)) ;

            assert_close(cos(a), (exp(u*a) + exp(-u*a))/real(2)) ;
            assert_close(sin(a), inv(u)*(exp(u*a) - exp(-u*a))/real(2)) ;
            assert_close(cosh(a), (exp(a) + exp(-a))/real(2)) ;
            assert_close(sinh(a), (exp(a) - exp(-a))/real(2)) ;
        }

        assert_close(cos(u), (exp(abs(u)) + exp(-abs(u)))/real(2)) ;
        assert_close(sin(u), (u/abs(u))*(exp(abs(u)) - exp(-abs(u)))/real(2)) ;
        assert_close(cosh(u), (exp(u) + exp(-u))/real(2)) ;
        assert_close(sinh(u), (exp(u) - exp(-u))/real(2)) ;

        {
            quat exp_a = quat(0) ;
            quat cos_a = quat(0) ;
            quat sin_a = quat(0) ;
            quat cosh_a = quat(0) ;
            quat sinh_a = quat(0) ;

            // log needs a smaller radius
            quat b = rand_quat() ;
            b /= abs(b) ;
            b *= 0.5*rand_real() ;
            quat log_b_plus_1 = quat(0) ;

            for( unsigned int n = 0 ; n <= 16 ; ++n )
            {
                const quat t = pow(a, n)/factorial<real>(n) ;
                const quat p = pow(b, n)/real(n) ;

                exp_a += t ;

                switch( n % 4 )
                {
                case 0:
                    cos_a += t ;
                    cosh_a += t ;
                    if( n > 0 ) log_b_plus_1 -= p ;
                    break ;
                case 1:
                    sin_a += t ;
                    sinh_a += t ;
                    log_b_plus_1 += p ;
                    break ;
                case 2:
                    cos_a -= t ;
                    cosh_a += t ;
                    log_b_plus_1 -= p ;
                    break ;
                case 3:
                    sin_a -= t ;
                    sinh_a += t ;
                    log_b_plus_1 += p ;
                    break ;
                }
            }

            assert_close(exp_a, exp(a)) ;
            assert_close(cos_a, cos(a)) ;
            assert_close(sin_a, sin(a)) ;
            assert_close(cosh_a, cosh(a)) ;
            assert_close(sinh_a, sinh(a)) ;
            assert_close(log_b_plus_1, log(b + real(1))) ;

            pure u = purepart(a)/abs(purepart(a)) ;
            assert_close(exp(u*r*a), cos(r*a) + u*sin(r*a)) ;
        }
        {
            quat exp_u = quat(0) ;
            quat cos_u = quat(0) ;
            quat sin_u = quat(0) ;
            quat cosh_u = quat(0) ;
            quat sinh_u = quat(0) ;

            for( unsigned int n = 0 ; n <= 16 ; ++n )
            {
                const quat t = pow(u, n)/factorial<real>(n) ;

                exp_u += t ;

                switch( n % 4 )
                {
                case 0:
                    cos_u += t ;
                    cosh_u += t ;
                    break ;
                case 1:
                    sin_u += t ;
                    sinh_u += t ;
                    break ;
                case 2:
                    cos_u -= t ;
                    cosh_u += t ;
                    break ;
                case 3:
                    sin_u -= t ;
                    sinh_u += t ;
                    break ;
                }
            }

            assert_close(exp_u, exp(u)) ;
            assert_close(cos_u, cos(u)) ;
            assert_close(sin_u, sin(u)) ;
            assert_close(cosh_u, cosh(u)) ;
            assert_close(sinh_u, sinh(u)) ;
        }
        {
            assert_close(tan(a), sin(a)*inv(cos(a))) ;
            assert_close(tan(a), inv(cos(a))*sin(a)) ;
            assert_close(tanh(a), sinh(a)*inv(cosh(a))) ;
            assert_close(tanh(a), inv(cosh(a))*sinh(a)) ;
        }
        {
            assert_close(tan(u), sin(u)*inv(cos(u))) ;
            assert_close(tan(u), inv(cos(u))*sin(u)) ;
            assert_close(tanh(u), sinh(u)*inv(cosh(u))) ;
            assert_close(tanh(u), inv(cosh(u))*sinh(u)) ;
        }

        //template<typename F> quat<F> sqrt( const quat<F> & ) ;
        //template<typename F> quat<F> sqrt( const pure<F> & ) ;

        assert_close(sqrt(a), pow(a, real(0.5))) ;
        assert_close(sqrt(a), exp(real(0.5)*log(a))) ;
        assert_close(sqrt(u), pow(u, real(0.5))) ;
        assert_close(sqrt(u), exp(real(0.5)*log(u))) ;

        //template<typename F> bool operator==( const quat<F> &,
        //                                      const quat<F> & ) ;
        //template<typename F> bool operator==( const quat<F> &,
        //                                      const pure<F> & ) ;
        //template<typename F> bool operator==( const pure<F> &,
        //                                      const quat<F> & ) ;
        //template<typename F> bool operator==( const pure<F> &,
        //                                      const pure<F> & ) ;
        //template<typename F> bool operator==( const quat<F> &, F ) ;
        //template<typename F> bool operator==( const pure<F> &, F ) ;
        //template<typename F> bool operator==( F, const quat<F> & ) ;
        //template<typename F> bool operator==( F, const pure<F> & ) ;
        //template<typename F> bool operator!=( const quat<F> &,
        //                                      const quat<F> & ) ;
        //template<typename F> bool operator!=( const quat<F> &,
        //                                      const pure<F> & ) ;
        //template<typename F> bool operator!=( const pure<F> &,
        //                                      const quat<F> & ) ;
        //template<typename F> bool operator!=( const pure<F> &,
        //                                      const pure<F> & ) ;
        //template<typename F> bool operator!=( const quat<F> &, F ) ;
        //template<typename F> bool operator!=( const pure<F> &, F ) ;
        //template<typename F> bool operator!=( F, const quat<F> & ) ;
        //template<typename F> bool operator!=( F, const pure<F> & ) ;

        {
            quat b = a ;
            assert_equal((a == b), true) ;
            assert_equal((a != b), false) ;
        }
        {
            quat a = quat(purepart(a)) ;
            pure u = purepart(a) ;
            assert_equal((a == u), true) ;
            assert_equal((u == a), true) ;
            assert_equal((a != u), false) ;
            assert_equal((u != a), false) ;
        }
        {
            pure v = u ;
            assert_equal((u == v), true) ;
            assert_equal((u != v), false) ;
        }
        {
            quat a = quat(r) ;
            assert_equal((a == r), true) ;
            assert_equal((r == a), true) ;
            assert_equal((a != r), false) ;
            assert_equal((r != a), false) ;
        }

        //template<typename F> quat<F> operator+( const quat<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> quat<F> operator+( const quat<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator+( const pure<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> pure<F> operator+( const pure<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator+( F, const quat<F> & ) ;
        //template<typename F> quat<F> operator+( F, const pure<F> & ) ;
        //template<typename F> quat<F> operator+( const quat<F> &, F ) ;
        //template<typename F> quat<F> operator+( const pure<F> &, F ) ;
        //template<typename F> const quat<F> & operator+( const quat<F> & ) ;
        //template<typename F> const pure<F> & operator+( const pure<F> & ) ;

        assert_close(a + b, quat(a.w() + b.w(),
                                 a.x() + b.x(),
                                 a.y() + b.y(),
                                 a.z() + b.z())) ;
        assert_close(a + u, quat(a) + quat(u)) ;
        assert_close(u + a, quat(u) + quat(a)) ;
        assert_close(a + r, quat(a) + quat(r)) ;
        assert_close(r + a, quat(r) + quat(a)) ;
        assert_close(u + r, quat(u) + quat(r)) ;
        assert_close(r + u, quat(r) + quat(u)) ;
        assert_equal(a, +a) ;
        assert_equal(u, +u) ;

        //template<typename F> quat<F> operator-( const quat<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> quat<F> operator-( const quat<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator-( const pure<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> pure<F> operator-( const pure<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator-( F, const quat<F> & ) ;
        //template<typename F> quat<F> operator-( F, const pure<F> & ) ;
        //template<typename F> quat<F> operator-( const quat<F> &, F ) ;
        //template<typename F> quat<F> operator-( const pure<F> &, F ) ;
        //template<typename F> quat<F> operator-( const quat<F> & ) ;
        //template<typename F> pure<F> operator-( const pure<F> & ) ;

        assert_close(a - b, quat(a.w() - b.w(),
                                 a.x() - b.x(),
                                 a.y() - b.y(),
                                 a.z() - b.z())) ;
        assert_close(a - u, quat(a) - quat(u)) ;
        assert_close(u - a, quat(u) - quat(a)) ;
        assert_close(a - r, quat(a) - quat(r)) ;
        assert_close(r - a, quat(r) - quat(a)) ;
        assert_close(u - r, quat(u) - quat(r)) ;
        assert_close(r - u, quat(r) - quat(u)) ;
        assert_close(quat(0) - a, -a) ;
        assert_close(quat(0) - u, -u) ;

        //template<typename F> quat<F> operator*( const quat<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> quat<F> operator*( const quat<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator*( const pure<F> &,
        //                                        const quat<F> & ) ;
        //template<typename F> quat<F> operator*( const pure<F> &,
        //                                        const pure<F> & ) ;
        //template<typename F> quat<F> operator*( F, const quat<F> & ) ;
        //template<typename F> pure<F> operator*( F, const pure<F> & ) ;
        //template<typename F> quat<F> operator*( const quat<F> &, F ) ;
        //template<typename F> pure<F> operator*( const pure<F> &, F ) ;

#if !defined(QUAT_CONSERVE_MULTIPLIES)
        {
            real a1 = real( (a.z() - a.y())*(b.y() - b.z()) ) ;
            real a2 = real( (a.w() + a.x())*(b.w() + b.x()) ) ;
            real a3 = real( (a.w() - a.x())*(b.y() + b.z()) ) ;
            real a4 = real( (a.y() + a.z())*(b.w() - b.x()) ) ;

            real b1 = real(-(a.x() - a.z())*(b.x() - b.y()) ) ;
            real b2 = real(-(a.x() + a.z())*(b.x() + b.y()) ) ;
            real b3 = real( (a.w() + a.y())*(b.w() - b.z()) ) ;
            real b4 = real( (a.w() - a.y())*(b.w() + b.z()) ) ;

            assert_close(a*b, quat(a1 + real(0.5)*(b1 + b2 + b3 + b4),
                                   a2 + real(0.5)*(b1 + b2 - b3 - b4),
                                   a3 + real(0.5)*(b1 - b2 + b3 - b4),
                                   a4 + real(0.5)*(b1 - b2 - b3 + b4))) ;
        }
#elif defined(QUAT_CONSERVE_MULTIPLIES)
        assert_close(
            a*b,
            quat(a.w()*b.w() - a.x()*b.x() - a.y()*b.y() - a.z()*b.z(),
                 a.w()*b.x() + a.x()*b.w() + a.y()*b.z() - a.z()*b.y(),
                 a.w()*b.y() - a.x()*b.z() + a.y()*b.w() + a.z()*b.x(),
                 a.w()*b.z() + a.x()*b.y() - a.y()*b.x() + a.z()*b.w())) ;
#endif

        assert_close(a*u, quat(a)*quat(u)) ;
        assert_close(u*a, quat(u)*quat(a)) ;
        assert_close(a*r, quat(a)*quat(r)) ;
        assert_close(r*a, quat(r)*quat(a)) ;
        assert_close(u*r, quat(u)*quat(r)) ;
        assert_close(r*u, quat(r)*quat(u)) ;

        //template<typename F> quat<F> operator/( const quat<F> &, F ) ;
        //template<typename F> pure<F> operator/( const pure<F> &, F ) ;

        assert_close(a/r, quat(a.w()/r, a.x()/r, a.y()/r, a.z()/r)) ;
        assert_close(u/r, pure(u.x()/r, u.y()/r, u.z()/r)) ;

        //namespace scalar_func {
        //template< typename F > F realpart( F a )  ;
        //template< typename F > F purepart( F a )  ;
        //template< typename F > F norm( F a )  ;
        //template< typename F > F conj( F a )  ;
        //template< typename F > F inv( F a )  ;
        //template< typename F > F dot( F a, F b )  ;
        //template< typename F > F cross( F a, F b )  ;
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

        assert_equal(realpart(r), r) ;
        assert_equal(purepart(r), real(0)) ;
        assert_close(norm(r), r*r) ;
        assert_close(conj(r), r) ;
        assert_close(inv(r), real(1)/r) ;
        assert_close(dot(r, s), r*s) ;
        assert_equal(cross(r, s), real(0)) ;

        //quat() ;
        //quat( F w, F x, F y, F z ) ;
        //quat( F w, const pure<F> & ) ;
        //explicit quat( const pure<F> & ) ;
        //explicit quat( F ) ;
        // compiler writes memberwise copy and assign

        assert_equal(quat(), quat(0, 0, 0, 0)) ;
        assert_equal(a, quat(a.w(), a.x(), a.y(), a.z())) ;
        assert_equal(a, quat(realpart(a), purepart(a))) ;
        assert_equal(u, quat(u)) ;
        assert_equal(r, quat(r)) ;

        // skip:
        //F w() const ;
        //F x() const ;
        //F y() const ;
        //F z() const ;
        //void w( F ) ;
        //void x( F ) ;
        //void y( F ) ;
        //void z( F ) ;

        //quat & operator+=( const quat & ) ;
        //quat & operator+=( const pure<F> & ) ;
        //quat & operator+=( F ) ;

        {
            quat c = a ;
            c += b ;
            assert_close(a + b, c) ;
        }
        {
            quat c = a ;
            c += u ;
            assert_close(a + u, c) ;
        }
        {
            quat c = a ;
            c += r ;
            assert_close(a + r, c) ;
        }

        //quat & operator-=( const quat & ) ;
        //quat & operator-=( const pure<F> & ) ;
        //quat & operator-=( F ) ;

        {
            quat c = a ;
            c -= b ;
            assert_close(a - b, c) ;
        }
        {
            quat c = a ;
            c -= u ;
            assert_close(a - u, c) ;
        }
        {
            quat c = a ;
            c -= r ;
            assert_close(a - r, c) ;
        }

        //quat & operator*=( const quat & ) ;
        //quat & operator*=( const pure<F> & ) ;
        //quat & operator*=( F ) ;

        {
            quat c = a ;
            c *= b ;
            assert_close(a*b, c) ;
        }
        {
            quat c = a ;
            c *= u ;
            assert_close(a*u, c) ;
        }
        {
            quat c = a ;
            c *= r ;
            assert_close(a*r, c) ;
        }

        //quat & operator/=( F ) ;

        {
            quat c = a ;
            c /= r ;
            assert_close(a/r, c) ;
        }

        //const F* data() const ;

        assert_equal(reinterpret_cast<const real*>(&a), a.data()) ;

        //pure() ;
        //pure( F x, F y, F z ) ;
        // compiler writes memberwise copy and assign

        assert_equal(pure(), pure(0, 0, 0)) ;
        assert_equal(u, pure(u.x(), u.y(), u.z())) ;

        // skip:
        //F w() const ;
        //F x() const ;
        //F y() const ;
        //F z() const ;
        //void x( F ) ;
        //void y( F ) ;
        //void z( F ) ;

        //pure & operator+=( const pure & ) ;
        //pure & operator-=( const pure & ) ;
        //pure & operator*=( F ) ;
        //pure & operator/=( F ) ;

        {
            pure c = u ;
            c += v ;
            assert_close(u + v, c)
        }
        {
            pure c = u ;
            c -= v ;
            assert_close(u - v, c)
        }
        {
            pure c = u ;
            c *= r ;
            assert_close(u*r, c)
        }
        {
            pure c = u ;
            c /= r ;
            assert_close(u/r, c)
        }

        //const F* data() const ;

        assert_equal(reinterpret_cast<const real*>(&u), u.data()) ;

        // streams
        {
            quat a = rand_quat() ;
            quat b ;

            std::ostringstream out ;
            out.precision(std::numeric_limits<real>::digits10 + 1) ;

            out << a ;
            std::istringstream in(out.str()) ;
            in >> b ;

            assert_close(a, b) ;
        }
        {
            pure a = rand_pure() ;
            pure b ;

            std::ostringstream out ;
            out.precision(std::numeric_limits<real>::digits10 + 1) ;

            out << a ;
            std::istringstream in(out.str()) ;
            in >> b ;

            assert_close(a, b) ;
        }
    }
}



