
#include <esve/engine/dim4/Make_Geom.hxx>

namespace esve { namespace engine { namespace dim4 {

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
draw()
{
    T_Target::draw() ;
}

}}} // namespace esve::engine::dim4
