//
// Given a complex polynomial with real coefficients,
//
//     f: C --> C
//
// there is a set of curves on the domain which yield values of f(z)
// which are strictly real,
//
//     f: {curves in C} --> R
//
// To draw these curves, choose small epsilon and show only the portion
// of the surface for which
//
//     abs(imag(f(z))) < epsilon
//

#ifndef apps_polynomialviewer_Polynomial_Surface_hxx
#define apps_polynomialviewer_Polynomial_Surface_hxx

#include <esve/geom/dim3/Parametric_Surface.hxx>
#include <esve/geom/dim3/Parametric_Surface_Spec.hxx>
#include <esve/base/dimn/vertex/CNPTD_Vertex.hxx>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

namespace polysurf_private {

template< typename complex, typename Forward_Iterator >
complex
evaluate_polynomial(
                    // point to be evaluated
                    const complex & z,

                    // highest power coeff
                    Forward_Iterator begin,

                    // one-past constant coeff
                    Forward_Iterator end )
{
    assert(begin != end) ;

    complex res(*begin) ;
    ++begin ;

    for( ; begin != end ; ++begin )
    {
        res = res*z + *begin ;
    }

    return res ;
}

struct Polynomial_Surface_Spec
    : public esve::geom::dim3::Parametric_Surface_Spec
{
    // different than a regular 3D surface -- Point is a quat
    typedef quat Point ;

    typedef complex Transformed_Domain_Point ;
    typedef complex Domain_Point ;

    typedef
    esve::base::dimn::vertex::CNPTD_Vertex
    <
        Color,
        Normal,
        Point,
        Transformed_Domain_Point,
        Domain_Point
    >
    Vertex ;

    typedef
    esve::geom::dimn::selectors::category::clipped
    category_selector ;

    typedef
    esve::geom::dimn::selectors::topology::plane
    topology_selector ;

    typedef
    esve::geom::dimn::selectors::postcompute::no
    postcompute_selector ;

    std::vector<real> coeffs ;
    real refz_scale ;
    real realcurves_epsilon ;
    real color_scale ;

    Polynomial_Surface_Spec()
        : coeffs(),
          refz_scale(1.0),
          realcurves_epsilon(0.10),
          color_scale(1.0)
    {
        coeffs.push_back(0) ;
    }

    complex domain( const complex & unit_square ) const
    {
        return real(6)*unit_square - complex(real(3), real(3)) ;
    }

    bool domain_clip( const complex & ,
                      const complex & ) const
    {
        return false ;
    }

    quat surface( const complex & ,
                  const complex & domain ) const
    {
        const complex fz =
            evaluate_polynomial(domain,
                                coeffs.rbegin(),
                                coeffs.rend()) ;

        return quat(fz.imag(),
                    domain.real(),
                    domain.imag(),
                    refz_scale*fz.real()) ;
    }

    bool surface_clip( const complex & ,
                       const complex & ,
                       const quat & surface ) const
    {
        return std::abs(surface.w()) >= realcurves_epsilon ;
    }

    rgba color( const complex & ,
                const complex & ,
                const quat & surface ) const
    {
        return rgba::from_hsva(
                   std::min(
                       color_scale*std::sqrt(
                           surface.z()*surface.z() +
                           surface.w()*surface.w()),
                       real(0.7)),
                   0.7,
                   1.0,
                   1.0) ;
    }
} ;

struct Polynomial_Surface_Data
{
    Polynomial_Surface_Spec spec ;

    Polynomial_Surface_Data()
        : spec() { }
} ;

} // namespace polysurf_private

class Polynomial_Surface
    : private polysurf_private::Polynomial_Surface_Data,
      public esve::geom::dim3::Parametric_Surface
             <
                 polysurf_private::Polynomial_Surface_Spec
             >
{
private:
    typedef
    polysurf_private::Polynomial_Surface_Data
    m_Data ;

    typedef
    esve::geom::dim3::Parametric_Surface
             <
                 polysurf_private::Polynomial_Surface_Spec
             >
    m_Base ;

public:
    ///////////////////////////////////////
    // types

    typedef polysurf_private::Polynomial_Surface_Spec::real real ;
    typedef std::vector<real>::const_iterator Coeffs_const_iterator ;

    ///////////////////////////////////////
    // Constructor
    Polynomial_Surface() ;

    ///////////////////////////////////////
    // compiler writes memberwise copy and assign

    ///////////////////////////////////////
    // epsilon as described above

    real realcurves_epsilon() const
    {
        return m_Data::spec.realcurves_epsilon ;
    }

    void realcurves_epsilon( real ) ;

    ///////////////////////////////////////
    // color gradient around roots

    real color_scale() const
    {
        return m_Data::spec.color_scale ;
    }

    void color_scale( real ) ;

    ///////////////////////////////////////
    // scale the real part of f(z)

    real refz_scale() const
    {
        return m_Data::spec.refz_scale ;
    }

    void refz_scale( real ) ;

    ///////////////////////////////////////
    // read current coefficients

    Coeffs_const_iterator coeffs_begin() const
    {
        return m_Data::spec.coeffs.begin() ;
    }

    Coeffs_const_iterator coeffs_end() const
    {
        return m_Data::spec.coeffs.end() ;
    }

    ///////////////////////////////////////
    // set new coefficients
    template< typename Input_Iterator >
    void coeffs( Input_Iterator begin, Input_Iterator end ) ;

    ~Polynomial_Surface() ;
} ;

template< typename Input_Iterator >
void
Polynomial_Surface::
coeffs( Input_Iterator begin, Input_Iterator end )
{
    assert(begin != end) ;

    m_Data::spec.coeffs.clear() ;

    for( ; begin != end ; ++begin )
    {
        m_Data::spec.coeffs.push_back(*begin) ;
    }

    m_Base::update_surface() ;
}

#endif
