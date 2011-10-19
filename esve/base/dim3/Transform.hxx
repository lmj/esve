
#ifndef esve_base_dim3_Transform_hxx
#define esve_base_dim3_Transform_hxx

#include <esve/math/quat.hxx>

namespace esve { namespace base { namespace dim3 {

template< typename T_real >
class Transform
{
private:
    typedef T_real m_real ;
    typedef math::pure<m_real> m_pure ;
    typedef math::quat<m_real> m_quat ;

    m_quat mr ;
    m_pure mt ;
    m_real ms ;

public:
    typedef m_real real ;
    typedef m_pure pure ;
    typedef m_quat quat ;

    static const Transform IDENTITY ;

    Transform()
        : mr(1),
          mt(),
          ms(1) { }

    Transform( const quat & rotation,
               const pure & translation = pure(),
               real scaling = real(1) )
        : mr(rotation),
          mt(translation),
          ms(scaling) { }

    // compiler writes memberwise copy and assign

    const quat & rotation() const
    {
        return mr ;
    }

    void rotation( const quat & a )
    {
        mr = a ;
    }

    const pure & translation() const
    {
        return mt ;
    }

    void translation( const pure & a )
    {
        mt = a ;
    }

    real scaling() const
    {
        return ms ;
    }

    void scaling( real a )
    {
        ms = a ;
    }

    void left_act( const Transform & a ) ;

    void right_act( const Transform & a ) ;

    void act( const Transform & action, const Transform & basis ) ;

    void rotate( real angle,
                 const pure & axis,
                 const Transform & basis = IDENTITY ) ;

    void translate( const pure & dt,
                    const Transform & basis = IDENTITY ) ;

    void scalate( real ds,
                  const Transform & basis = IDENTITY ) ;

    void identity()
    {
        mr = quat(1) ;
        mt = pure() ;
        ms = real(1) ;
    }

    void invert() ;

    void normalize()
    {
        mr /= abs(mr) ;
        ms = real(1) ;
    }

    bool operator==( const Transform & a ) const
    {
        return
            mr == a.mr &&
            mt == a.mt &&
            ms == a.ms ;
    }

    bool operator!=( const Transform & a ) const
    {
        return
            mr != a.mr ||
            mt != a.mt ||
            ms != a.ms ;
    }
} ;

}}} // namespace esve::base::dim3

#include <esve/base/dim3/Transform.template.cxx>

#endif

