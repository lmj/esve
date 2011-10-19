
#ifndef esve_components_dim3_Min_Z_hxx
#define esve_components_dim3_Min_Z_hxx

#include <esve/types/real.hxx>

namespace esve { namespace components { namespace dim3 {

///
/// @class Min_Z esve/components/dim3/Min_Z.hxx
/// @brief Report a minimum z-value.
///

class Min_Z
{
public:
    /// The minimum z-value being reported.
    virtual types::real min_z() const = 0 ;

    virtual ~Min_Z() = 0 ;

protected:
    Min_Z() ;

private:
    Min_Z( const Min_Z & ) ;
    Min_Z & operator=( const Min_Z & ) ;
} ;

}}} // namespace esve::components::dim3

#endif

