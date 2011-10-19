
#ifndef esve_geom_dimn_specs_Polar_Annulus_hxx
#define esve_geom_dimn_specs_Polar_Annulus_hxx

#include <esve/geom/dimn/selectors.hxx>
#include <esve/math/constants.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
class Polar_Annulus
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;

    m_real m_inner_radius ;
    m_real m_outer_radius ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef selectors::category::regular category_selector ;
    typedef selectors::topology::cylinder_wrap_height topology_selector ;

    Polar_Annulus( real inner_radius,
                   real outer_radius )
        : m_inner_radius(inner_radius),
          m_outer_radius(outer_radius) { }

    // compiler writes memberwise copy and assign

    real inner_radius() const
    {
        return m_inner_radius ;
    }

    void inner_radius( real a )
    {
        m_inner_radius = a ;
    }

    real outer_radius() const
    {
        return m_outer_radius ;
    }

    void outer_radius( real a )
    {
        m_outer_radius = a ;
    }

    complex domain( const complex & unit_square ) const
    {
        return
            (
             (m_inner_radius + real(0.001))
             +
             unit_square.real()*(m_outer_radius - m_inner_radius)
             )
            *
            exp(real(math::constants::TWO_PI)
                *
                complex(0, 1)*unit_square.imag()) ;
    }
} ;

}}}} // namespace esve::geom::dimn::specs

#endif

