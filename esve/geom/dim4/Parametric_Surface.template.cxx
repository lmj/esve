
#include <esve/geom/dim4/Parametric_Surface.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace geom { namespace dim4 {

template< typename T_Spec >
Parametric_Surface<T_Spec>::
Parametric_Surface( const Spec & spec )
    : m_Base(spec),
      m_spec(spec)
{
    m_Base::topology(
        dimn::selectors_impl::select_topology<m_topology_selector>::value) ;
}

template< typename T_Spec >
Parametric_Surface<T_Spec>::
~Parametric_Surface()
{
}

template< typename T_Spec >
void
Parametric_Surface<T_Spec>::
pretransform()
{
    m_Base::compute() ;
}

template< typename T_Spec >
void
Parametric_Surface<T_Spec>::
posttransform()
{
    m_Base::compute_normals() ;
    m_postcompute(m_postcompute_selector()) ;
}

template< typename T_Spec >
void
Parametric_Surface<T_Spec>::
m_postcompute( dimn::selectors::postcompute::yes )
{
    for( m_Vertices_iterator v = m_Base::vertices_begin() ;
         v != m_Base::vertices_end() ;
         ++v )
    {
        m_spec.postcompute(*v) ;
    }
}

template< typename T_Spec >
void
Parametric_Surface<T_Spec>::
draw()
{
    if( m_Base::vertices_size() != 0 &&
        m_Base::facets_size() != 0 )
    {
        glInterleavedArrays(
            GL_C4F_N3F_V3F,
            sizeof(m_Vertex),
            static_cast<const GLvoid*>(&*m_Base::vertices_begin())) ;

        glDrawElements(
            GL_QUADS,
            4*m_Base::facets_size(),
            GL_UNSIGNED_INT,
            static_cast<const GLvoid*>(&*m_Base::facets_begin())) ;
    }
}

}}} // namespace esve::geom::dim4
