//
// The type Vertex::Domain_Point and corresponding member
// vertex.domain_point are used (vertex_types.hxx).
//

#ifndef esve_surface_base_Rectangular_Mesh_hxx
#define esve_surface_base_Rectangular_Mesh_hxx

#include <esve/surface/base/Packed_Quad.hxx>
#include <esve/surface/base/Packed_Mesh.hxx>
#include <esve/surface/base/Rectangular_Domain.hxx>

namespace esve { namespace surface { namespace base {

//////////////////////////////////////////////////////////////////
//
// Rectangular_Mesh
//
//////////////////////////////////////////////////////////////////

template< typename T_Vertex,
          typename T_Vertex_Index >
class Rectangular_Mesh
    : private Packed_Mesh< T_Vertex,
                           Packed_Quad<T_Vertex_Index> >
{
private:
    typedef
    Packed_Mesh< T_Vertex, Packed_Quad<T_Vertex_Index> >
    m_Base ;

    Rectangular_Domain<m_Base> m_domain ;

public:
    typedef typename m_Base::Vertex Vertex ;
    typedef typename m_Base::Facet Facet ;
    typedef typename m_Base::Vertex::Point::value_type real ;

    typedef typename m_Base::Vertices_iterator Vertices_iterator ;
    typedef typename m_Base::Vertices_const_iterator Vertices_const_iterator ;
    typedef typename m_Base::Vertices_size_type Vertices_size_type ;

    typedef typename m_Base::Facets_const_iterator Facets_const_iterator ;
    typedef typename m_Base::Facets_size_type Facets_size_type ;

    typedef typename T_Vertex::Domain_Point Domain_Point ;

    typedef Rectangular_Domain_Spec<Domain_Point, Facets_size_type> Spec ;

    using m_Base::vertices ;
    using m_Base::vertices_begin ;
    using m_Base::vertices_end ;
    using m_Base::vertices_size ;

    const Facet & facet( Facets_size_type i ) const
    {
        return m_Base::facet(i) ;
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

    void compute( const Spec & spec )
    {
        m_domain.compute(spec) ;
    }

    const Spec & spec() const
    {
        return m_domain.spec() ;
    }

    Rectangular_Mesh() ;
    // compiler writes memberwise copy and assign
    ~Rectangular_Mesh() ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Rectangular_Mesh.template.cxx>

#endif

