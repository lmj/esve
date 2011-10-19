
#ifndef esve_components_dimn_Inertial_Motion_Handler_hxx
#define esve_components_dimn_Inertial_Motion_Handler_hxx

#include <esve/types/real.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Inertial_Motion_Handler esve/components/dimn/Inertial_Motion_Handler.hxx
/// @brief Motion Handlers with inertia.
///

class Inertial_Motion_Handler
{
public:
    /// Stop all motion.
    virtual void stop() = 0 ;

    ///@{
    /// @brief Scalar multiplier for all motion.
    virtual types::real sensitivity() const = 0 ;
    virtual void sensitivity( types::real ) = 0 ;
    ///@}

    virtual ~Inertial_Motion_Handler() = 0 ;

protected:
    Inertial_Motion_Handler() ;

private:
    Inertial_Motion_Handler( const Inertial_Motion_Handler & ) ;
    Inertial_Motion_Handler & operator=( const Inertial_Motion_Handler & ) ;
} ;

}}} // namespace esve::components::dimn

#endif
