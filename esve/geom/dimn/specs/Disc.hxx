
#ifndef esve_geom_dimn_specs_Disc_hxx
#define esve_geom_dimn_specs_Disc_hxx

#include <esve/geom/dimn/selectors.hxx>
#include <esve/geom/dimn/Circle.hxx>
#include <esve/geom/dimn/slicers/Disc.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex >
class Disc
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;
    typedef Circle<m_complex> m_Circle ;
    typedef slicers::Disc<m_complex> m_Slicer ;

    // data
    m_Circle m_disc ;

    // slicer
    m_Slicer m_slicer ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef m_Circle Circle ;
    typedef selectors::category::sliced category_selector ;
    typedef selectors::topology::plane topology_selector ;

    explicit Disc( const Circle & ) ;

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
            complex(real(0.001), real(0.001))
            +
            m_disc.radius()
            *
            (real(2)*unit_square - complex(1, 1)) ;
    }

    bool domain_clip( const complex & unit_square,
                      const complex & domain ) const
    {
        return m_slicer.domain_clip(unit_square, domain) ;
    }

    complex domain_snap( const complex & unit_square,
                         const complex & domain ) const
    {
        return m_slicer.domain_snap(unit_square, domain) ;
    }

protected:
    typedef m_Slicer Slicer ;

    const Slicer & slicer() const
    {
        return m_slicer ;
    }
} ;

}}}} // namespace esve::geom::dimn::specs

#include <esve/geom/dimn/specs/Disc.template.cxx>

#endif

