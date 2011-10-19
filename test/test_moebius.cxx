//
// A complete or near-complete test of matrix_2h.hxx and moebius.hxx.
//

#include "common.hxx"
#include <esve/math/matrix_2h.hxx>
#include <esve/math/moebius.hxx>
#include <sstream>
#include <limits>

using esve::math::moebius::moebius ;

typedef esve::math::matrix_2h<quat> mat ;

mat rand_mat()
{
    return mat(rand_quat(),
               rand_quat(),
               rand_quat(),
               rand_quat()) ;
}

bool within( const mat & m1, const mat & m2, const real epsilon )
{
    return
        within(m1.a(), m2.a(), epsilon) &&
        within(m1.b(), m2.b(), epsilon) &&
        within(m1.c(), m2.c(), epsilon) &&
        within(m1.d(), m2.d(), epsilon) ;
}

void test_moebius()
{
    for( int n = 0 ; n != TRIALS ; ++n )
    {
        const quat a = rand_quat() ;
        const quat b = rand_quat() ;
        const quat c = rand_quat() ;
        const quat d = rand_quat() ;
        const quat t = rand_quat() ;

        const mat m1 = mat(a, b, c, d) ;
        const mat m2 = rand_mat() ;

        //
        // (a*t + b)*inv(c*t + d)
        //
        //template< typename T_quat >
        //    T_quat moebius( const T_quat & a,
        //                    const T_quat & b,
        //                    const T_quat & c,
        //                    const T_quat & d,
        //                    const T_quat & t )
        //    }

        assert_close(moebius(a, b, c, d, t),
                     (a*t + b)*inv(c*t + d)) ;

        //matrix_2h() ;
        assert_equal(mat(), mat(quat(1), quat(0), quat(0), quat(1))) ;

        ////
        //// [ a  b ]
        //// [ c  d ]
        ////
        //matrix_2h( const quat & a, const quat & b,
        //           const quat & c, const quat & d ) ;
        {
            mat m = mat(a, b, c, d) ;
            assert_equal(m, mat(m.a(), m.b(), m.c(), m.d())) ;
        }

        // skip:
        //const quat & a() const { return ma ; }
        //const quat & b() const { return mb ; }
        //const quat & c() const { return mc ; }
        //const quat & d() const { return md ; }
        //void a( const quat & a ) { ma = a ; }
        //void b( const quat & b ) { mb = b ; }
        //void c( const quat & c ) { mc = c ; }
        //void d( const quat & d ) { md = d ; }
        // compiler writes memberwise copy and assign

        //// *this := 1
        //void identity() ;
        {
            mat m = mat(a, b, c, d) ;
            m.identity() ;
            assert_equal(m, mat()) ;
        }

        //// *this := left * (*this)
        //void left_act( const matrix_2h & left ) ;
        {
            mat res = m2 ;
            res.left_act(m1) ;

            assert_close(res,
                         mat(m1.a()*m2.a() + m1.b()*m2.c(),
                             m1.a()*m2.b() + m1.b()*m2.d(),
                             m1.c()*m2.a() + m1.d()*m2.c(),
                             m1.c()*m2.b() + m1.d()*m2.d())) ;
        }

        //// *this := (*this) * right
        //void right_act( const matrix_2h & right ) ;
        {
            mat res = m1 ;
            res.right_act(m2) ;

            assert_close(res,
                         mat(m1.a()*m2.a() + m1.b()*m2.c(),
                             m1.a()*m2.b() + m1.b()*m2.d(),
                             m1.c()*m2.a() + m1.d()*m2.c(),
                             m1.c()*m2.b() + m1.d()*m2.d())) ;
        }

        //// *this := (*this)^(-1)
        //void invert() ;
        {
            mat m1_inv = m1 ;
            m1_inv.invert() ;
            {
                mat res = m1 ;
                res.left_act(m1_inv) ;
                assert_close(res, mat()) ;

                res = m1 ;
                res.right_act(m1_inv) ;
                assert_close(res, mat()) ;
            }


            const real nm =
                norm(a*d)
                +
                norm(b*c)
                -
                real(2)*dot(a*conj(c), b*conj(d)) ;

            assert_close(m1_inv,
                         mat((norm(d)*conj(a) - conj(c)*d*conj(b))/nm,
                             (norm(b)*conj(c) - conj(a)*b*conj(d))/nm,
                             (norm(c)*conj(b) - conj(d)*c*conj(a))/nm,
                             (norm(a)*conj(d) - conj(b)*a*conj(c))/nm)) ;
        }

        //// *this := transpose(conj(*this))
        //void adjoint() ;
        {
            mat res = m1 ;
            res.adjoint() ;
            assert_equal(res, mat(conj(a), conj(c), conj(b), conj(d))) ;
        }

        //// a*d - b*c
        //quat det() const ;
        assert_close(m1.det(), a*d - b*c) ;

        //// det((*this)*adjoint(*this))
        //scalar norm() const ;
        assert_close(m1.norm(),
                     norm(a*d)
                     +
                     norm(b*c)
                     -
                     real(2)*dot(a*conj(c), b*conj(d))) ;
        {
            mat res = m1 ;
            res.adjoint() ;
            res.right_act(m1) ;
            assert_close(res.det(), m1.norm()) ;
        }
        {
            mat res = m1 ;
            res.adjoint() ;
            res.left_act(m1) ;
            assert_close(res.det(), m1.norm()) ;
        }

        //// elementwise compare
        //bool operator==( const matrix_2h & ) const ;
        //bool operator!=( const matrix_2h & ) const ;

        assert_equal((m1 == mat(m1.a(), m1.b(), m1.c(), m1.d())),
                     true) ;
        assert_equal((m1 != mat(-m1.a(), m1.b(), m1.c(), m1.d())),
                     true) ;

        // streams
        {
            mat a = rand_mat() ;
            mat b ;

            std::ostringstream out ;
            out.precision(std::numeric_limits<real>::digits10 + 1) ;

            out << a ;
            std::istringstream in(out.str()) ;
            in >> b ;

            assert_close(a, b) ;
        }
    }
}



