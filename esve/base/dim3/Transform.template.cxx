
#include <esve/base/dim3/Transform.hxx>
#include <cmath>

namespace esve { namespace base { namespace dim3 {

template< typename T_real >
const
Transform<T_real>
Transform<T_real>::
IDENTITY ;

template< typename T_real >
void
Transform<T_real>::
left_act( const Transform & a )
{
    mt = purepart(a.mr*mt*conj(a.mr)) + (real(1)/ms)*a.mt ;
    mr = a.mr*mr ;
    ms = a.ms*ms ;
}

template< typename T_real >
void
Transform<T_real>::
right_act( const Transform & a )
{
    mt = purepart(mr*a.mt*conj(mr)) + (real(1)/a.ms)*mt ;
    mr = mr*a.mr ;
    ms = ms*a.ms ;
}

template< typename T_real >
void
Transform<T_real>::
act( const Transform & action, const Transform & basis )
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
rotate( real angle,
        const pure & axis,
        const Transform & basis )
{
    const real theta = real(0.5)*angle ;
    const quat dr = quat(std::cos(theta), axis*std::sin(theta)) ;

    if( &basis == &IDENTITY )
    {
        mt = purepart(dr*mt*conj(dr)) ;
        mr = dr*mr ;
    }
    else if( &basis == this )
    {
        mr = mr*dr ;
    }
    else
    {
        const Transform action(dr) ;
        act(action, basis) ;
    }
}

template< typename T_real >
void
Transform<T_real>::
translate( const pure & dt, const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        mt = mt + (real(1)/ms)*dt ;
    }
    else if( &basis == this )
    {
        mt = purepart(mr*dt*conj(mr)) + mt ;
    }
    else
    {
        const Transform action(quat(1), dt) ;
        act(action, basis) ;
    }
}

template< typename T_real >
void
Transform<T_real>::
scalate( real ds,
         const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        ms *= ds ;
    }
    else if( &basis == this )
    {
        mt /= ds ;
        ms *= ds ;
    }
    else
    {
        const Transform action(quat(1), pure(), ds) ;
        act(action, basis) ;
    }
}

template< typename T_real >
void
Transform<T_real>::
invert()
{
    mt = -purepart(ms*conj(mr)*mt*mr) ;
    mr = conj(mr) ;
    ms = 1/ms ;
}

}}} // namespace esve::base::dim3
