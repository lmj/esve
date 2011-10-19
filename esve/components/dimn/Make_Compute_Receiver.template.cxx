
#include <esve/components/dimn/Make_Compute_Receiver.hxx>

namespace esve { namespace components { namespace dimn {

template< typename T_Target >
Make_Compute_Receiver<T_Target>::
Make_Compute_Receiver()
    : Compute_Receiver(),
      T_Target()
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Compute_Receiver<T_Target>::
Make_Compute_Receiver( T_Arg & arg )
    : Compute_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
template< typename T_Arg >
Make_Compute_Receiver<T_Target>::
Make_Compute_Receiver( const T_Arg & arg )
    : Compute_Receiver(),
      T_Target(arg)
{
}

template< typename T_Target >
Make_Compute_Receiver<T_Target>::
~Make_Compute_Receiver()
{
}

template< typename T_Target >
void
Make_Compute_Receiver<T_Target>::
compute()
{
    T_Target::compute() ;
}

}}} // namespace esve::components::dimn
