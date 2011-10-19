
#include <esve/base/dim4/Transform.hxx>
#include <esve/math/moebius.hxx>
#include <cmath>

namespace esve { namespace base { namespace dim4 {

template< typename T_real >
const
Transform<T_real>
Transform<T_real>::
IDENTITY ;

template< typename T_real >
void
Transform<T_real>::
normalize()
{
    m.a(m.a()/abs(m.a())) ;
    m.c(quat(0)) ;
    m.d(m.d()/abs(m.d())) ;
}

template< typename T_real >
void
Transform<T_real>::
act( const Transform & action,
     const Transform & basis )
{
    Transform inv_basis = basis ;
    inv_basis.invert() ;
    left_act(inv_basis) ;
    left_act(action) ;
    left_act(basis) ;
}

template< typename T_real >
void
Transform<T_real>::
m_act( const Transform & action,
       const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        left_act(action) ;
    }
    else if( &basis == this )
    {
        right_act(action) ;
    }
    else
    {
        act(action, basis) ;
    }
}

template< typename T_real >
void
Transform<T_real>::
rotate( real alpha,
        real beta,
        const quat & r,
        const quat & s,
        const Transform & basis )
{
    const real rps = real(0.5)*(alpha + beta) ;
    const real rms = real(0.5)*(alpha - beta) ;

    Transform dr =
        Transform(quat(std::cos(rps), cross(r, s)*std::sin(rps)),
                  quat(real(0)),
                  quat(real(0)),
                  quat(std::cos(rms), cross(conj(r), conj(s))*std::sin(rms))) ;

    m_act(dr, basis) ;
}

template< typename T_real >
void
Transform<T_real>::
rotate( real alpha,
        real beta,
        const pure & u,
        const Transform & basis )
{
    const real rps = real(0.5)*(alpha + beta) ;
    const real rms = real(0.5)*(alpha - beta) ;

    // r == 1
    // s == u
    Transform dr =
        Transform(quat(std::cos(rps), u*std::sin(rps)),
                  quat(real(0)),
                  quat(real(0)),
                  quat(std::cos(rms), -u*std::sin(rms))) ;

    m_act(dr, basis) ;
}

template< typename T_real >
void
Transform<T_real>::
translate( const quat & r,
           const Transform & basis )
{
    Transform action =
        Transform(quat(1),
                  r,
                  quat(0),
                  quat(1)) ;

    m_act(action, basis) ;
}

template< typename T_real >
void
Transform<T_real>::
invertate( const quat & r,
           const Transform & basis )
{
    Transform action =
        Transform(quat(1),
                  quat(0),
                  r,
                  quat(1)) ;

    m_act(action, basis) ;
}

template< typename T_real >
void
Transform<T_real>::
scalate( real gamma,
         const Transform & basis )
{
    Transform action =
        Transform(quat(gamma),
                  quat(0),
                  quat(0),
                  quat(1)) ;

    m_act(action, basis) ;
}

}}} // namespace esve::base::dim4
