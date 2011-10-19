//
// Combine two existing slicers.
//
// A slicer is a class which defines the methods domain_clip() and
// domain_snap().
//

#ifndef esve_geom_dimn_Slicer_Union_hxx
#define esve_geom_dimn_Slicer_Union_hxx

namespace esve { namespace geom { namespace dimn {

template< typename Slicer1,
          typename Slicer2 >
class Slicer_Union
{
public:
    typedef typename Slicer1::complex complex ;

    Slicer_Union( const Slicer1 & s1,
                  const Slicer2 & s2 )
        : m_slicer1(s1),
          m_slicer2(s2) { }

    bool domain_clip( const complex & unit_square,
                      const complex & domain ) const
    {
        return
            m_slicer1.domain_clip(unit_square, domain)
            ||
            m_slicer2.domain_clip(unit_square, domain) ;
    }

    complex domain_snap( const complex & unit_square,
                         const complex & domain ) const
    {
        const complex s1 = m_slicer1.domain_snap(unit_square, domain) ;
        const complex s2 = m_slicer2.domain_snap(unit_square, domain) ;

        if( abs(domain - s1) < abs(domain - s2) )
        {
            return s1 ;
        }

        return s2 ;
    }

private:
    Slicer_Union( const Slicer_Union & ) ;
    Slicer_Union & operator=( const Slicer_Union & ) ;

    const Slicer1 & m_slicer1 ;
    const Slicer2 & m_slicer2 ;
} ;

}}} // namespace esve::geom::dimn

#endif

