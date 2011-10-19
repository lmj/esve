
#include <esve/base/dim3/transform_util.hxx>

namespace esve { namespace base { namespace dim3 {

namespace transform_util {

template< typename real >
void
build_matrix( const math::quat<real> & r,
              const math::pure<real> & t,
              real s,
              real matrix[16] )
{
    const real x2 = r.x() + r.x() ;
    const real y2 = r.y() + r.y() ;
    const real z2 = r.z() + r.z() ;
    const real xx = r.x()*x2 ;
    const real xy = r.x()*y2 ;
    const real xz = r.x()*z2 ;
    const real yy = r.y()*y2 ;
    const real yz = r.y()*z2 ;
    const real zz = r.z()*z2 ;
    const real wx = r.w()*x2 ;
    const real wy = r.w()*y2 ;
    const real wz = r.w()*z2 ;

    matrix[0] =  real(1) - (yy + zz) ;
    matrix[1] =  xy + wz ;
    matrix[2] =  xz - wy ;
    matrix[3] =  real(0) ;
    matrix[4] =  xy - wz ;
    matrix[5] =  real(1) - (xx + zz) ;
    matrix[6] =  yz + wx ;
    matrix[7] =  real(0) ;
    matrix[8] =  xz + wy ;
    matrix[9] =  yz - wx ;
    matrix[10] = real(1) - (xx + yy) ;
    matrix[11] = real(0) ;
    matrix[12] = t.x() ;
    matrix[13] = t.y() ;
    matrix[14] = t.z() ;
    matrix[15] = real(1)/s ;
}

template< typename real >
math::pure<real>
apply_transform( const math::quat<real> & r,
                 const math::pure<real> & t,
                 real s,
                 const math::pure<real> & z )
{
    return s*(purepart(r*z*conj(r)) + t) ;
}

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator >
void
apply_transform( const math::quat<real> & r,
                 const math::pure<real> & t,
                 real s,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin )
{
    const math::quat<real> conj_r = conj(r) ;

    Input_Iterator z = input_begin ;
    Output_Iterator fz = output_begin ;

    for( ; z != input_end ; ++z, ++fz )
    {
        *fz = s*(purepart(r*(*z)*conj_r) + t) ;
    }
}

} // namespace transform_util

}}} // namespace esve::base::dim3

