
#ifndef esve_viewers_dimn_Scaling_hxx
#define esve_viewers_dimn_Scaling_hxx

#include <esve/types/real.hxx>

namespace esve { namespace viewers { namespace dimn {

/// @if details
///
/// @class Scaling esve/viewers/dimn/Scaling.hxx
/// @brief Generic scaling value.
///
/// @endif

class Scaling
{
public:
    virtual void scaling( types::real ) = 0 ;
    virtual types::real scaling() const = 0 ;

    virtual ~Scaling() = 0 ;

protected:
    Scaling() ;

private:
    Scaling( const Scaling & ) ;
    Scaling & operator=( const Scaling & ) ;
} ;

}}} // namespace esve::viewers::dimn

#endif
