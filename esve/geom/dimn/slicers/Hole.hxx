
#ifndef esve_geom_dimn_slicers_Hole_hxx
#define esve_geom_dimn_slicers_Hole_hxx

#include <esve/geom/dimn/Circle.hxx>

namespace esve { namespace geom { namespace dimn { namespace slicers {

template< typename T_complex >
class Hole
{
public:
    typedef T_complex complex ;
    typedef typename complex::value_type real ;
    typedef geom::dimn::Circle<complex> Circle ;

    explicit Hole( const Circle & circle )
        : m_circle(circle) { }

    bool domain_clip( const complex & ,
                      const complex & domain ) const
    {
        return abs(domain - m_circle.center()) < m_circle.radius() ;
    }

    complex domain_snap( const complex & ,
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
    Hole( const Hole & ) ;
    Hole & operator=( const Hole & ) ;

    const Circle & m_circle ;
} ;

}}}} // namespace esve::geom::dimn::slicers

#endif

