//
// Clip away portions of a parametric surface with
// functions.domain_clip() and functions.surface_clip().
//

#ifndef esve_surface_geom_Clipped_Parametric_Surface_hxx
#define esve_surface_geom_Clipped_Parametric_Surface_hxx

#include <esve/surface/base/Rectangular_Mesh.hxx>
#include <esve/surface/base/Rectangular_Surface_Spec.hxx>
#include <esve/surface/base/Rectangular_Surface.hxx>
#include <esve/util/array.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec,
          typename T_Facets_Around_Vertex =
              util::array<typename T_Spec::Vertex_Index, 4> >
class Clipped_Parametric_Surface
    : protected base::Rectangular_Surface_Spec
                <
                    typename T_Spec::Vertex,
                    typename T_Spec::Vertex_Index,
                    T_Facets_Around_Vertex
                >::Packed_Surface
{
private:
    typedef typename
    base::Rectangular_Surface_Spec
                <
                    typename T_Spec::Vertex,
                    typename T_Spec::Vertex_Index,
                    T_Facets_Around_Vertex
                >::Packed_Surface
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

    void m_requirements_4( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;

        bool r = spec.domain_clip(Domain_Point(),
                                  Domain_Point()) ;
        
        m_unused(r) ;
    }
    
    void m_requirements_5( const T_Spec & spec ) const
    {
        typedef typename T_Spec::Domain_Point Domain_Point ;
        typedef typename T_Spec::Point Point ;

        bool r = spec.surface_clip(Domain_Point(),
                                   Domain_Point(),
                                   Point()) ;
        
        m_unused(r) ;
    }
    
    struct m_Requirements
    {
        m_Requirements()
        {
            typedef
                void (Clipped_Parametric_Surface::*R)( const T_Spec & ) const ;

            R r1 = &Clipped_Parametric_Surface::m_requirements_1 ;
            R r2 = &Clipped_Parametric_Surface::m_requirements_2 ;
            R r3 = &Clipped_Parametric_Surface::m_requirements_3 ;
            R r4 = &Clipped_Parametric_Surface::m_requirements_4 ;
            R r5 = &Clipped_Parametric_Surface::m_requirements_5 ;
            
            m_unused(r1) ;
            m_unused(r2) ;
            m_unused(r3) ;
            m_unused(r4) ;
            m_unused(r5) ;
        }
    } m_requirements ;
#endif // !defined(NDEBUG)

    typedef T_Spec m_Spec ;
    typedef typename m_Base::Vertex m_Vertex ;
    typedef typename m_Base::Facet m_Facet ;
    typedef typename m_Base::Facet::Vertex_Index m_Vertex_Index ;
    typedef typename m_Vertex::Domain_Point m_Domain_Point ;

    typedef
    std::vector<m_Vertex_Index>
    m_Vertex_Indexes ;

    typedef
    base::Rectangular_Mesh< m_Vertex, m_Vertex_Index >
    m_Mesh ;

    typedef typename
    m_Mesh::Spec
    m_Mesh_Spec ;

    typedef typename
    m_Mesh::Vertices_iterator
    m_Mesh_Vertices_iterator ;

    typedef typename
    m_Mesh::Facets_const_iterator
    m_Mesh_Facets_const_iterator ;

    typedef typename
    m_Vertex_Indexes::const_iterator
    m_Vertex_Indexes_const_iterator ;

    enum m_Facet_Clip_Test
    {
        m_ONE_REQUIRED,
        m_ALL_REQUIRED
    } ;

    struct m_Domain_Facet_Is_Clipped_False
    {
        m_Domain_Facet_Is_Clipped_False( const Clipped_Parametric_Surface & )
        {
        }

        bool operator()( m_Mesh_Facets_const_iterator f ) const
        {
            return false ;
        }
    } ;

    struct m_Domain_Facet_Is_Clipped_One_Required
    {
        const Clipped_Parametric_Surface & m ;

        m_Domain_Facet_Is_Clipped_One_Required(
            const Clipped_Parametric_Surface & m_ )
            : m(m_) { }

        bool operator()( m_Mesh_Facets_const_iterator f ) const
        {
            return
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_0()]
                ||
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_1()]
                ||
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_2()]
                ||
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_3()] ;
        }
    } ;

    struct m_Domain_Facet_Is_Clipped_All_Required
    {
        const Clipped_Parametric_Surface & m ;

        m_Domain_Facet_Is_Clipped_All_Required(
            const Clipped_Parametric_Surface & m_ )
            : m(m_) { }

        bool operator()( m_Mesh_Facets_const_iterator f ) const
        {
            return
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_0()]
                &&
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_1()]
                &&
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_2()]
                &&
                m.m_domain_vertex_is_clipped[(*f).vertex_indexes_3()] ;
        }
    } ;

    struct m_Surface_Facet_Is_Clipped_One_Required
    {
        const Clipped_Parametric_Surface & m ;

        m_Surface_Facet_Is_Clipped_One_Required(
            const Clipped_Parametric_Surface & m_ )
            : m(m_) { }

        bool operator()( m_Mesh_Facets_const_iterator f ) const ;
    } ;

    struct m_Surface_Facet_Is_Clipped_All_Required
    {
        const Clipped_Parametric_Surface & m ;

        m_Surface_Facet_Is_Clipped_All_Required(
            const Clipped_Parametric_Surface & m_ )
            : m(m_) { }

        bool operator()( m_Mesh_Facets_const_iterator f ) const ;
    } ;

    Clipped_Parametric_Surface( const Clipped_Parametric_Surface & ) ;
    Clipped_Parametric_Surface &
    operator=( const Clipped_Parametric_Surface & ) ;

    template< typename T_Domain_Facet_Is_Clipped,
              typename T_Surface_Facet_Is_Clipped >
    void m_compute_surface_clip() ;

    const m_Spec & m_spec ;

    bool m_need_compute_resolution ;
    bool m_need_compute_domain ;
    bool m_need_compute_domain_clip ;
    bool m_need_compute_surface ;
    bool m_need_compute_surface_clip ;
    bool m_need_compute_color ;

    m_Mesh_Spec m_mesh_spec ;
    m_Mesh m_mesh ;

    m_Vertex_Indexes m_domain_vertices ;
    std::vector<char> m_domain_vertex_is_clipped ;
    m_Vertex_Indexes m_vertex_map ;
    m_Facet_Clip_Test m_facet_clip_test ;

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

    typedef m_Facet_Clip_Test Facet_Clip_Test ;

    // A facet is clipped when at least one of its vertices is clipped.
    // (default)
    static const Facet_Clip_Test ONE_REQUIRED = m_ONE_REQUIRED ;

    // A facet is clipped only when all of its vertices are clipped.
    static const Facet_Clip_Test ALL_REQUIRED = m_ALL_REQUIRED ;

    //////////////////////////////////////////////////////
    // constructor
    //////////////////////////////////////////////////////

    Clipped_Parametric_Surface( const Spec & ) ;

    //////////////////////////////////////////////////////
    // surface parameters
    //////////////////////////////////////////////////////

    void resolution( Facets_size_type width, Facets_size_type height ) ;
    Facets_size_type width_resolution() const
    {
        return m_mesh_spec.width_resolution ;
    }

    Facets_size_type height_resolution() const
    {
        return m_mesh_spec.height_resolution ;
    }

    Topology topology() const ;
    void topology( Topology ) ;

    Facet_Clip_Test facet_clip_test() const
    {
        return m_facet_clip_test ;
    }

    void facet_clip_test( Facet_Clip_Test a )
    {
        m_facet_clip_test = a ;
    }

    //////////////////////////////////////////////////////
    // flags
    //////////////////////////////////////////////////////

    void update_domain()
    {
        m_need_compute_domain = true ;
    }

    void update_domain_clip()
    {
        m_need_compute_domain_clip = true ;
    }

    void update_surface()
    {
        m_need_compute_surface = true ;
    }

    void update_surface_clip()
    {
        m_need_compute_surface_clip = true ;
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
        return m_need_compute_domain_clip ;
    }

    bool surface_changed() const
    {
        return m_need_compute_surface ;
    }

    bool surface_clip_changed() const
    {
        return m_need_compute_surface_clip ;
    }

    bool color_changed() const
    {
        return m_need_compute_color ;
    }

    virtual ~Clipped_Parametric_Surface() ;

protected:
    virtual void compute() ;
    virtual bool changed() const ;

    virtual void compute_resolution() ;
    virtual void compute_domain() ;
    virtual void compute_domain_clip() ;
    virtual void compute_surface() ;
    virtual void compute_surface_clip() ;
    virtual void compute_color() ;
} ;

}}} // namespace esve::surface::geom

#include <esve/surface/geom/Clipped_Parametric_Surface.template.cxx>

#endif

