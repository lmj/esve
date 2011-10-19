//
// Rectangular Domain: plane, torus, projective plane, etc
//
// Operates on the given mesh data.
//
// The type Vertex::Domain_Point and corresponding member
// vertex.domain_point are used (see vertex_types.hxx).
//

#ifndef esve_surface_base_Rectangular_Domain_hxx
#define esve_surface_base_Rectangular_Domain_hxx

#include <esve/surface/base/Topology.hxx>
#include <esve/surface/base/Rectangular_Domain_Spec.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Packed_Mesh >
class Rectangular_Domain
{
private:
    typedef T_Packed_Mesh m_Packed_Mesh ;
    typedef typename m_Packed_Mesh::Vertex::Domain_Point m_Domain_Point ;
    typedef typename m_Packed_Mesh::Facets_size_type m_Facets_size_type ;
    typedef typename m_Packed_Mesh::Vertex m_Vertex ;
    typedef typename m_Packed_Mesh::Facet m_Facet ;

    typedef typename m_Packed_Mesh::Vertices_size_type m_Index ;
    typedef typename m_Packed_Mesh::Vertices_size_type m_Vertex_Index ;

    typedef typename m_Domain_Point::value_type m_real ;

    typedef
    Rectangular_Domain_Spec<m_Domain_Point, m_Facets_size_type>
    m_Spec ;

    Rectangular_Domain( const Rectangular_Domain & ) ;
    Rectangular_Domain & operator=( const Rectangular_Domain & ) ;

    m_Vertex_Index m_coord2index( m_Index i, m_Index j )
    {
        return i + j*m_spec.width_resolution ;
    }

    void m_add_dpoint( m_Index i, m_Index j, m_real w, m_real h )
    {
        (*m_mesh.add_vertex(m_Vertex())).domain_point =

            m_Domain_Point(m_spec.corner0.real()
                           +
                           i*w/m_spec.width_resolution,

                           m_spec.corner0.imag()
                           +
                           j*h/m_spec.height_resolution) ;
    }

    void m_compute() ;
    void m_compute_plane_vertices() ;
    void m_compute_plane() ;
    void m_compute_straight_wrapped() ;
    void m_stretch() ;

    m_Packed_Mesh & m_mesh ;
    m_Spec m_spec ;

public:
    typedef m_Spec Spec ;
    typedef m_Packed_Mesh Packed_Mesh ;

    Rectangular_Domain( Packed_Mesh & ) ;

    void compute( const Spec & ) ;
    const Spec & spec() const
    {
        return m_spec ;
    }

    Rectangular_Domain() ;
    ~Rectangular_Domain() ;
} ;

}}} // namespace esve::surface::base

#include <esve/surface/base/Rectangular_Domain.template.cxx>

#endif

