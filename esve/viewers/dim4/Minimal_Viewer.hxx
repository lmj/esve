
#ifndef esve_viewers_dim4_Minimal_Viewer_hxx
#define esve_viewers_dim4_Minimal_Viewer_hxx

#include <esve/viewers/dim3/Minimal_Viewer.hxx>

namespace esve { namespace engine { namespace dim4 {

class Geom ;

}}} // namespace esve::engine::dim4

namespace esve { namespace viewers { namespace dim4 {

///
/// @class Minimal_Viewer esve/viewers/dim4/Minimal_Viewer.hxx
/// @brief Elementary viewer stuff.
///

class Minimal_Viewer
    : virtual public viewers::dim3::Minimal_Viewer
{
private:
    typedef viewers::dim3::Minimal_Viewer super ;

    Minimal_Viewer( const Minimal_Viewer & ) ;
    Minimal_Viewer & operator=( const Minimal_Viewer & ) ;
    
public:
    ///@{
    /// @brief Add a geometric object.
    virtual void add_geom( engine::dim4::Geom & ) = 0 ;
    /// @brief Remove a geometric object.
    virtual void remove_geom( engine::dim4::Geom & ) = 0 ;
    ///@}

    using super::add_geom ;
    using super::remove_geom ;

    virtual ~Minimal_Viewer() = 0 ;

protected:
    Minimal_Viewer() ;
} ;

}}} // namespace esve::viewers::dim4

#endif
