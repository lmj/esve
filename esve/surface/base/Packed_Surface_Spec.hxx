//
// A typical set of types for Packed_Surface
//

#ifndef esve_surface_base_Packed_Surface_Spec_hxx
#define esve_surface_base_Packed_Surface_Spec_hxx

#include <esve/base/dimn/vertex/tags.hxx>
#include <esve/math/quat.hxx>

namespace esve { namespace surface { namespace base {

namespace packed_surface_spec_private {

//////////////////////////////////////////////////////////////////
// select_manual_normalize 
//////////////////////////////////////////////////////////////////

template< typename T_Normal,
          bool manual_normalize >
struct select_manual_normalize ;

template< typename F >
struct select_manual_normalize<math::pure<F>, true>
{
    void operator()( math::pure<F> & normal )
    {
        normal /= abs(normal) ;
    }
} ;

template< typename T_Normal >
struct select_manual_normalize<T_Normal, false>
{
    void operator()( T_Normal & ) { }
} ;

//////////////////////////////////////////////////////////////////
// select_transformed_point
//////////////////////////////////////////////////////////////////

template< typename T_Vertex,
          typename T_has_transformed_point >
struct select_transformed_point ;

template< typename T_Vertex >
struct select_transformed_point<T_Vertex,
                                esve::base::dimn::vertex::tags::true_tag>
{
    typedef typename T_Vertex::Transformed_Point type ;
} ;

template< typename T_Vertex >
struct select_transformed_point<T_Vertex,
                                esve::base::dimn::vertex::tags::false_tag>
{
    typedef typename T_Vertex::Point type ;
} ;

//////////////////////////////////////////////////////////////////
// select_compute_facet_normal
//////////////////////////////////////////////////////////////////

template< typename T_Vertex,
          typename T_Normal,
          typename T_Transformed_Point,
          typename T_has_transformed_point >
struct select_compute_facet_normal ;

template< typename T_Vertex >
struct select_compute_facet_normal
       <
           T_Vertex,
           math::pure<typename T_Vertex::Point::value_type>,
           math::pure<typename T_Vertex::Normal::value_type>,
           esve::base::dimn::vertex::tags::true_tag
       >
{
    typedef T_Vertex Vertex ;
    typedef typename Vertex::Normal Normal ;

    Normal operator()( const Vertex & a,
                       const Vertex & b,
                       const Vertex & c )
    {
        const Normal normal =
            cross(b.transformed_point - a.transformed_point,
                  c.transformed_point - a.transformed_point) ;
        return normal/abs(normal) ;
    }
} ;

template< typename T_Vertex >
struct select_compute_facet_normal
       <
           T_Vertex,
           math::pure<typename T_Vertex::Point::value_type>,
           math::pure<typename T_Vertex::Normal::value_type>,
           esve::base::dimn::vertex::tags::false_tag
       >
{
    typedef T_Vertex Vertex ;
    typedef typename Vertex::Normal Normal ;

    Normal operator()( const Vertex & a,
                       const Vertex & b,
                       const Vertex & c )
    {
        const Normal normal =
            cross(b.point - a.point,
                  c.point - a.point) ;
        return normal/abs(normal) ;
    }
} ;

template< typename T_Vertex >
struct select_compute_facet_normal
       <
           T_Vertex,
           math::pure<typename T_Vertex::Normal::value_type>,
           math::quat<typename T_Vertex::Point::value_type>,
           esve::base::dimn::vertex::tags::true_tag
       >
{
    typedef T_Vertex Vertex ;
    typedef typename Vertex::Normal Normal ;

    Normal operator()( const Vertex & a,
                       const Vertex & b,
                       const Vertex & c )
    {
        const Normal normal =
            cross(purepart(b.transformed_point - a.transformed_point),
                  purepart(c.transformed_point - a.transformed_point)) ;
        return normal/abs(normal) ;
    }
} ;

template< typename T_Vertex >
struct select_compute_facet_normal
       <
           T_Vertex,
           math::pure<typename T_Vertex::Normal::value_type>,
           math::quat<typename T_Vertex::Point::value_type>,
           esve::base::dimn::vertex::tags::false_tag
       >
{
    typedef T_Vertex Vertex ;
    typedef typename Vertex::Normal Normal ;

    Normal operator()( const Vertex & a,
                       const Vertex & b,
                       const Vertex & c )
    {
        const Normal normal =
            cross(purepart(b.point - a.point),
                  purepart(c.point - a.point)) ;
        return normal/abs(normal) ;
    }
} ;

} // namespace packed_surface_spec_private

//////////////////////////////////////////////////////////////////
//
// Packed_Surface_Spec
//
//////////////////////////////////////////////////////////////////

template< typename T_Vertex,
          typename T_Facet,
          typename T_Facets_Around_Vertex >
class Packed_Surface_Spec
{
private:
    typedef T_Vertex m_Vertex ;
    typedef T_Facet m_Facet ;
    typedef T_Facets_Around_Vertex m_Facets_Around_Vertex ;

    typedef typename m_Vertex::Normal m_Normal ;
    typedef typename m_Vertex::has_transformed_point m_has_transformed_point ;

    typedef typename
    packed_surface_spec_private::select_transformed_point
    <
        m_Vertex,
        m_has_transformed_point
    >::type
    m_Transformed_Point ;

    typedef
    packed_surface_spec_private::select_compute_facet_normal
    <
        m_Vertex,
        m_Normal,
        m_Transformed_Point,
        m_has_transformed_point
    >
    m_Compute_Facet_Normal ;

    // Let OpenGL normalize by default.
    typedef
    packed_surface_spec_private::select_manual_normalize
    <
        m_Normal,
        false
    >
    m_Manual_Normalize ;

public:
    typedef m_Vertex Vertex ;
    typedef m_Facet Facet ;
    typedef m_Facets_Around_Vertex Facets_Around_Vertex ;
    typedef m_Compute_Facet_Normal Compute_Facet_Normal ;
    typedef m_Manual_Normalize Manual_Normalize ;
} ;

}}} // namespace esve::surface::base

#endif
