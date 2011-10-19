
#include <esve/surface/base/Rectangular_Domain.hxx>

namespace esve { namespace surface { namespace base {

template< typename T_Packed_Mesh >
Rectangular_Domain<T_Packed_Mesh>::
Rectangular_Domain( Packed_Mesh & mesh )
    : m_mesh(mesh),
      m_spec(Spec(m_Domain_Point(0, 0), m_Domain_Point(0, 0), 0, 0))
{
}

template< typename T_Packed_Mesh >
Rectangular_Domain<T_Packed_Mesh>::
~Rectangular_Domain()
{
}

template< typename T_Packed_Mesh >
void
Rectangular_Domain<T_Packed_Mesh>::
compute( const Spec & spec )
{
    m_spec = spec ;
    m_compute() ;
}

template< typename T_Packed_Mesh >
void
Rectangular_Domain<T_Packed_Mesh>::
m_compute()
{
    m_mesh.vertices_erase(m_mesh.vertices_begin(), m_mesh.vertices_end()) ;
    m_mesh.facets_erase(m_mesh.facets_begin(), m_mesh.facets_end()) ;

    if( m_spec.width_resolution != 0 &&
        m_spec.height_resolution != 0 )
    {
        switch( m_spec.topology )
        {
        case topology::PLANE:
            m_compute_plane() ;
            break ;

        case topology::CYLINDER_WRAP_WIDTH:
        case topology::CYLINDER_WRAP_HEIGHT:
        case topology::TORUS:
            m_compute_straight_wrapped() ;
            break ;

        case topology::MOEBIUS_BAND_WRAP_WIDTH:
        case topology::MOEBIUS_BAND_WRAP_HEIGHT:
        case topology::KLEIN_BOTTLE_WRAP_WIDTH:
        case topology::KLEIN_BOTTLE_WRAP_HEIGHT:
        case topology::PROJECTIVE_PLANE:
            // to be implemented
            m_compute_plane() ;
            break ;
        }
    }
}

template< typename T_Packed_Mesh >
void
Rectangular_Domain<T_Packed_Mesh>::
m_compute_plane_vertices()
{
    const m_Index wr = m_spec.width_resolution ;
    const m_Index hr = m_spec.height_resolution ;

    const m_real w = m_spec.corner1.real() - m_spec.corner0.real() ;
    const m_real h = m_spec.corner1.imag() - m_spec.corner0.imag() ;

    for( m_Index j = 0 ; j != hr + 1 ; ++j )
    {
        for( m_Index i = 0 ; i != wr + 1 ; ++i )
        {
            m_add_dpoint(i, j, w, h) ;
        }
    }
}

template< typename T_Packed_Mesh >
void
Rectangular_Domain<T_Packed_Mesh>::
m_compute_plane()
{
    const m_Index wr = m_spec.width_resolution ;
    const m_Index hr = m_spec.height_resolution ;

    m_compute_plane_vertices() ;

    for( m_Index j = 0 ; j != hr ; ++j )
    {
        for( m_Index i = 0 ; i != wr ; ++i )
        {
            m_mesh.add_facet(m_Facet((i + 0) +
                                     (j + 0)*(wr + 1),

                                     (i + 1) +
                                     (j + 0)*(wr + 1),

                                     (i + 1) +
                                     (j + 1)*(wr + 1),

                                     (i + 0) +
                                     (j + 1)*(wr + 1))) ;
        }
    }
}

template< typename T_Packed_Mesh >
void
Rectangular_Domain<T_Packed_Mesh>::
m_compute_straight_wrapped()
{
    const m_Index wr = m_spec.width_resolution ;
    const m_Index hr = m_spec.height_resolution ;

    if( wr == 0 || hr == 0 )
    {
        return ;
    }

    const m_real w = m_spec.corner1.real() - m_spec.corner0.real() ;
    const m_real h = m_spec.corner1.imag() - m_spec.corner0.imag() ;

    ///////////////////////////////////////////////
    // all quads except top and right quads
    ///////////////////////////////////////////////

    for( m_Index j = 0 ; j != hr ; ++j )
    {
        for( m_Index i = 0 ; i != wr ; ++i )
        {
            m_add_dpoint(i, j, w, h) ;
        }
    }

    for( m_Index j = 0 ; j != hr - 1 ; ++j )
    {
        for( m_Index i = 0 ; i != wr - 1 ; ++i )
        {
            m_mesh.add_facet(m_Facet(m_coord2index(i    , j    ),
                                     m_coord2index(i + 1, j    ),
                                     m_coord2index(i + 1, j + 1),
                                     m_coord2index(i    , j + 1))) ;
        }
    }

    ///////////////////////////////////////////////
    // top quads except top-right quad, no wrapping
    ///////////////////////////////////////////////

    if( m_spec.topology == topology::CYLINDER_WRAP_WIDTH )
    {
        // new vertices along the top

        for( m_Index i = 0 ; i != wr ; ++i )
        {
            m_add_dpoint(i, hr, w, h) ;
        }

        // new facets connecting the new vertices
        {
            m_Index i = 0 ;
            m_Vertex_Index v = m_mesh.vertices_size() - wr ;
            for( ; i != wr - 1 ; ++i, ++v )
            {
                m_mesh.add_facet(m_Facet(m_coord2index(i, hr - 1),
                                         m_coord2index(i + 1, hr - 1),
                                         v + 1,
                                         v)) ;
            }
        }
    }

    ///////////////////////////////////////////////
    // right quads except top-right quad, no wrapping
    ///////////////////////////////////////////////

    if( m_spec.topology == topology::CYLINDER_WRAP_HEIGHT )
    {
        // new vertices along the right edge

        for( m_Index j = 0 ; j != hr ; ++j )
        {
            m_add_dpoint(wr, j, w, h) ;
        }

        // new facets connecting the new vertices
        {
            m_Index j = 0 ;
            m_Vertex_Index v = m_mesh.vertices_size() - hr ;
            for( ; j != hr - 1 ; ++j, ++v )
            {
                m_mesh.add_facet(m_Facet(m_coord2index(wr - 1, j),
                                         v,
                                         v + 1,
                                         m_coord2index(wr - 1, j + 1))) ;
            }
        }
    }

    ///////////////////////////////////////////////
    // top quads except top-right quad, straight wrapping
    ///////////////////////////////////////////////

    if( m_spec.topology == topology::CYLINDER_WRAP_HEIGHT ||
        m_spec.topology == topology::TORUS )
    {
        for( m_Index i = 0 ; i != wr - 1 ; ++i )
        {
            m_mesh.add_facet(m_Facet(m_coord2index(i    , hr - 1),
                                     m_coord2index(i + 1, hr - 1),
                                     m_coord2index(i + 1, 0     ),
                                     m_coord2index(i    , 0     ))) ;
        }
    }

    ///////////////////////////////////////////////
    // right quads except top-right quad, straight wrapping
    ///////////////////////////////////////////////

    if( m_spec.topology == topology::CYLINDER_WRAP_WIDTH ||
        m_spec.topology == topology::TORUS )
    {
        for( m_Index j = 0 ; j != hr - 1 ; ++j )
        {
            m_mesh.add_facet(m_Facet(m_coord2index(wr - 1, j    ),
                                     m_coord2index(0     , j    ),
                                     m_coord2index(0     , j + 1),
                                     m_coord2index(wr - 1, j + 1))) ;
        }
    }

    ///////////////////////////////////////////////
    // single top-right quad
    ///////////////////////////////////////////////

    if( m_spec.topology == topology::CYLINDER_WRAP_WIDTH )
    {
        m_mesh.add_facet(m_Facet(m_coord2index(wr - 1, hr - 1),
                                 m_coord2index(0     , hr - 1),
                                 m_mesh.vertices_size() - wr,
                                 m_mesh.vertices_size() - 1)) ;
    }
    else if( m_spec.topology == topology::CYLINDER_WRAP_HEIGHT )
    {
        m_mesh.add_facet(m_Facet(m_coord2index(wr - 1, hr - 1),
                                 m_mesh.vertices_size() - 1,
                                 m_mesh.vertices_size() - hr,
                                 m_coord2index(wr - 1, 0))) ;

    }
    else if( m_spec.topology == topology::TORUS )
    {
        m_mesh.add_facet(m_Facet(m_coord2index(wr - 1, hr - 1),
                                 m_coord2index(0     , hr - 1),
                                 m_coord2index(0     ,      0),
                                 m_coord2index(wr - 1,      0))) ;
    }
}

}}} // namespace esve::surface::base
