#ifndef esve_engine_dim3_Transform_hxx
#define esve_engine_dim3_Transform_hxx

#include <esve/base/dim3/Transform.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Transform esve/engine/dim3/Transform.hxx
/// @brief Three-dimensional transforms with rotation, translation,
/// and scaling components.
///
/// Transforms are implemented as upper-triangular Moebius
/// transformations of the form
///
/// @verbatim
/// [ s  0 ][ 1  t ][ r  0 ] = [ s*r  s*t*r ]
/// [ 0  1 ][ 0  1 ][ 0  r ]   [  0     r   ]@endverbatim
///
/// where @c s is real, @c t is pure, and @c r is unitary.
///
/// Concatenation gives
///
/// @verbatim
/// [ s1*r1  s1*t1*r1 ][ s2*r2  s2*t2*r2 ]
/// [   0       r1    ][   0       r2    ]
///
///     = [ (s1*s2)(r1*r2)  (s1*s2)*(r1*t2*conj(r1) + (1/s2)*t1)*(r1*r2) ]
///       [       0                            r1*r2                     ]@endverbatim
///
/// and the inverse is
///
/// @verbatim
/// [ conj(r)     0    ][ 1  -t ][ 1/s  0 ]
/// [    0     conj(r) ][ 0   1 ][  0   1 ]
///
///     = [ (1/s)*conj(r)  (1/s)*(-s*conj(r)*t*r)*conj(r) ]
///       [       0                    conj(r)            ]@endverbatim
///
/// Thus we have found a subgroup of Moebius transformations
/// consisting of operations within R^3.
///
/// In the public interface, @c r is rotation(), @c t is
/// translation(), and @c s is scaling().
///
/// The order in which these compositional matrices are applied
/// matches that of the 4x4 projective transformations used by OpenGL.
/// In the real-projective (column-major) representation, @c s
/// corresponds to the reciprocal of the lower-right entry, @c t
/// corresponds to the 3x1 upper-right column, and @c r corresponds to
/// the 3x3 upper-left minor.  (Of course, there is a bijective
/// correspondence between unit quaternions mod sign and real
/// (unitary) orthogonal 3x3 matrices, both being representations of
/// SO(3).)
///
///@verbatim
/// +-----------+ +---+     +-----------+ +---+     +-----------+ +---+
/// |           | |   |     |           | |   |     |           | |   |
/// |           | |   |     |           | |   |     |           | |   |
/// |     1     | | 0 |     |     1     | | t |     |     r     | | 0 |
/// |           | |   |  *  |           | |   |  *  |           | |   |
/// |           | |   |     |           | |   |     |           | |   |
/// +-----------+ +---+     +-----------+ +---+     +-----------+ +---+
/// +-----------+ +---+     +-----------+ +---+     +-----------+ +---+
/// |     0     | |1/s|     |     0     | | 1 |     |     0     | | 1 |
/// +-----------+ +---+     +-----------+ +---+     +-----------+ +---+
///
///
///          +-----------+ +---+
///          |           | |   |
///          |           | |   |
///      =   |     r     | | t |
///          |           | |   |
///          |           | |   |
///          +-----------+ +---+
///          +-----------+ +---+
///          |     0     | |1/s|
///          +-----------+ +---+
///@endverbatim

class Transform
{
private:
    typedef
    base::dim3::Transform<types::real>
    m_Transform ;

    m_Transform m ;

public:
    /// The group identity element.
    static const Transform IDENTITY ;

    /// Construct the identity.
    Transform()
        :
        m()
    {
    }

    /// Constructor.
    Transform( const types::quat & rotation,
               const types::pure & translation = types::pure(),
               types::real scaling = types::real(1) )
        :
        m(rotation,
          translation,
          scaling)
    {
    }

    /// Copy.
    Transform( const Transform & a )
        :
        m(a.m)
    {
    }

    /// Assignment.
    Transform & operator=( const Transform & a )
    {
        m = a.m ;
        return *this ;
    }

    ///@{
    ///
    /// @name Matrix elements
    /// @brief See the description of Transform.
    ///

    ///@{
    /// @brief Rotation state.
    /// @pre unit length
    const types::quat & rotation() const
    {
        return m.rotation() ;
    }
    void rotation( const types::quat & a )
    {
        m.rotation(a) ;
    }
    ///@}

    ///@{
    /// @brief Translation state.
    const types::pure & translation() const
    {
        return m.translation() ;
    }

    void translation( const types::pure & a )
    {
        m.translation(a) ;
    }
    ///@}

    ///@{
    /// @brief Scaling state.
    types::real scaling() const
    {
        return m.scaling() ;
    }

    void scaling( types::real a )
    {
        m.scaling(a) ;
    }
    ///@}

    ///@}

    ///@{
    ///
    /// @name Actions
    ///
    /// The basis argument is similarity-conjugated:
    /// @code
    ///     *this := basis*action*(basis)^(-1)*(*this)
    /// @endcode
    ///
    /// <tt>basis == IDENTITY</tt> means left action. <br>
    /// <tt>basis == *this</tt> means right action.

    /// *this := a * (*this)
    void left_act( const Transform & a )
    {
        m.left_act(a.m) ;
    }

    /// *this := (*this) * a
    void right_act( const Transform & a )
    {
        m.right_act(a.m) ;
    }

    /// General differential action.
    void act( const Transform & action,
              const Transform & basis = IDENTITY )
    {
        m.act(action.m, basis.m) ;
    }

    /// @brief Rotate around this axis by this angle (in radians).
    /// The axis must have unit length.
    void rotate( types::real angle,
                 const types::pure & axis,
                 const Transform & basis = IDENTITY ) ;

    /// @brief *this := (*this) + dt
    void translate( const types::pure & dt,
                    const Transform & basis = IDENTITY ) ;

    /// @brief *this := (*this)*ds
    void scalate( types::real ds,
                  const Transform & basis = IDENTITY ) ;
    ///@}

    ///@{
    ///
    /// @name Other operations
    ///

    /// *this := (*this)^(-1)
    void invert()
    {
        m.invert() ;
    }

    /// *this := a
    void assign( const Transform & a )
    {
        m = a.m ;
    }

    /// @brief Snap to closest orthogonal transform.
    /// The translation component is retained.
    void normalize()
    {
        m.normalize() ;
    }

    /// Equal by value.
    bool operator==( const Transform & a ) const
    {
        return m.operator==(a.m) ;
    }

    /// Unequal by value.
    bool operator!=( const Transform & a ) const
    {
        return m.operator!=(a.m) ;
    }

    void identity()
    {
        m.identity() ;
    }

    ///@}

    virtual ~Transform()
    {
    }
} ;

}}} // namespace esve::engine::dim3

#endif

