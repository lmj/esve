//
// Rectangular Surface
//
// Packed_Surface operations are restricted to those leaving the
// topology invariant.
//
// See Rectangular_Surface_Spec for an example of the 'spec' template
// parameter.
//

#ifndef esve_surface_base_Rectangular_Surface_hxx
#define esve_surface_base_Rectangular_Surface_hxx

namespace esve { namespace surface { namespace base {

//////////////////////////////////////////////////////////////////
//
// Rectangular_Surface
//
//////////////////////////////////////////////////////////////////

template< typename T_Spec >
class Rectangular_Surface
    : private T_Spec::Packed_Surface
{
private:
    typedef T_Spec m_Spec ;

    typedef typename
    m_Spec::Packed_Surface
    m_Base ;

    typedef typename
    m_Spec::Rectangular_Domain
    m_Rectangular_Domain ;

    typedef typename
    m_Rectangular_Domain::Spec
    m_Rectangular_Domain_Spec ;

    m_Rectangular_Domain m_domain ;

public:
    ///////////////////////////////////////////////////////////
    // allowed Packed_Surface types/methods
    ///////////////////////////////////////////////////////////

    typedef typename m_Base::Vertex Vertex ;
    typedef typename m_Base::Facet Facet ;
    typedef typename m_Base::Vertex::Point::value_type real ;

    typedef typename m_Base::Vertices_iterator Vertices_iterator ;
    typedef typename m_Base::Vertices_const_iterator Vertices_const_iterator ;
    typedef typename m_Base::Vertices_size_type Vertices_size_type ;

    typedef typename m_Base::Facets_const_iterator Facets_const_iterator ;
    typedef typename m_Base::Facets_size_type Facets_size_type ;

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

    using m_Base::compute_facet_normals ;
    using m_Base::compute_vertex_normals ;
    using m_Base::compute_normals ;

    ///////////////////////////////////////////////////////////
    // own types/methods
    ///////////////////////////////////////////////////////////

    typedef m_Spec Spec ;
    typedef m_Rectangular_Domain_Spec Domain_Spec ;

    Rectangular_Surface() ;
    // compiler writes memberwise copy and assign

    const Domain_Spec & domain_spec() const
    {
        return m_domain.spec() ;
    }

    void compute( const Domain_Spec & spec )
    {
        m_domain.compute(spec) ;
    }

    ~Rectangular_Surface() ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Rectangular_Surface.template.cxx>

#endif

