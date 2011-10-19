
#ifndef esve_geom_dimn_specs_Unit_Square_hxx
#define esve_geom_dimn_specs_Unit_Square_hxx

#include <esve/geom/dimn/selectors.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
class Unit_Square
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef selectors::category::regular category_selector ;
    typedef selectors::topology::plane topology_selector ;

    Unit_Square() { }

    // compiler writes memberwise copy and assign

    complex domain( const complex & unit_square ) const
    {
        return unit_square ;
    }
} ;

}}}} // namespace esve::geom::dimn::specs

#endif

