
#ifndef esve_geom_dimn_specs_Polar_Disc_hxx
#define esve_geom_dimn_specs_Polar_Disc_hxx

#include <esve/geom/dimn/selectors.hxx>
#include <esve/geom/dimn/Circle.hxx>
#include <esve/math/constants.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
class Polar_Disc
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;
    typedef Circle<m_complex> m_Circle ;

    m_Circle m_disc ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef m_Circle Circle ;
    typedef selectors::category::regular category_selector ;
    typedef selectors::topology::cylinder_wrap_height topology_selector ;

    explicit Polar_Disc( const Circle & disc )
        : m_disc(disc) { }

    // compiler writes memberwise copy and assign

    const Circle & disc() const
    {
        return m_disc ;
    }

    void disc( const Circle & a )
    {
        m_disc = a ;
    }

    complex domain( const complex & unit_square ) const
    {
        return
            m_disc.center()
            +
            (m_disc.radius()*unit_square.real() + real(0.001))
            *
            exp(real(math::constants::TWO_PI)
                *
                complex(0, 1)*unit_square.imag()) ;
    }
} ;

}}}} // namespace esve::geom::dimn::specs

#endif

