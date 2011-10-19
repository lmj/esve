
#ifndef esve_components_dimn_Valuator_hxx
#define esve_components_dimn_Valuator_hxx

#include <esve/ui/extra/Widget.hxx>
#include <esve/types/complex.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Valuator esve/components/dimn/Valuator.hxx
/// @brief A user-interface widget representing a given value type.
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
/// The facilities of kernel::Caching_Node and kernel::Caching_Server
/// solve the issue of handle() being emitted before an object is
/// fully constructed.  As of this writing, all front-ends use
/// Simple_Kernel which caches handle() messages during the
/// startup/construction phase.
///

template< typename T_Value >
class Valuator
    : public ui::extra::Widget
{
public:
    /// Query the current value.
    virtual T_Value value() const = 0 ;

    ///
    /// @brief Assign a new value.
    ///
    /// @return *this
    ///
    virtual Valuator & value( const T_Value & ) = 0 ;

    ///
    /// @brief Set the increment in which the value changes.
    /// @return *this
    ///
    virtual Valuator & step( const T_Value & ) = 0 ;

    ///
    /// @brief Set the allowable range of values.
    /// @return *this
    ///
    virtual
    Valuator &
    range( const T_Value & min_corner,
           const T_Value & max_corner ) = 0 ;

protected:
    Valuator() { }

    // creator owns it
    ~Valuator() { }

private:
    Valuator( const Valuator & ) ;
    Valuator & operator=( const Valuator & ) ;
} ;

template<>
class Valuator<types::real>
    : public ui::extra::Widget
{
public:
    /// Query the current value.
    virtual types::real value() const = 0 ;

    ///
    /// @brief Assign a new value.
    /// @return *this
    ///
    virtual Valuator & value( types::real ) = 0 ;

    ///
    /// @brief Set the increment in which the value changes.
    /// @return *this
    ///
    virtual Valuator & step( types::real ) = 0 ;

    ///
    /// @brief Set the allowable range of values.
    /// @return *this
    ///
    virtual
    Valuator &
    range( types::real min, types::real max ) = 0 ;

protected:
    Valuator() { }

    // creator owns it
    ~Valuator() { }

private:
    Valuator( const Valuator & ) ;
    Valuator & operator=( const Valuator & ) ;
} ;

template<>
class Valuator<types::complex>
    : public ui::extra::Widget
{
public:
    /// Query the current value.
    virtual types::complex value() const = 0 ;

    ///@{
    ///
    /// @brief Assign a new value.
    /// @return *this
    ///
    virtual Valuator & value( const types::complex & ) = 0 ;
    virtual Valuator & value( types::real , types::real ) = 0 ;
    ///@}

    ///@{
    ///
    /// @brief Set the increment in which the value changes.
    /// @return *this
    ///
    virtual Valuator & step( const types::complex & ) = 0 ;
    virtual Valuator & step( types::real, types::real ) = 0 ;
    ///@}

    ///
    /// @brief Set the allowable range of values.
    /// @return *this
    ///
    virtual
    Valuator &
    range( const types::complex & lower_left_corner,
           const types::complex & upper_right_corner ) = 0 ;

protected:
    Valuator() { }

    // creator owns it
    ~Valuator() { }

private:
    Valuator( const Valuator & ) ;
    Valuator & operator=( const Valuator & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

