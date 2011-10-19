
#ifndef esve_engine_dimn_Materials_Stowed_hxx
#define esve_engine_dimn_Materials_Stowed_hxx

namespace esve { namespace engine { namespace dimn {

class Materials ;

///
/// @class Materials_Stowed esve/engine/dimn/Materials_Stowed.hxx
/// @brief Stowed materials.
///
/// A method whose name begins with "peek" is guaranteed to always
/// return the same reference (for a given instance).
///

class Materials_Stowed
{
public:
    ///@{
    /// @brief Peek at the materials.
    virtual const engine::dimn::Materials & peek_materials() const = 0 ;
    virtual engine::dimn::Materials & peek_materials() = 0 ;
    ///@}

    virtual ~Materials_Stowed() = 0 ;

protected:
    Materials_Stowed() ;

private:
    Materials_Stowed( const Materials_Stowed & ) ;
    Materials_Stowed & operator=( const Materials_Stowed & ) ;
} ;

}}} // namespace esve::engine::dimn

#endif


