
#ifndef esve_base_dim4_transform_util_hxx
#define esve_base_dim4_transform_util_hxx

#include <esve/math/quat.hxx>
#include <esve/math/moebius.hxx>

namespace esve { namespace base { namespace dim4 {

namespace transform_util {

template< typename real >
inline
math::quat<real>
apply_transform( const math::quat<real> & a,
                 const math::quat<real> & b,
                 const math::quat<real> & c,
                 const math::quat<real> & d,
                 const math::quat<real> & z )
{
    return math::moebius::moebius(a, b, c, d, z) ;
}

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator >
void
apply_transform( const math::quat<real> & a,
                 const math::quat<real> & b,
                 const math::quat<real> & c,
                 const math::quat<real> & d,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin ) ;

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator,
          typename Function >
void
apply_transform( const math::quat<real> & a,
                 const math::quat<real> & b,
                 const math::quat<real> & c,
                 const math::quat<real> & d,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin,
                 Function & function ) ;

} // namespace transform_util

}}} // namespace esve::base::dim4

#include <esve/base/dim4/transform_util.template.cxx>

#endif

