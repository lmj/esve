
#include <esve/engine/dim3/Make_Geom.hxx>

namespace esve { namespace engine { namespace dim3 {

template< typename T_Target >
Make_Geom<T_Target>::
Make_Geom()
    : super()
{
}

template< typename T_Target >
Make_Geom<T_Target>::
~Make_Geom()
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Geom<T_Target>::
Make_Geom( T_Arg & arg )
    : super(arg)
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Geom<T_Target>::
Make_Geom( const T_Arg & arg )
    : super(arg)
{
}

template< typename T_Target >
void
Make_Geom<T_Target>::
compute()
{
    T_Target::compute() ;
}

}}} // namespace esve::engine::dim3
