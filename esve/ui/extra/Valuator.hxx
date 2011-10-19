
#ifndef esve_ui_extra_Valuator_hxx
#define esve_ui_extra_Valuator_hxx

#include <esve/ui/extra/Widget.hxx>

namespace esve { namespace ui { namespace extra {

///
/// @class Valuator esve/ui/extra/Valuator.hxx
/// @brief A user-interface widget representing a floating point
/// value.
///
/// Keep in mind that modifying the value in code (even implicitly
/// with step() or range()) has a side-effect: it will send a
/// handle_*() message as if the user changed it.
///
/// Setting the value within handle() itself is OK; the recursion is
/// detected and consequently ignored.
///
/// This side-effect of emitting handle() in response to changing the
/// value may seem surprising at first, but in the end it is the right
/// thing.  One should not depend upon the kindness of programmers to
/// manually call update() every time they change something in code.
///
/// The facilities of Caching_Server and Caching_Emitter solve the
/// issue of handle() being emitted before an object is fully
/// constructed.  As of this writing, all front-ends use Simple_Kernel
/// which caches handle() messages during startup/construction phase.
///

class Valuator
    : public Widget
{
public:
    /// Query the current value.
    virtual double value() const = 0 ;

    ///
    /// @brief Assign a new value.
    /// @return *this
    ///
    virtual Valuator & value( double ) = 0 ;

    ///
    /// @brief Set the increment in which the value changes.
    /// @return *this
    ///
    virtual Valuator & step( double ) = 0 ;

    ///
    /// @brief Set the allowable range of values.
    /// @return *this
    ///
    virtual Valuator & range( double min, double max ) = 0 ;

protected:
    Valuator() ;

    // creator owns it
    ~Valuator() = 0 ;

private:
    Valuator( const Valuator & ) ;
    Valuator & operator=( const Valuator & ) ;
} ;

}}} // namespace esve::ui::extra

#endif

