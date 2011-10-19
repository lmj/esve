
#ifndef esve_geom_dim4_Parametric_Surface_hxx
#define esve_geom_dim4_Parametric_Surface_hxx

#include <esve/geom/dimn/selectors_impl.hxx>
#include <esve/util/member_iterator.hxx>

namespace esve { namespace geom { namespace dim4 {

template< typename T_Spec >
class Parametric_Surface
    : public dimn::selectors_impl::select_category
             <
                 T_Spec,
                 typename T_Spec::category_selector
             >::type
{
private:
    typedef typename
    dimn::selectors_impl::select_category
             <
                 T_Spec,
                 typename T_Spec::category_selector
             >::type
    m_Base ;

    typedef typename m_Base::Vertex m_Vertex ;
    typedef typename m_Base::Vertices_iterator m_Vertices_iterator ;

    typedef typename
    m_Base::Vertices_const_iterator
    m_Vertices_const_iterator ;

    typedef typename m_Vertex::Point m_Point ;
    typedef typename m_Vertex::Transformed_Point m_Transformed_Point ;
    typedef typename m_Base::Spec m_Spec ;
    typedef typename m_Spec::topology_selector m_topology_selector ;
    typedef typename m_Spec::postcompute_selector m_postcompute_selector ;

    Parametric_Surface( const Parametric_Surface & ) ;
    Parametric_Surface & operator=( const Parametric_Surface & ) ;

    void m_postcompute( dimn::selectors::postcompute::yes ) ;
    void m_postcompute( dimn::selectors::postcompute::no ) { }

    const m_Spec & m_spec ;

public:
    typedef m_Spec Spec ;

    Parametric_Surface( const Spec & ) ;
    ~Parametric_Surface() ;

protected:
    //////////////////////////////////////////////////////
    // system
    //////////////////////////////////////////////////////

    typedef
    util::member_iterator< m_Vertices_const_iterator,
                           const m_Point,
                           &m_Vertex::point >
    Points_iterator ;

    typedef
    util::member_iterator< m_Vertices_iterator,
                           m_Transformed_Point,
                           &m_Vertex::transformed_point >
    Transformed_Points_iterator ;

    // OpenGL
    virtual void draw() ;

    // 4d frame engine

    Points_iterator points_begin() const
    {
        return Points_iterator(m_Base::vertices_begin()) ;
    }

    Points_iterator points_end() const
    {
        return Points_iterator(m_Base::vertices_end()) ;
    }

    Transformed_Points_iterator transformed_points_begin()
    {
        return Transformed_Points_iterator(m_Base::vertices_begin()) ;
    }

    virtual void pretransform() ;
    virtual void posttransform() ;
} ;

}}} // namespace esve::geom::dim4

#include <esve/geom/dim4/Parametric_Surface.template.cxx>

#endif

