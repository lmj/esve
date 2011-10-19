
#ifndef esve_viewers_dimn_Minimal_Viewer_hxx
#define esve_viewers_dimn_Minimal_Viewer_hxx

namespace esve { namespace kernel { class Handler ; } }

namespace esve { namespace components { namespace dimn {

class Motion_Handler ;

}}} // namespace esve::engine::dimn

namespace esve { namespace viewers { namespace dimn {

///
/// @class Minimal_Viewer esve/viewers/dimn/Minimal_Viewer.hxx
/// @brief Elementary viewer stuff.
///

class Minimal_Viewer
{
public:
    /// Hand off control to the viewer.
    virtual int takeover() = 0 ;

    ///@{
    /// @brief Add a motion handler.
    virtual void add_handler( components::dimn::Motion_Handler & ) = 0 ;
    /// @brief Remove a motion handler.
    virtual void remove_handler( components::dimn::Motion_Handler & ) = 0 ;
    ///@}

    ///@{
    /// @brief Add a regular handler.
    virtual void add_handler( kernel::Handler & ) = 0 ;
    /// @brief Remove a regular handler.
    virtual void remove_handler( kernel::Handler & ) = 0 ;
    ///@}

    virtual ~Minimal_Viewer() = 0 ;

protected:
    Minimal_Viewer() ;

private:
    Minimal_Viewer( const Minimal_Viewer & ) ;
    Minimal_Viewer & operator=( const Minimal_Viewer & ) ;
} ;

}}} // namespace esve::viewers::dimn

#endif
