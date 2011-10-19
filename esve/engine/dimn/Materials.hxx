
#ifndef esve_engine_dimn_Materials_hxx
#define esve_engine_dimn_Materials_hxx

#include <esve/types/rgba.hxx>

namespace esve { namespace engine { namespace dimn {

///
/// @class Materials esve/engine/dimn/Materials.hxx
/// @brief OpenGL material colors.
///

class Materials
{
public:
    Materials() ;

    ///@{
    virtual const types::rgba & ambient() const ;
    virtual void ambient( const types::rgba & ) ;
    ///@}

    ///@{
    virtual const types::rgba & diffuse() const ;
    virtual void diffuse( const types::rgba & ) ;
    ///@}

    ///@{
    virtual const types::rgba & specular() const ;
    virtual void specular( const types::rgba & ) ;
    ///@}

    virtual ~Materials() ;

private:
    Materials( const Materials & ) ;
    Materials & operator=( const Materials & ) ;

    types::rgba m_ambient ;
    types::rgba m_diffuse ;
    types::rgba m_specular ;
} ;

}}} // namespace esve::engine::dimn

#endif


