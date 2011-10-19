
#ifndef esve_base_dim3_transform_util_hxx
#define esve_base_dim3_transform_util_hxx

#include <esve/math/quat.hxx>

namespace esve { namespace base { namespace dim3 {

namespace transform_util {

template< typename real >
void
build_matrix( const math::quat<real> & rotation,
              const math::pure<real> & translation,
              real scaling,
              real matrix[16] ) ;

template< typename real >
math::pure<real>
apply_transform( const math::quat<real> & rotation,
                 const math::pure<real> & translation,
                 real scaling,
                 const math::pure<real> & z ) ;

template< typename real,
          typename Input_Iterator,
          typename Output_Iterator >
void
apply_transform( const math::quat<real> & rotation,
                 const math::pure<real> & translation,
                 real scaling,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin ) ;

} // namespace transform_util

}}} // namespace esve::base::dim3

#include <esve/base/dim3/transform_util.template.cxx>

#endif

