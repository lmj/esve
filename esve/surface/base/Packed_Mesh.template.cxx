
#include <esve/surface/base/Packed_Mesh.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Vertex, typename T_Facet >
Packed_Mesh<T_Vertex, T_Facet>::
Packed_Mesh()
    : m_vertices(),
      m_facets()
{
}

template< typename T_Vertex, typename T_Facet >
Packed_Mesh<T_Vertex, T_Facet>::
~Packed_Mesh()
{
}

}}} // namespace esve::surface::base
