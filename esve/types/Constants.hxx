
#ifndef esve_types_Constants_hxx
#define esve_types_Constants_hxx

#include <esve/types/real.hxx>
#include <esve/math/misc.hxx>

namespace esve { namespace types {

///
/// @class Constants esve/types/Constants.hxx
/// @brief Misc math constants.
///

struct Constants
{
    /// .
    static const real PI ;
    /// .
    static const real TWO_PI ;
    /// .
    static const real PI_2 ;
    /// .
    static const real PI_4 ;
    /// .
    static const real SQRT2 ;
    /// .
    static const real SQRT1_2 ;
    /// .
    static const real E ;
    /// .
    static const real LOG2E ;
    /// .
    static const real LOG10E ;
    /// .
    static const real LN2 ;
    /// .
    static const real LN10 ;
    /// .
    static const real MAX_REAL ;
    /// .
    static const real MIN_REAL ;

protected:
    // prevent polymorphic use
    ~Constants() { }
} ;

}} // namespace esve::types

#endif
