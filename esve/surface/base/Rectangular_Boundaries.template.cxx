
#include <esve/surface/base/Rectangular_Boundaries.hxx>
#include <cassert>
#include <algorithm>

namespace esve { namespace surface { namespace base {

template< typename T_Surface >
Rectangular_Boundaries<T_Surface>::
Rectangular_Boundaries()
    : m_list(),
      m_marked_vertices(),
      m_actual_list_end(m_list.end())
{
}

template< typename T_Surface >
Rectangular_Boundaries<T_Surface>::
~Rectangular_Boundaries()
{
}

template< typename T_Surface >
void
Rectangular_Boundaries<T_Surface>::
compute( const Surface & surface )
{
    const m_Vertices_size_type vertices_size = surface.vertices_size() ;

    m_actual_list_end = m_list.begin() ;

    m_marked_vertices.clear() ;
    m_marked_vertices.resize(vertices_size, false) ;

    for(;;)
    {
        m_Vertices_size_type start = 0 ;

        for( ; start != vertices_size ; ++start )
        {
            if( !m_marked_vertices[start]
                &&
                m_boundary_vertex(start, surface) )
            {
                break ;
            }
        }

        if( start == vertices_size )
        {
            // no more boundaries
            return ;
        }
        else
        {
            // found a vertex on some boundary

            if( m_actual_list_end == m_list.end() )
            {
                m_list.push_back(m_Vertex_Indexes()) ;
                m_actual_list_end = m_list.end() ;
            }
            else
            {
                ++m_actual_list_end ;
            }

            m_List_iterator back = m_actual_list_end ;
            --back ;

            m_compute_boundary(surface,
                               start,
                               m_marked_vertices,
                               *back) ;
        }
    }
}

//
// Sloppy and fast computation of boundaries --- don't distinguish
// between a one-polygon-wide section and no section at all.
//
template< typename T_Surface >
void
Rectangular_Boundaries<T_Surface>::
m_compute_boundary_fast(
    const T_Surface & surface,
    m_Vertex_Index start,
    m_Marked_Vertices & marked_vertices,
    m_Vertex_Indexes & boundary )
{
    boundary.clear() ;
    boundary.push_back(start) ;
    marked_vertices[start] = true ;

    for(;;)
    {
        m_Facets_Around_Vertex_const_iterator favi =
            surface.facets_around_vertex_begin(surface.vertices_begin() +
                                               boundary.back()) ;

        m_Facets_Around_Vertex_const_iterator end =
            surface.facets_around_vertex_end(surface.vertices_begin() +
                                             boundary.back()) ;

        m_Vertex_Indexes_size_type size = size = boundary.size() ;

        for( ; favi != end ; ++favi )
        {
            if( surface.facets(*favi).vertex_indexes_0() == boundary.back()
                &&
                !marked_vertices[surface.facets(*favi).vertex_indexes_1()]
                &&
                m_boundary_vertex(surface.facets(*favi).vertex_indexes_1(),
                                  surface) )
            {
                boundary.push_back(surface.facets(*favi).vertex_indexes_1()) ;
                marked_vertices[boundary.back()] = true ;
                break ;
            }

            if( surface.facets(*favi).vertex_indexes_1() == boundary.back()
                &&
                !marked_vertices[surface.facets(*favi).vertex_indexes_2()]
                &&
                m_boundary_vertex(surface.facets(*favi).vertex_indexes_2(),
                                  surface) )
            {
                boundary.push_back(surface.facets(*favi).vertex_indexes_2()) ;
                marked_vertices[boundary.back()] = true ;
                break ;
            }

            if( surface.facets(*favi).vertex_indexes_2() == boundary.back()
                &&
                !marked_vertices[surface.facets(*favi).vertex_indexes_3()]
                &&
                m_boundary_vertex(surface.facets(*favi).vertex_indexes_3(),
                                  surface) )
            {
                boundary.push_back(surface.facets(*favi).vertex_indexes_3()) ;
                marked_vertices[boundary.back()] = true ;
                break ;
            }

            if( surface.facets(*favi).vertex_indexes_3() == boundary.back()
                &&
                !marked_vertices[surface.facets(*favi).vertex_indexes_0()]
                &&
                m_boundary_vertex(surface.facets(*favi).vertex_indexes_0(),
                                  surface) )
            {
                boundary.push_back(surface.facets(*favi).vertex_indexes_0()) ;
                marked_vertices[boundary.back()] = true ;
                break ;
            }
        }

        if( size == boundary.size() )
        {
            break ;
        }
    }
}

template< typename T_Surface >
void
Rectangular_Boundaries<T_Surface>::
m_compute_boundary(
    const T_Surface & surface,
    m_Vertex_Index start,
    m_Marked_Vertices & marked_vertices,
    m_Vertex_Indexes & boundary )
{
    m_Pairs pairs ;
    pairs.reserve(20) ;

    m_Vertex_Indexes next_vertices ;
    next_vertices.reserve(20) ;

    boundary.clear() ;
    boundary.push_back(start) ;

    for(;;)
    {
        marked_vertices[boundary.back()] = true ;

        pairs.clear() ;
        next_vertices.clear() ;

        m_Facets_Around_Vertex_const_iterator favi =
            surface.facets_around_vertex_begin(surface.vertices_begin() +
                                               boundary.back()) ;

        m_Facets_Around_Vertex_const_iterator end =
            surface.facets_around_vertex_end(surface.vertices_begin() +
                                             boundary.back()) ;

        for( ; favi != end ; ++favi )
        {
            if( surface.facets(*favi).vertex_indexes_0() ==
                boundary.back() )
            {
                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_1(),
                    1)) ;

                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_3(),
                    -1)) ;
            }

            else if( surface.facets(*favi).vertex_indexes_1() ==
                     boundary.back() )
            {
                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_2(),
                    1)) ;

                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_0(),
                    -1)) ;
            }

            else if( surface.facets(*favi).vertex_indexes_2() ==
                     boundary.back() )
            {
                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_3(),
                    1)) ;

                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_1(),
                    -1)) ;
            }

            else
            {
                assert( surface.facets(*favi).vertex_indexes_3() ==
                        boundary.back() ) ;

                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_0(),
                    1)) ;

                pairs.push_back(m_Pair(
                    surface.facets(*favi).vertex_indexes_2(),
                    -1)) ;
            }
        }

        assert(pairs.size() >= 2) ;

        std::sort(pairs.begin(), pairs.end()) ;

        for( m_Pairs_const_iterator i = pairs.begin() ;
             i != pairs.end() ;
             ++i )
        {
            if( i != pairs.end() - 1
                &&
                (*i).vertex_index == (*(i + 1)).vertex_index )
            {
                ++i ;
            }
            else if( (*i).direction == 1 )
            {
                // found next vertex

                if( (*i).vertex_index == start )
                {
                    // done!
                    return ;
                }
                else
                {
                    next_vertices.push_back((*i).vertex_index) ;
                }
            }
        }

        assert(next_vertices.size() != 0) ;

        if( next_vertices.size() == 1 )
        {
            // a solid next vertex. continue on the path.
            boundary.push_back(next_vertices.back()) ;
        }
        else
        {
            // two quads connected by only one vertex.
            // "hanging chad"

            assert(next_vertices.size() == 2) ;

            if( boundary.size() == 1 )
            {
                // we just started; arbitrarily choose to go one way.
                boundary.push_back(next_vertices.back()) ;
            }
            else
            {
                // stay on the same quad.

                m_Facets_Around_Vertex_const_iterator favi =
                    surface.facets_around_vertex_begin(
                        surface.vertices_begin() +
                        boundary.back()) ;

                m_Facets_Around_Vertex_const_iterator end =
                    surface.facets_around_vertex_end(
                        surface.vertices_begin() +
                        boundary.back()) ;

                for( ; favi != end ; ++favi )
                {
                    if( surface.facets(*favi).vertex_indexes_0() ==
                        *(boundary.end() - 2)
                        &&
                        surface.facets(*favi).vertex_indexes_1() ==
                        *(boundary.end() - 1) )
                    {
                        boundary.push_back(
                            surface.facets(*favi).vertex_indexes_2()) ;
                        break ;
                    }

                    if( surface.facets(*favi).vertex_indexes_1() ==
                        *(boundary.end() - 2)
                        &&
                        surface.facets(*favi).vertex_indexes_2() ==
                        *(boundary.end() - 1) )
                    {
                        boundary.push_back(
                            surface.facets(*favi).vertex_indexes_3()) ;
                        break ;
                    }

                    if( surface.facets(*favi).vertex_indexes_2() ==
                        *(boundary.end() - 2)
                        &&
                        surface.facets(*favi).vertex_indexes_3() ==
                        *(boundary.end() - 1) )
                    {
                        boundary.push_back(
                            surface.facets(*favi).vertex_indexes_0()) ;
                        break ;
                    }

                    if( surface.facets(*favi).vertex_indexes_3() ==
                        *(boundary.end() - 2)
                        &&
                        surface.facets(*favi).vertex_indexes_0() ==
                        *(boundary.end() - 1) )
                    {
                        boundary.push_back(
                            surface.facets(*favi).vertex_indexes_1()) ;
                        break ;
                    }
                }

                assert(favi != end) ;
            }
        }
    }
}

}}} // namespace esve::surface::base

