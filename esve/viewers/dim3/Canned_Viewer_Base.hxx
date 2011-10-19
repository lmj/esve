
#ifndef esve_viewers_dim3_Canned_Viewer_Base_hxx
#define esve_viewers_dim3_Canned_Viewer_Base_hxx

#include <esve/viewers/dim3/Starry_Viewer.hxx>
#include <esve/components/dimn/Command_Line.hxx>
#include <esve/types/real.hxx>
#include <memory>

namespace esve { namespace ui { namespace extra { class Modal_Tie ; } } }

namespace esve { namespace viewers { namespace dim3 {

///
/// @class Canned_Viewer_Base esve/viewers/dim3/Canned_Viewer_Base.hxx
/// @brief Undocumented base class.
///

class Canned_Viewer_Base
    : public Starry_Viewer
{
private:
    typedef Starry_Viewer super ;

    Canned_Viewer_Base( const Canned_Viewer_Base & ) ;
    Canned_Viewer_Base & operator=( const Canned_Viewer_Base & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    ~Canned_Viewer_Base() ;

protected:
    typedef
    components::dimn::Command_Line::Arguments_iterator
    Command_Line_Arguments_iterator ;

    /// Constructor.  Give arguments from main().
    Canned_Viewer_Base( int argc, char** argv ) ;

    /// Take advantage of a modal tie.
    void modal_tie( ui::extra::Modal_Tie & ) ;

    /// Motion sensitivity read at command line.
    types::real sensitivity() const ;

    ///@{
    /// @brief Non-option command-line arguments.
    Command_Line_Arguments_iterator arguments_begin() const ;
    Command_Line_Arguments_iterator arguments_end() const ;
    ///@}
} ;

}}} // namespace esve::viewers::dim3

#endif
