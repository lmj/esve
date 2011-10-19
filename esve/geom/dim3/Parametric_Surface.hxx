
#ifndef esve_geom_dim3_Parametric_Surface_hxx
#define esve_geom_dim3_Parametric_Surface_hxx

#include <esve/geom/dimn/selectors_impl.hxx>

namespace esve { namespace geom { namespace dim3 {

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

    typedef typename m_Base::Spec m_Spec ;
    typedef typename m_Base::Vertex m_Vertex ;
    typedef typename m_Base::Vertices_iterator m_Vertices_iterator ;
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
    void draw() ;
    void compute() ;
} ;

}}} // namespace esve::geom::dim3

#include <esve/geom/dim3/Parametric_Surface.template.cxx>

#endif

