
#include <esve/engine/dim4/Make_Frame.hxx>
#include <esve/engine/dim4/transform_util.hxx>

namespace esve { namespace engine { namespace dim4 {

template< typename T_Target, typename T_Frame >
Make_Frame<T_Target, T_Frame>::
Private::
Private()
    : initialized(false),
      last_world_transform()
{
}

template< typename T_Target, typename T_Frame >
Make_Frame<T_Target, T_Frame>::
Make_Frame()
    : Compute_Receiver(),
      T_Frame(),
      T_Target(),
      m()
{
}

template< typename T_Target, typename T_Frame >
template< typename T_Arg >
Make_Frame<T_Target, T_Frame>::
Make_Frame( T_Arg & args )
    : Compute_Receiver(),
      T_Frame(),
      T_Target(args),
      m()
{
}

template< typename T_Target, typename T_Frame >
template< typename T_Arg >
Make_Frame<T_Target, T_Frame>::
Make_Frame( const T_Arg & args )
    : Compute_Receiver(),
      T_Frame(),
      T_Target(args),
      m()
{
}

template< typename T_Target, typename T_Frame >
Make_Frame<T_Target, T_Frame>::
~Make_Frame()
{
}

template< typename T_Target, typename T_Frame >
void
Make_Frame<T_Target, T_Frame>::
pretransform()
{
    T_Target::pretransform() ;
}

template< typename T_Target, typename T_Frame >
void
Make_Frame<T_Target, T_Frame>::
posttransform()
{
    T_Target::posttransform() ;
}

template< typename T_Target, typename T_Frame >
bool
Make_Frame<T_Target, T_Frame>::
changed() const
{
    return T_Target::changed() ;
}

template< typename T_Target, typename T_Frame >
void
Make_Frame<T_Target, T_Frame>::
compute()
{
    if( !m.initialized ||
        changed() ||
        T_Frame::world_transform() != m.last_world_transform )
    {
        pretransform() ;
        apply_transform() ;
        posttransform() ;

        m.initialized = true ;
        m.last_world_transform = T_Frame::world_transform() ;
    }
}

template< typename T_Target, typename T_Frame >
void
Make_Frame<T_Target, T_Frame>::
apply_transform()
{
    engine::dim4::transform_util::apply_transform(
        T_Frame::world_transform(),
        T_Target::points_begin(),
        T_Target::points_end(),
        T_Target::transformed_points_begin()) ;
}

}}} // namespace esve::engine::dim4
