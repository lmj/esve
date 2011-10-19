
#ifndef esve_engine_dim4_transform_util_hxx
#define esve_engine_dim4_transform_util_hxx

#include <esve/engine/dim4/Transform.hxx>
#include <esve/base/dim4/transform_util.hxx>
#include <esve/types/quat.hxx>

namespace esve { namespace engine { namespace dim4 {

namespace transform_util {

inline
types::quat
apply_transform( const Transform & transform,
                 const types::quat & z )
{
    return base::dim4::transform_util::apply_transform(
               transform.a(),
               transform.b(),
               transform.c(),
               transform.d(),
               z) ;
}

template< typename Input_Iterator,
          typename Output_Iterator >
inline
void
apply_transform( const Transform & transform,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin )
{
    base::dim4::transform_util::apply_transform(
        transform.a(),
        transform.b(),
        transform.c(),
        transform.d(),
        input_begin,
        input_end,
        output_begin) ;
}

template< typename Input_Iterator,
          typename Output_Iterator,
          typename Function >
inline
void
apply_transform( const Transform & transform,
                 Input_Iterator input_begin,
                 Input_Iterator input_end,
                 Output_Iterator output_begin,
                 Function & function )
{
    base::dim4::transform_util::apply_transform(
        transform.a(),
        transform.b(),
        transform.c(),
        transform.d(),
        input_begin,
        input_end,
        output_begin,
        function) ;
}

} // namespace transform_util

}}} // namespace esve::engine::dim4

#endif

