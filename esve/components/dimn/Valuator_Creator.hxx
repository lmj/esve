
#ifndef esve_components_dimn_Valuator_Creator_hxx
#define esve_components_dimn_Valuator_Creator_hxx

#include <esve/types/real.hxx>
#include <string>

namespace esve { namespace components { namespace dimn {

template< typename T_Valuat > class Valuator ;

///
/// @class Valuator_Creator esve/components/dimn/Valuator_Creator.hxx
/// @brief Create valuators.
///

template< typename T_Value >
class Valuator_Creator
{
public:
    /// Create a valuator.
    virtual
    Valuator<T_Value> &
    create_valuator( const T_Value & initial_value,
                     const std::string & label ) = 0 ;

    virtual ~Valuator_Creator() { }

protected:
    Valuator_Creator() { }

private:
    Valuator_Creator( const Valuator_Creator & ) ;
    Valuator_Creator & operator=( const Valuator_Creator & ) ;
} ;

// real specialization. pass by value.
template<>
class Valuator_Creator<types::real>
{
public:
    /// Create a valuator.
    virtual
    Valuator<types::real> &
    create_valuator( types::real initial_value,
                     const std::string & label ) = 0 ;

    virtual ~Valuator_Creator() { }

protected:
    Valuator_Creator() { }

private:
    Valuator_Creator( const Valuator_Creator & ) ;
    Valuator_Creator & operator=( const Valuator_Creator & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

