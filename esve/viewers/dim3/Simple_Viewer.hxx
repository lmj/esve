
#ifndef esve_viewers_dim3_Simple_Viewer_hxx
#define esve_viewers_dim3_Simple_Viewer_hxx

#include <esve/viewers/dim3/Minimal_Viewer.hxx>
#include <esve/viewers/dim3/Auto_Widgets.hxx>
#include <esve/viewers/dimn/Simple_Viewer.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <string>
#include <memory>

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Simple_Viewer esve/viewers/dim3/Simple_Viewer.hxx
/// @brief A simplified front-end to the three-dimensional engine.
///

class Simple_Viewer
    : virtual protected Auto_Widgets,
      virtual protected viewers::dimn::Simple_Viewer,
      virtual protected viewers::dim3::Minimal_Viewer
{
public:
    /// Constructor.  Give the arguments from main().
    Simple_Viewer( int argc,
                   char** argv,
                   const std::string & label = "simple3d" ) ;

    int takeover() ;

    ~Simple_Viewer() ;

protected:
    ///////////////////////////////////////////////////////
    // Simple_Viewer
    ///////////////////////////////////////////////////////

    const std::string & help_text() const ;
    void initialize() ;

    ///////////////////////////////////////////////////////
    // Minimal_Viewer
    ///////////////////////////////////////////////////////

    void add_geom( engine::dim3::Geom & ) ;
    void remove_geom( engine::dim3::Geom & ) ;

    ///////////////////////////////////////////////////////
    // Simple_UI
    ///////////////////////////////////////////////////////

    void create_label( const std::string & label ) ;

    // (doxygen bug workaround)
    /// Create a valuator.
    Valuator &
    create_valuator( real initial_value,
                     const std::string & label = "" ) ;

    Complex_Valuator &
    create_valuator( const complex & initial_value,
                     const std::string & label = "" ) ;

    Pure_Valuator &
    create_valuator( const pure & initial_value,
                     const std::string & label = "" ) ;

    Quat_Valuator &
    create_valuator( const quat & initial_value,
                     const std::string & label = "" ) ;

    Toggle &
    create_toggle( bool initial_value,
                   const std::string & label ) ;

    File_Selector &
    create_file_selector( const std::string & initial_value = "",
                          const std::string & label = "file",
                          const std::string & selector_label = "select a file",
                          const std::string & initial_directory = ".",
                          const std::string & filter = "*" ) ;

    void create_help( const std::string & text,
                      const std::string & label = "help" ) ;

    ///////////////////////////////////////////////////////
    // Auto_Widgets
    ///////////////////////////////////////////////////////

    Valuator &
    create_scaling_valuator( const std::string & label = "scale" ) ;

    ///////////////////////////////////////////////////////
    // handlers
    ///////////////////////////////////////////////////////

    ///@{
    /// @brief Add/remove handlers.  (Expert use only.)
    void add_handler( kernel::Handler & ) ;
    void remove_handler( kernel::Handler & ) ;
    void add_handler( components::dimn::Motion_Handler & ) ;
    void remove_handler( components::dimn::Motion_Handler & ) ;
    ///@}

    Catch_Function catch_function() const ;
    void catch_function( Catch_Function ) ;

private:
    Simple_Viewer( const Simple_Viewer & ) ;
    Simple_Viewer & operator=( const Simple_Viewer & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::viewers::dim3

#endif

