
#ifndef esve_geom_dimn_slicers_Disc_hxx
#define esve_geom_dimn_slicers_Disc_hxx

#include <esve/geom/dimn/Circle.hxx>

namespace esve { namespace geom { namespace dimn { namespace slicers {

template< typename T_complex >
class Disc
{
public:
    typedef T_complex complex ;
    typedef typename complex::value_type real ;
    typedef geom::dimn::Circle<complex> Circle ;

    explicit Disc( const Circle & circle )
        : m_circle(circle) { }

    bool domain_clip( const complex & unit_square,
                      const complex & domain ) const
    {
        return abs(domain - m_circle.center()) > m_circle.radius() ;
    }

    complex domain_snap( const complex & unit_square,
                         const complex & domain ) const
    {
        const complex offset = domain - m_circle.center() ;

        return
            m_circle.center()
            +
            m_circle.radius()
            *
            offset/abs(offset) ;
    }

private:
    Disc( const Disc & ) ;
    Disc & operator=( const Disc & ) ;

    const Circle & m_circle ;
} ;

}}}} // namespace esve::geom::dimn::slicers

#endif

