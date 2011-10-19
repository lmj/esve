
#include <esve/components/dimn/Make_Update_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

template< typename T_Target >
Make_Update_Receiver<T_Target>::
Make_Update_Receiver()
    : Update_Receiver(),
      T_Target()
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Update_Receiver<T_Target>::
Make_Update_Receiver( T_Arg & arg )
    : Update_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Update_Receiver<T_Target>::
Make_Update_Receiver( const T_Arg & arg )
    : Update_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
Make_Update_Receiver<T_Target>::
~Make_Update_Receiver()
{
}

template< typename T_Target >
void
Make_Update_Receiver<T_Target>::
update( double dt )
{
    T_Target::update(dt) ;
}

template< typename T_Target >
void
Make_Update_Receiver<T_Target>::
update()
{
    T_Target::update() ;
}

}}} // namespace esve::components::dimn
