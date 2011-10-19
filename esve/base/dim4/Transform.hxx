
#ifndef esve_base_dim4_Transform_hxx
#define esve_base_dim4_Transform_hxx

#include <esve/math/quat.hxx>
#include <esve/math/matrix_2h.hxx>

namespace esve { namespace base { namespace dim4 {

template< typename T_real >
class Transform
{
private:
    typedef math::matrix_2h< math::quat<T_real> > m_Matrix ;

    void m_act( const Transform & a, const Transform & b ) ;

    m_Matrix m ;

public:
    typedef T_real real ;
    typedef math::pure<real> pure ;
    typedef math::quat<real> quat ;

    static const Transform IDENTITY ;

    Transform()
        : m() { }

    Transform( const quat & a,
               const quat & b,
               const quat & c,
               const quat & d )
        : m(a, b, c, d) { }

    const quat & a() const
    {
        return m.a() ;
    }

    const quat & b() const
    {
        return m.b() ;
    }

    const quat & c() const
    {
        return m.c() ;
    }

    const quat & d() const
    {
        return m.d() ;
    }

    void a( const quat & a )
    {
        m.a(a) ;
    }

    void b( const quat & b )
    {
        m.b(b) ;
    }

    void c( const quat & c )
    {
        m.c(c) ;
    }

    void d( const quat & d )
    {
        m.d(d) ;
    }

    void identity()
    {
        m.identity() ;
    }

    void invert()
    {
        m.invert() ;
    }

    bool operator==( const Transform & a ) const
    {
        return m.operator==(a.m) ;
    }

    bool operator!=( const Transform & a ) const
    {
        return m.operator!=(a.m) ;
    }

    void left_act( const Transform & a )
    {
        m.left_act(a.m) ;
    }

    void right_act( const Transform & a )
    {
        m.right_act(a.m) ;
    }

    void act( const Transform & a,
              const Transform & b = IDENTITY ) ;

    void rotate( real alpha,
                 real beta,
                 const quat & r,
                 const quat & s,
                 const Transform & basis = IDENTITY ) ;

    void rotate( real alpha,
                 real beta,
                 const pure & u,
                 const Transform & basis = IDENTITY ) ;

    void translate( const quat & r,
                    const Transform & basis = IDENTITY ) ;

    void invertate( const quat & r,
                    const Transform & basis = IDENTITY ) ;

    void scalate( real gamma,
                  const Transform & basis = IDENTITY ) ;

    void normalize() ;
} ;

}}} // namespace esve::base::dim4

#include <esve/base/dim4/Transform.template.cxx>

#endif

