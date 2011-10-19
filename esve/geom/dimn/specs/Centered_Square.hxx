
#ifndef esve_geom_dimn_specs_Centered_Square_hxx
#define esve_geom_dimn_specs_Centered_Square_hxx

#include <esve/geom/dimn/selectors.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
class Centered_Square
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;

    m_real m_radius ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef selectors::category::regular category_selector ;
    typedef selectors::topology::plane topology_selector ;

    explicit Centered_Square( real radius )
        : m_radius(radius) { }

    // compiler writes memberwise copy and assign

    real radius() const
    {
        return m_radius ;
    }

    void radius( real a )
    {
        m_radius = a ;
    }

    complex domain( const complex & unit_square ) const
    {
        return m_radius*(real(2)*unit_square - complex(1, 1)) ;
    }
} ;

}}}} // namespace esve::geom::dimn::specs

#endif

