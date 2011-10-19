
#include <esve/surface/base/Rectangular_Mesh.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Vertex, typename T_Vertex_Index >
Rectangular_Mesh<T_Vertex,
                 T_Vertex_Index>::
Rectangular_Mesh()
    : m_Base(),
      m_domain(*this)
{
}

template< typename T_Vertex, typename T_Vertex_Index >
Rectangular_Mesh<T_Vertex,
                 T_Vertex_Index>::
~Rectangular_Mesh()
{
}

}}} // namespace esve::surface::base

