
#include <esve/surface/geom/Clipped_Parametric_Surface.hxx>

namespace esve { namespace surface { namespace geom {

template< typename T_Spec, typename T_FAV >
Clipped_Parametric_Surface<T_Spec, T_FAV>::
Clipped_Parametric_Surface( const m_Spec & spec )
    : m_Base(),
      m_spec(spec),
      m_need_compute_resolution(true),
      m_need_compute_domain(true),
      m_need_compute_domain_clip(true),
      m_need_compute_surface(true),
      m_need_compute_surface_clip(true),
      m_need_compute_color(true),
      m_mesh_spec(m_Mesh_Spec(m_Domain_Point(0, 0),
                              m_Domain_Point(1, 1),
                              0, 0)),
      m_mesh(),
      m_domain_vertices(),
      m_domain_vertex_is_clipped(),
      m_vertex_map(),
      m_facet_clip_test(m_ONE_REQUIRED)
{
}

template< typename T_Spec, typename T_FAV >
Clipped_Parametric_Surface<T_Spec, T_FAV>::
~Clipped_Parametric_Surface()
{
}

template< typename T_Spec, typename T_FAV >
typename Clipped_Parametric_Surface<T_Spec, T_FAV>::Topology
Clipped_Parametric_Surface<T_Spec, T_FAV>::
topology() const
{
    return m_mesh_spec.topology ;
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
topology( Topology a )
{
    m_mesh_spec.topology = a ;
    m_need_compute_resolution = true ;
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
resolution( Facets_size_type wr, Facets_size_type hr )
{
    m_mesh_spec.width_resolution = wr ;
    m_mesh_spec.height_resolution = hr ;
    m_need_compute_resolution = true ;
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_resolution()
{
    m_mesh.compute(m_mesh_spec) ;
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_domain()
{
    for( m_Mesh_Vertices_iterator r = m_mesh.vertices_begin() ;
         r != m_mesh.vertices_end() ;
         ++r )
    {
        (*r).transformed_domain_point =
            m_spec.domain((*r).domain_point) ;
    }
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_domain_clip()
{
    m_domain_vertices.clear() ;

    m_domain_vertex_is_clipped.clear() ;
    m_domain_vertex_is_clipped.resize(m_mesh.vertices_size(), true) ;

    for( m_Mesh_Vertices_iterator r = m_mesh.vertices_begin() ;
         r != m_mesh.vertices_end() ;
         ++r )
    {
        if( !m_spec.domain_clip((*r).domain_point,
                                (*r).transformed_domain_point) )
        {
            m_domain_vertices.push_back(r - m_mesh.vertices_begin()) ;
            m_domain_vertex_is_clipped[r - m_mesh.vertices_begin()] = false ;
        }
    }
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_surface()
{
    for( m_Vertex_Indexes_const_iterator i = m_domain_vertices.begin() ;
         i != m_domain_vertices.end() ;
         ++i )
    {
        m_mesh.vertices(*i).point =
            m_spec.surface(
                m_mesh.vertices(*i).domain_point,
                m_mesh.vertices(*i).transformed_domain_point) ;
    }
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_surface_clip()
{
    m_Base::vertices_erase(m_Base::vertices_begin(),
                           m_Base::vertices_end()) ;
    m_Base::facets_erase(m_Base::facets_begin(),
                         m_Base::facets_end()) ;

    m_vertex_map.clear() ;
    m_vertex_map.resize(m_mesh.vertices_size(), m_Vertex_Index(-1)) ;

    if( m_domain_vertices.size() == m_mesh.vertices_size() )
    {
        switch( m_facet_clip_test )
        {
        case m_ONE_REQUIRED:
            m_compute_surface_clip
            <
                m_Domain_Facet_Is_Clipped_False,
                m_Surface_Facet_Is_Clipped_One_Required
            >() ;
            break ;

        case m_ALL_REQUIRED:
            m_compute_surface_clip
            <
                m_Domain_Facet_Is_Clipped_False,
                m_Surface_Facet_Is_Clipped_All_Required
            >() ;
            break ;
        }
    }
    else
    {
        switch( m_facet_clip_test )
        {
        case m_ONE_REQUIRED:
            m_compute_surface_clip
            <
                m_Domain_Facet_Is_Clipped_One_Required,
                m_Surface_Facet_Is_Clipped_One_Required
            >() ;
            break ;

        case m_ALL_REQUIRED:
            m_compute_surface_clip
            <
                m_Domain_Facet_Is_Clipped_All_Required,
                m_Surface_Facet_Is_Clipped_All_Required
            >() ;
            break ;
        }
    }
}

template< typename T_Spec, typename T_FAV >
template< typename T_Domain_Facet_Is_Clipped,
          typename T_Surface_Facet_Is_Clipped >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
m_compute_surface_clip()
{
    T_Domain_Facet_Is_Clipped domain_facet_is_clipped(*this) ;
    T_Surface_Facet_Is_Clipped surface_facet_is_clipped(*this) ;

    for( m_Mesh_Facets_const_iterator f = m_mesh.facets_begin() ;
         f != m_mesh.facets_end() ;
         ++f )
    {
        if( !(domain_facet_is_clipped(f)
              ||
              surface_facet_is_clipped(f)) )
        {
            // facet kept

            if( m_vertex_map[(*f).vertex_indexes_0()] == m_Vertex_Index(-1) )
            {
                m_Base::add_vertex(m_mesh.vertices((*f).vertex_indexes_0())) ;

                m_vertex_map[(*f).vertex_indexes_0()] =
                    m_Base::vertices_size() - 1 ;
            }
            if( m_vertex_map[(*f).vertex_indexes_1()] == m_Vertex_Index(-1) )
            {
                m_Base::add_vertex(m_mesh.vertices((*f).vertex_indexes_1())) ;

                m_vertex_map[(*f).vertex_indexes_1()] =
                    m_Base::vertices_size() - 1 ;
            }
            if( m_vertex_map[(*f).vertex_indexes_2()] == m_Vertex_Index(-1) )
            {
                m_Base::add_vertex(m_mesh.vertices((*f).vertex_indexes_2())) ;

                m_vertex_map[(*f).vertex_indexes_2()] =
                    m_Base::vertices_size() - 1 ;
            }
            if( m_vertex_map[(*f).vertex_indexes_3()] == m_Vertex_Index(-1) )
            {
                m_Base::add_vertex(m_mesh.vertices((*f).vertex_indexes_3())) ;

                m_vertex_map[(*f).vertex_indexes_3()] =
                    m_Base::vertices_size() - 1 ;
            }

            m_Base::add_facet(
                m_Facet(m_vertex_map[(*f).vertex_indexes_0()],
                        m_vertex_map[(*f).vertex_indexes_1()],
                        m_vertex_map[(*f).vertex_indexes_2()],
                        m_vertex_map[(*f).vertex_indexes_3()])) ;
        }
    }
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute_color()
{
    for( Vertices_iterator i = m_Base::vertices_begin() ;
         i != m_Base::vertices_end() ;
         ++i )
    {
        (*i).color =
            m_spec.color(
                (*i).domain_point,
                (*i).transformed_domain_point,
                (*i).point) ;
    }
}

template< typename T_Spec, typename T_FAV >
bool
Clipped_Parametric_Surface<T_Spec, T_FAV>::
changed() const
{
    return
        m_need_compute_resolution ||
        m_need_compute_domain ||
        m_need_compute_domain_clip ||
        m_need_compute_surface ||
        m_need_compute_surface_clip ||
        m_need_compute_color ;
}

template< typename T_Spec, typename T_FAV >
void
Clipped_Parametric_Surface<T_Spec, T_FAV>::
compute()
{
    if( m_need_compute_resolution )
    {
        compute_resolution() ;
        m_need_compute_domain = true ;
    }
    if( m_need_compute_domain )
    {
        compute_domain() ;
        m_need_compute_domain_clip = true ;
    }
    if( m_need_compute_domain_clip )
    {
        compute_domain_clip() ;
        m_need_compute_surface = true ;
    }
    if( m_need_compute_surface )
    {
        compute_surface() ;
        m_need_compute_surface_clip = true ;
    }
    if( m_need_compute_surface_clip )
    {
        compute_surface_clip() ;
        m_need_compute_color = true ;
    }
    if( m_need_compute_color )
    {
        compute_color() ;
    }

    m_need_compute_resolution = false ;
    m_need_compute_domain = false ;
    m_need_compute_domain_clip = false ;
    m_need_compute_surface = false ;
    m_need_compute_surface_clip = false ;
    m_need_compute_color = false ;
}

template< typename T_Spec, typename T_FAV >
bool
Clipped_Parametric_Surface<T_Spec, T_FAV>::
m_Surface_Facet_Is_Clipped_One_Required::
operator()( m_Mesh_Facets_const_iterator f ) const
{
    // near-duplicate (below); needed for shortcut evaluation
    return
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            point)
        ||
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            point)
        ||
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            point)
        ||
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            point) ;
}

template< typename T_Spec, typename T_FAV >
bool
Clipped_Parametric_Surface<T_Spec, T_FAV>::
m_Surface_Facet_Is_Clipped_All_Required::
operator()( m_Mesh_Facets_const_iterator f ) const
{
    // near-duplicate (above); needed for shortcut evaluation
    return
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_0()).
            point)
        &&
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_1()).
            point)
        &&
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_2()).
            point)
        &&
        m.m_spec.surface_clip(
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            transformed_domain_point,
            m.m_mesh.vertices((*f).vertex_indexes_3()).
            point) ;
}

}}} // namespace esve::surface::geom

