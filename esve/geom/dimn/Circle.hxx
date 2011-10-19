
#ifndef esve_geom_dimn_Circle_hxx
#define esve_geom_dimn_Circle_hxx

namespace esve { namespace geom { namespace dimn {

template< typename T_complex >
class Circle
{
private:
    typedef T_complex m_complex ;
    typedef typename m_complex::value_type m_real ;

    m_complex m_center ;
    m_real m_radius ;

public:
    typedef m_complex complex ;
    typedef m_real real ;

    Circle( const complex & center,
            real radius )
        : m_center(center),
          m_radius(radius) { }

    // compiler writes memberwise copy and assign

    const complex & center() const
    {
        return m_center ;
    }

    void center( const complex & a )
    {
        m_center = a ;
    }

    const real radius() const
    {
        return m_radius ;
    }

    void radius( const real a )
    {
        m_radius = a ;
    }
} ;

}}} // namespace esve::geom::dimn

#endif

