
#include <esve/types/Constants.hxx>
#include <esve/math/constants.hxx>
#include <limits>

namespace esve { namespace types {

const real Constants::PI      = math::constants::PI ;
const real Constants::TWO_PI  = math::constants::TWO_PI ;
const real Constants::PI_2    = math::constants::PI_2 ;
const real Constants::PI_4    = math::constants::PI_4 ;
const real Constants::SQRT2   = math::constants::SQRT2 ;
const real Constants::SQRT1_2 = math::constants::SQRT1_2 ;
const real Constants::E       = math::constants::E ;
const real Constants::LOG2E   = math::constants::LOG2E ;
const real Constants::LOG10E  = math::constants::LOG10E ;
const real Constants::LN2     = math::constants::LN2 ;
const real Constants::LN10    = math::constants::LN10 ;

const real Constants::MAX_REAL =
std::numeric_limits<real>::max() ;

const real Constants::MIN_REAL =
std::numeric_limits<real>::min() ;

}} // namespace esve::types
