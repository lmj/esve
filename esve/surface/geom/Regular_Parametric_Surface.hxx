
#ifndef esve_surface_geom_Regular_Parametric_Surface_hxx
#define esve_surface_geom_Regular_Parametric_Surface_hxx

#include <esve/surface/base/Rectangular_Surface_Spec.hxx>
#include <esve/surface/base/Rectangular_Surface.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec >
class Regular_Parametric_Surface
    : protected base::Rectangular_Surface
                <
                    base::Rectangular_Surface_Spec
                    <
                        typename T_Spec::Vertex,
                        typename T_Spec::Vertex_Index
                    >
                >
{
private:
    typedef
    base::Rectangular_Surface
                <
                    base::Rectangular_Surface_Spec
                    <
                        typename T_Spec::Vertex,
                        typename T_Spec::Vertex_Index
                    >
                >
    m_Base ;

#if !defined(NDEBUG)
    template< class U > static void m_unused( const U & ) { }

    void m_requirements_1( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;

        Domain_Point r = spec.domain(Domain_Point()) ;

        m_unused(r) ;
    }

    void m_requirements_2( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;
        typedef typename T_Spec::Point Point ;

        Point r = spec.surface(Domain_Point(),
                               Domain_Point()) ;

        m_unused(r) ;
    }

    void m_requirements_3( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;
        typedef typename T_Spec::Point Point ;
        typedef typename T_Spec::Color Color ;

        Color r = spec.color(Domain_Point(),
                             Domain_Point(),
                             Point()) ;

        m_unused(r) ;
    }

    struct m_Requirements
    {
        m_Requirements()
        {
            typedef
                void (Regular_Parametric_Surface::*R)( const T_Spec & ) const ;

            R r1 = &Regular_Parametric_Surface::m_requirements_1 ;
            R r2 = &Regular_Parametric_Surface::m_requirements_2 ;
            R r3 = &Regular_Parametric_Surface::m_requirements_3 ;
            
            m_unused(r1) ;
            m_unused(r2) ;
            m_unused(r3) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    typedef T_Spec m_Spec ;
    typedef typename m_Base::Vertex::Domain_Point m_Domain_Point ;
    typedef typename m_Base::Domain_Spec m_Domain_Spec ;

    Regular_Parametric_Surface( const Regular_Parametric_Surface & ) ;
    Regular_Parametric_Surface &
    operator=( const Regular_Parametric_Surface & ) ;

    void m_compute_resolution_domain_surface_color() ;
    void m_compute_domain_surface_color() ;
    void m_compute_surface_color() ;
    void m_compute_color() ;

    const m_Spec & m_spec ;

    bool m_need_compute_resolution ;
    bool m_need_compute_domain ;
    bool m_need_compute_surface ;
    bool m_need_compute_color ;

    m_Domain_Spec m_domain_spec ;

public:
    ///////////////////////////////////////////////////////////
    // allowed Packed_Surface types/methods
    ///////////////////////////////////////////////////////////

    typedef typename m_Base::Vertex
                             Vertex ;
    typedef typename m_Base::Facet
                             Facet ;

    typedef typename m_Base::Vertices_iterator
                             Vertices_iterator ;
    typedef typename m_Base::Vertices_const_iterator
                             Vertices_const_iterator ;
    typedef typename m_Base::Vertices_size_type
                             Vertices_size_type ;

    typedef typename m_Base::Facets_const_iterator
                             Facets_const_iterator ;
    typedef typename m_Base::Facets_size_type
                             Facets_size_type ;

    typedef typename m_Base::Facet_Normals_const_iterator
                             Facet_Normals_const_iterator ;
    typedef typename m_Base::Facet_Normals_size_type
                             Facet_Normals_size_type ;

    typedef typename m_Base::Facets_Around_Vertex_const_iterator
                             Facets_Around_Vertex_const_iterator ;
    typedef typename m_Base::Facets_Around_Vertex_size_type
                             Facets_Around_Vertex_size_type ;

    using m_Base::vertices ;
    using m_Base::vertices_begin ;
    using m_Base::vertices_end ;
    using m_Base::vertices_size ;

    const Facet & facets( Facets_size_type i ) const
    {
        return m_Base::facets(i) ;
    }

    Facets_const_iterator facets_begin() const
    {
        return m_Base::facets_begin() ;
    }

    Facets_const_iterator facets_end() const
    {
        return m_Base::facets_end() ;
    }

    Facets_size_type facets_size() const
    {
        return m_Base::facets_size() ;
    }

    using m_Base::facet_normals_begin ;
    using m_Base::facet_normals_end ;
    using m_Base::facet_normals_size ;

    Facets_Around_Vertex_const_iterator
    facets_around_vertex_begin( Vertices_const_iterator v ) const
    {
        return m_Base::facets_around_vertex_begin(v) ;
    }

    Facets_Around_Vertex_const_iterator
    facets_around_vertex_end( Vertices_const_iterator v ) const
    {
        return m_Base::facets_around_vertex_end(v) ;
    }

    Facets_Around_Vertex_size_type
    facets_around_vertex_size( Vertices_const_iterator v ) const
    {
        return m_Base::facets_around_vertex_size(v) ;
    }

    //////////////////////////////////////////////////////
    // types
    //////////////////////////////////////////////////////

    typedef m_Spec Spec ;
    typedef base::Topology Topology ;

    //////////////////////////////////////////////////////
    // constructor
    //////////////////////////////////////////////////////

    Regular_Parametric_Surface( const Spec & ) ;

    //////////////////////////////////////////////////////
    // surface parameters
    //////////////////////////////////////////////////////

    void resolution( Facets_size_type width, Facets_size_type height ) ;

    Facets_size_type width_resolution() const
    {
        return m_domain_spec.width_resolution ;
    }

    Facets_size_type height_resolution() const
    {
        return m_domain_spec.height_resolution ;
    }

    Topology topology() const ;
    void topology( Topology ) ;

    //////////////////////////////////////////////////////
    // flags
    //////////////////////////////////////////////////////

    void update_domain()
    {
        m_need_compute_domain = true ;
    }

    void update_domain_clip()
    {
        m_need_compute_domain = true ;
    }

    void update_surface()
    {
        m_need_compute_surface = true ;
    }

    void update_surface_clip()
    {
        m_need_compute_surface = true ;
    }

    void update_color()
    {
        m_need_compute_color = true ;
    }

    bool resolution_changed() const
    {
        return m_need_compute_resolution ;
    }

    bool domain_changed() const
    {
        return m_need_compute_domain ;
    }

    bool domain_clip_changed() const
    {
        return m_need_compute_domain ;
    }

    bool surface_changed() const
    {
        return m_need_compute_surface ;
    }

    bool surface_clip_changed() const
    {
        return m_need_compute_surface ;
    }

    bool color_changed() const
    {
        return m_need_compute_color ;
    }

    virtual ~Regular_Parametric_Surface() ;

protected:
    //////////////////////////////////////////////////////
    // engine hooks
    //////////////////////////////////////////////////////

    virtual void compute() ;
    virtual bool changed() const ;
} ;

}}} // namespace esve::surface::geom

#include <esve/surface/geom/Regular_Parametric_Surface.template.cxx>

#endif

