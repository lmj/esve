
#include <esve/components/dim4/Report_Min_Z.hxx>
#include <esve/engine/dim4/Transform.hxx>
#include <esve/engine/dim4/transform_util.hxx>
#include <limits>

namespace esve { namespace components { namespace dim4 {

using types::real ;

template< typename T_Frame >
Report_Min_Z<T_Frame>::
Private::
Private()
    : initial_min_z(std::numeric_limits<real>::max()),
      min_z(0)
{
}

template< typename T_Frame >
Report_Min_Z<T_Frame>::
Report_Min_Z()
    : T_Frame(),
      m()
{
}

template< typename T_Frame >
template< typename T_Arg >
Report_Min_Z<T_Frame>::
Report_Min_Z( T_Arg & arg )
    : T_Frame(arg),
      m()
{
}

template< typename T_Frame >
template< typename T_Arg >
Report_Min_Z<T_Frame>::
Report_Min_Z( const T_Arg & arg )
    : T_Frame(arg),
      m()
{
}

template< typename T_Frame >
Report_Min_Z<T_Frame>::
~Report_Min_Z()
{
}

template< typename T_Frame >
void
Report_Min_Z<T_Frame>::
apply_transform()
{
    m_Find_Min find_min(m.initial_min_z) ;

    engine::dim4::transform_util::apply_transform(
        this->world_transform(),
        this->points_begin(),
        this->points_end(),
        this->transformed_points_begin(),
        find_min) ;

    m.min_z = find_min.min_z ;
}

}}} // namespace esve::components::dim4
