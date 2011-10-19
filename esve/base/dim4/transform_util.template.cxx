
#include <esve/base/dim4/Transform.hxx>
#include <esve/math/moebius.hxx>
#include <cmath>

namespace esve { namespace base { namespace dim4 {

namespace transform_util {

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator >
void
apply_transform( const math::quat<real> & a_,
                 const math::quat<real> & b_,
                 const math::quat<real> & c_,
                 const math::quat<real> & d_,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin )
{
    typedef math::quat<real> quat ;

    const quat a = a_ ;
    const quat b = b_ ;
    const quat c = c_ ;
    const quat d = d_ ;

    Input_Iterator z = input_begin ;
    Output_Iterator fz = output_begin ;

    if( c == real(0) )
    {
        const quat inv_d = inv(d) ;

        if( b == real(0) )
        {
            for( ; z != input_end ; ++z, ++fz )
            {
                *fz = a*(*z)*inv_d ;
            }
        }
        else
        {
            for( ; z != input_end ; ++z, ++fz )
            {
                *fz = (a*(*z) + b)*inv_d ;
            }
        }
    }
    else
    {
        for( ; z != input_end ; ++z, ++fz )
        {
            *fz = math::moebius::moebius(a, b, c, d, *z) ;
        }
    }
}

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator,
          typename Function >
void
apply_transform( const math::quat<real> & a_,
                 const math::quat<real> & b_,
                 const math::quat<real> & c_,
                 const math::quat<real> & d_,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin,
                 Function & function )
{
    typedef math::quat<real> quat ;

    const quat a = a_ ;
    const quat b = b_ ;
    const quat c = c_ ;
    const quat d = d_ ;

    Input_Iterator z = input_begin ;
    Output_Iterator fz = output_begin ;

    if( c == real(0) )
    {
        const quat inv_d = inv(d) ;

        if( b == real(0) )
        {
            for( ; z != input_end ; ++z, ++fz )
            {
                *fz = a*(*z)*inv_d ;
                function(*fz) ;
            }
        }
        else
        {
            for( ; z != input_end ; ++z, ++fz )
            {
                *fz = (a*(*z) + b)*inv_d ;
                function(*fz) ;
            }
        }
    }
    else
    {
        for( ; z != input_end ; ++z, ++fz )
        {
            *fz = math::moebius::moebius(a, b, c, d, *z) ;
            function(*fz) ;
        }
    }
}

} // namespace transform_util

}}} // namespace esve::base::dim4

