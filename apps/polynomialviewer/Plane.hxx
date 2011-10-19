
#ifndef apps_polynomialviewer_Plane_hxx
#define apps_polynomialviewer_Plane_hxx

#include <esve/geom/dim3/Parametric_Surface.hxx>
#include <esve/geom/dim3/Parametric_Surface_Spec.hxx>

namespace plane_private {

struct Plane_Spec : public esve::geom::dim3::Parametric_Surface_Spec
{
    typedef
    esve::geom::dimn::selectors::category::regular
    category_selector ;

    typedef
    esve::geom::dimn::selectors::topology::plane
    topology_selector ;

    typedef
    esve::geom::dimn::selectors::postcompute::no
    postcompute_selector ;

    real size ;
    real fade ;

    Plane_Spec()
        : size(5.0),
          fade(0.2) { }

    complex domain( const complex & unit_square ) const
    {
        return real(2)*unit_square - complex(1, 1) ;
    }

    pure surface( const complex & unit_square,
                  const complex & domain ) const
    {
        return pure(size*domain.real(), size*domain.imag(), 0) ;
    }

    rgba color( const complex & unit_square,
                const complex & domain,
                const pure & surface ) const
    {
        return rgba(1, 1, 1, fade) ;
    }
} ;

struct Plane_Data
{
    Plane_Spec spec ;
    Plane_Data()
        : spec() { }
} ;

} // namespace plane_private

class Plane
    : private plane_private::Plane_Data,
      public esve::geom::dim3::Parametric_Surface<plane_private::Plane_Spec>
{
private:
    typedef
    plane_private::Plane_Data
    m_Data ;

    typedef
    esve::geom::dim3::Parametric_Surface<plane_private::Plane_Spec>
    m_Base ;

public:
    Plane() ;

    // compiler writes memberwise copy and assign

    real size() const
    {
        return m_Data::spec.size ;
    }

    void size( real ) ;

    real fade() const
    {
        return m_Data::spec.fade ;
    }

    void fade( real ) ;

    ~Plane() ;
} ;

#endif

