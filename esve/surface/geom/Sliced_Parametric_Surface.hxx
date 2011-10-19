//
// A Sliced_Parametric_Surface is a Clipped_Parametric_Surface with a
// nicely formed boundary.
//
// This is done via spec.domain_snap() which gives the closest point
// on the boundary from a given point.
//

#ifndef esve_surface_geom_Sliced_Parametric_Surface_hxx
#define esve_surface_geom_Sliced_Parametric_Surface_hxx

#include <esve/surface/geom/Clipped_Parametric_Surface.hxx>
#include <esve/surface/base/Rectangular_Boundaries.hxx>
#include <esve/util/array.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec,
          typename T_Facets_Around_Vertex =
              // domain snapping up to 6 FAV; ignore the other FAVs (if any)
              util::array<typename T_Spec::Vertex_Index, 6> >
class Sliced_Parametric_Surface
    : public Clipped_Parametric_Surface<T_Spec, T_Facets_Around_Vertex>
{
private:
    typedef
    Clipped_Parametric_Surface<T_Spec, T_Facets_Around_Vertex>
    m_Base ;

#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;

        Domain_Point r = spec.domain_snap(Domain_Point(),
                                          Domain_Point()) ;

        m_unused(r) ;
    }
    
    struct m_Requirements
    {
        m_Requirements()
        {
            typedef
                void (Sliced_Parametric_Surface::*R)( const T_Spec & ) const ;

            R r1 = &Sliced_Parametric_Surface::m_requirements_1 ;
            
            m_unused(r1) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    typedef T_Spec m_Spec ;

    typedef typename
    m_Base::Vertices_iterator
    m_Vertices_iterator ;

    typedef typename
    m_Base::Facet
    m_Facet ;

    typedef
    base::Rectangular_Boundaries<m_Base>
    m_Boundaries ;

    typedef typename
    m_Base::Vertices_size_type
    m_Vertices_size_type ;

    typedef typename
    m_Boundaries::const_iterator
    m_Boundaries_const_iterator ;

    typedef typename
    m_Boundaries::Boundary::const_iterator
    m_Boundary_const_iterator ;

    Sliced_Parametric_Surface( const Sliced_Parametric_Surface & ) ;
    Sliced_Parametric_Surface &
    operator=( const Sliced_Parametric_Surface & ) ;

    const m_Spec & m_spec ;
    m_Boundaries m_boundaries ;

public:
    typedef m_Spec Spec ;

    Sliced_Parametric_Surface( const Spec & ) ;
    ~Sliced_Parametric_Surface() ;

protected:
    // base override
    void compute_surface_clip() ;
} ;

}}} // namespace esve::surface::geom

#include <esve/surface/geom/Sliced_Parametric_Surface.template.cxx>

#endif

