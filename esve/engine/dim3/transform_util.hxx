
#ifndef esve_engine_dim3_transform_util_hxx
#define esve_engine_dim3_transform_util_hxx

#include <esve/engine/dim3/Transform.hxx>
#include <esve/base/dim3/transform_util.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace engine { namespace dim3 {

namespace transform_util {

inline
void
build_matrix( const Transform & transform,
              types::real matrix[16] )
{
    base::dim3::transform_util::build_matrix(
        transform.rotation(),
        transform.translation(),
        transform.scaling(),
        matrix) ;
}

inline
types::pure
apply_transform( const Transform & transform,
                 const types::pure & z )
{
    return
    base::dim3::transform_util::apply_transform(
        transform.rotation(),
        transform.translation(),
        transform.scaling(),
        z) ;
}

template< typename T_Input_Iterator,
          typename T_Output_Iterator >
inline
void
apply_transform( const Transform & transform,
                 T_Input_Iterator input_begin,
                 T_Input_Iterator input_end,
                 T_Output_Iterator output_begin )
{
    base::dim3::transform_util::apply_transform(
        transform.rotation(),
        transform.translation(),
        transform.scaling(),
        input_begin,
        input_end,
        output_begin) ;
}

} // namespace transform_util

}}} // namespace esve::engine::dim3

#endif
