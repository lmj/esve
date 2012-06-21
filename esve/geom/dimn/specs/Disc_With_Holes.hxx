
#ifndef esve_geom_dimn_specs_Disc_With_Holes_hxx
#define esve_geom_dimn_specs_Disc_With_Holes_hxx

#include <esve/geom/dimn/specs/Disc.hxx>
#include <esve/geom/dimn/Slicer_Union.hxx>
#include <esve/geom/dimn/slicers/Hole.hxx>

namespace esve { namespace geom { namespace dimn { namespace specs {

template< typename T_complex,
          unsigned int num_holes >
class Disc_With_Holes
    : protected Disc_With_Holes<T_complex, num_holes - 1>
{
private:
    typedef Disc_With_Holes<T_complex, num_holes - 1> m_Base ;
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;
    typedef geom::dimn::Circle<m_complex> m_Circle ;
    typedef slicers::Hole<m_complex> m_Hole_Slicer ;
    typedef Slicer_Union<typename m_Base::Slicer, m_Hole_Slicer> m_Slicer ;

    // data
    m_Circle m_hole ;

    // slicers
    m_Hole_Slicer m_hole_slicer ;
    m_Slicer m_slicer ;

public:
    typedef m_complex complex ;
    typedef m_real real ;
    typedef m_Circle Circle ;
    typedef selectors::category::sliced category_selector ;
    typedef selectors::topology::plane topology_selector ;

    explicit Disc_With_Holes( const Circle & disc ) ;

    // compiler writes memberwise copy and assign

    using m_Base::disc ;
    using m_Base::domain ;

    template< unsigned int index >
    const Circle & hole() const
    {
        return Disc_With_Holes<T_complex, index + 1>::own_hole() ;
    }

    template< unsigned int index >
    void hole( const Circle & a )
    {
        Disc_With_Holes<T_complex, index + 1>::own_hole(a) ;
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

    const Circle & own_hole() const
    {
        return m_hole ;
    }

    void own_hole( const Circle & hole )
    {
        m_hole = hole ;
    }
} ;

template< typename T_complex >
class Disc_With_Holes<T_complex, 0>
    : private Disc<T_complex>
{
private:
    typedef Disc<T_complex> m_Base ;
    
public:
    typedef typename m_Base::complex complex ;
    typedef typename m_Base::real real ;
    typedef typename m_Base::Circle Circle ;
    typedef typename m_Base::category_selector category_selector ;
    typedef typename m_Base::topology_selector topology_selector ;

    explicit Disc_With_Holes( const Circle & circle )
        : m_Base(circle) { }

    // compiler writes memberwise copy and assign

    using m_Base::disc ;
    using m_Base::domain ;
    using m_Base::domain_clip ;
    using m_Base::domain_snap ;

protected:
    typedef typename m_Base::Slicer Slicer ;
    using m_Base::slicer ;
} ;

}}}} // namespace esve::geom::dimn::specs

#include <esve/geom/dimn/specs/Disc_With_Holes.template.cxx>

#endif

