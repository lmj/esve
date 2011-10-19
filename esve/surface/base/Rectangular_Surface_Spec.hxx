//
// A typical set of types for Rectangular_Surface
//

#ifndef esve_surface_base_Rectangular_Surface_Spec_hxx
#define esve_surface_base_Rectangular_Surface_Spec_hxx

#include <esve/surface/base/Packed_Quad.hxx>
#include <esve/surface/base/Packed_Surface_Spec.hxx>
#include <esve/surface/base/Packed_Surface.hxx>
#include <esve/surface/base/Rectangular_Domain.hxx>
#include <esve/util/array.hxx>

namespace esve { namespace surface { namespace base {

//////////////////////////////////////////////////////////////////
//
// Rectangular_Surface_Spec
//
//////////////////////////////////////////////////////////////////

template< typename T_Vertex,
          typename T_Vertex_Index,
          typename T_Facets_Around_Vertex =
             // maximum of four facets around a vertex
             util::array<T_Vertex_Index, 4> >
class Rectangular_Surface_Spec
{
private:
    typedef T_Vertex m_Vertex ;
    typedef T_Vertex_Index m_Vertex_Index ;
    typedef T_Facets_Around_Vertex m_Facets_Around_Vertex ;
    typedef Packed_Quad<m_Vertex_Index> m_Facet ;

    typedef
    Packed_Surface
    <
        Packed_Surface_Spec
        <
            m_Vertex,
            m_Facet,
            m_Facets_Around_Vertex
        >
    >
    m_Packed_Surface ;

    typedef
    Rectangular_Domain<m_Packed_Surface>
    m_Rectangular_Domain ;

public:
    typedef m_Packed_Surface Packed_Surface ;
    typedef m_Rectangular_Domain Rectangular_Domain ;
} ;

}}} // namespace esve::surface::base

#endif
