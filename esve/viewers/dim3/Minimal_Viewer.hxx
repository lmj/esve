
#ifndef esve_viewers_dim3_Minimal_Viewer_hxx
#define esve_viewers_dim3_Minimal_Viewer_hxx

#include <esve/viewers/dimn/Minimal_Viewer.hxx>

namespace esve { namespace engine { namespace dim3 {

class Geom ;

}}} // namespace esve::engine::dim3

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Minimal_Viewer esve/viewers/dim3/Minimal_Viewer.hxx
/// @brief Elementary viewer stuff.
///

class Minimal_Viewer
    : virtual public viewers::dimn::Minimal_Viewer
{
public:
    ///@{
    /// @brief Add a geometric object.
    virtual void add_geom( engine::dim3::Geom & ) = 0 ;
    /// @brief Remove a geometric object.
    virtual void remove_geom( engine::dim3::Geom & ) = 0 ;
    ///@}

    virtual ~Minimal_Viewer() = 0 ;

protected:
    Minimal_Viewer() ;

private:
    Minimal_Viewer( const Minimal_Viewer & ) ;
    Minimal_Viewer & operator=( const Minimal_Viewer & ) ;
} ;

}}} // namespace esve::viewers::dim3

#endif
