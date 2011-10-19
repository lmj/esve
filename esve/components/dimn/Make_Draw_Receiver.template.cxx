
#include <esve/components/dimn/Make_Draw_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

template< typename T_Target >
Make_Draw_Receiver<T_Target>::
Make_Draw_Receiver()
    : Draw_Receiver(),
      T_Target()
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Draw_Receiver<T_Target>::
Make_Draw_Receiver( T_Arg & arg )
    : Draw_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Draw_Receiver<T_Target>::
Make_Draw_Receiver( const T_Arg & arg )
    : Draw_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
Make_Draw_Receiver<T_Target>::
~Make_Draw_Receiver()
{
}

template< typename T_Target >
void
Make_Draw_Receiver<T_Target>::
draw()
{
    T_Target::draw() ;
}

}}} // namespace esve::components::dimn
