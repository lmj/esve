
#ifndef esve_components_dimn_Supermouse_hxx
#define esve_components_dimn_Supermouse_hxx

#include <esve/types/pure.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Supermouse esve/components/dimn/Supermouse.hxx
/// @brief The current state the supermouse (three-dimensional input).
///
/// This also represents a regular mouse (with z-coordinate of zero).
///

class Supermouse
{
public:
    /// Supermouse buttons.
    enum Button
    {
        /// .
        LEFT,
        /// .
        MIDDLE,
        /// .
        RIGHT // determines NUM_BUTTONS
    } ;

    static const unsigned int NUM_BUTTONS = RIGHT + 1 ;

    /// Where is the pointer?
    virtual const types::pure & position() const = 0 ;

    /// Is this button pushed?
    virtual bool pushed( Button a ) const = 0 ;

    virtual ~Supermouse() = 0 ;

protected:
    Supermouse() ;

private:
    Supermouse( const Supermouse & ) ;
    Supermouse & operator=( const Supermouse & ) ;
} ;

}}} // namespace esve::components::dimn

#endif
