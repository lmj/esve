#ifndef esve_engine_dim4_Transform_hxx
#define esve_engine_dim4_Transform_hxx

#include <esve/base/dim4/Transform.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace engine { namespace dim4 {

///
/// @class Transform esve/engine/dim4/Transform.hxx
/// @brief Four-dimensional transforms with rotation, translation,
/// inversion, and scaling components.
///
/// These are Moebius transformations, which have the form
///
/// @verbatim f(z) = (a*z + b)*inv(c*z + d)@endverbatim
///
/// and are isomorphic to projective 2x2 quaternion matrix transformations
///
/// @verbatim
///   T [ z1 ] = [ a  b ] [ z1 ]
///     [ z2 ]   [ c  d ] [ z2 ]@endverbatim
///
/// Just as real 4x4 projective matrices represent 3D transformations
/// which carry a local rotation, origin, and a scaling factor, these
/// quaternionic 2x2 projective matrices represent 4D transformations
/// which carry a local rotation, origin, and a scaling factor --- as
/// well as a local infinity.
///
/// Moebius transformations blur the distinction between spheres and
/// planes, continuously transforming one into the other.  A plane is
/// merely a sphere with infinite radius, and a line is merely a
/// circle with infinite radius.
///

class Transform
{
private:
    typedef base::dim4::Transform<types::real> m_Transform ;
    m_Transform m ;

public:
    /// The group identity element.
    static const Transform IDENTITY ;

    ///@{
    /// @brief Construct the identity.
    Transform()
        :
        m()
    {
    }

    /// @brief Construct with these matrix elements.
    Transform( const types::quat & a,
               const types::quat & b,
               const types::quat & c,
               const types::quat & d )
        :
        m(a, b, c, d)
    {
    }

    /// @brief Copy.
    Transform( const Transform & a )
        :
        m(a.m)
    {
    }

    /// @brief Assignment.
    Transform & operator=( const Transform & a )
    {
        m = a.m ;
        return *this ;
    }
    ///@}


    /// @name Matrix elements
    ///
    /// @brief @verbatim f(z) = (a*z + b)*inv(c*z + d) @endverbatim
    /// See the description of Transform.
    ///

    ///@{
    /// @brief Upper-left.
    const types::quat & a() const
    {
        return m.a() ;
    }
    void a( const types::quat & a )
    {
        m.a(a) ;
    }
    ///@}

    ///@{
    /// @brief Upper-right.
    const types::quat & b() const
    {
        return m.b() ;
    }
    void b( const types::quat & b )
    {
        m.b(b) ;
    }
    ///@}

    ///@{
    /// @brief Lower-left.
    const types::quat & c() const
    {
        return m.c() ;
    }
    void c( const types::quat & c )
    {
        m.c(c) ;
    }
    ///@}

    ///@{
    /// @brief Lower-right.
    const types::quat & d() const
    {
        return m.d() ;
    }

    void d( const types::quat & d )
    {
        m.d(d) ;
    }
    ///@}

    /// @name Actions
    ///
    /// Relative actions on the current state.
    /// The basis argument is similarity-conjugated:
    /// @code
    ///     *this := basis*action*(basis)^(-1)*(*this)
    /// @endcode
    ///
    /// <tt>basis == IDENTITY</tt> means left action.
    /// <br> <tt>basis == *this</tt> means right action.
    ///@{

    /// *this := left * (*this)
    void left_act( const Transform & left )
    {
        m.left_act(left.m) ;
    }

    /// *this := (*this) * right
    void right_act( const Transform & right )
    {
        m.right_act(right.m) ;
    }

    /// General differential action.
    void act( const Transform & action,
              const Transform & basis )
    {
        m.act(action.m, basis.m) ;
    }

    ///
    /// @brief Rotate by angle alpha in the <em>(r, s)</em> plane;
    /// rotate by angle beta in the <em>(r, s)</em>-complement plane.
    ///
    /// Orientation is positive with @e r rotating toward @e s.
    /// @pre <em>r, s</em> must be orthonormal.
    ///
    void rotate( types::real alpha,
                 types::real beta,
                 const types::quat & r,
                 const types::quat & s,
                 const Transform & basis = IDENTITY ) ;

    ///
    /// @brief Rotate by angle alpha in the <em>(1, u)</em> plane;
    /// rotate by angle beta in the <em>(1, u)</em>-complement plane.
    ///
    /// Orientation is positive with @e 1 rotating toward @e u.
    /// @pre @e u is unit length.
    ///
    void rotate( types::real alpha,
                 types::real beta,
                 const types::pure & u,
                 const Transform & basis = IDENTITY ) ;

    /// @brief Move the local origin from @e g to <em>g' = g + r</em>.
    void translate( const types::quat & r,
                    const Transform & basis = IDENTITY ) ;


    /// @brief Move the local infinity from @e h to @e h' per the relation
    /// <em>(h')^(-1) = h^(-1) + r</em>.
    void invertate( const types::quat & r,
                    const Transform & basis = IDENTITY ) ;

    /// Scale from the current state by a factor of @e gamma.
    void scalate( types::real gamma,
                  const Transform & basis = IDENTITY ) ;
    ///@}

    /// @name Other operations
    ///
    ///@{

    /// *this := 1
    void identity()
    {
        m.identity() ;
    }

    /// *this := (*this)^(-1)
    void invert()
    {
        m.invert() ;
    }

    /// *this := t
    void assign( const Transform & h )
    {
        m = h.m ;
    }

    ///
    /// @brief Snap to upper-triangular with unitary diagonal elements.
    ///
    /// In other words, remove inversion and scaling, leaving only the
    /// rotation group with translations.
    ///
    /// After normalize(), the transformation will be of the form
    /// @verbatim f(z) = a*z*conj(d) + b*conj(d)@endverbatim
    /// where @em a and @em d are unitary.
    ///
    void normalize()
    {
        m.normalize() ;
    }

    /// Equal by value.
    bool operator==( const Transform & h ) const
    {
        return m.operator==(h.m) ;
    }

    /// Unequal by value.
    bool operator!=( const Transform & h ) const
    {
        return m.operator!=(h.m) ;
    }

    ///@}

    virtual ~Transform()
    {
    }
} ;

}}} // namespace esve::engine::dim4

#endif
