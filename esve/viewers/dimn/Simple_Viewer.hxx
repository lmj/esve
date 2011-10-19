
#ifndef esve_viewers_dimn_Simple_Viewer_hxx
#define esve_viewers_dimn_Simple_Viewer_hxx

#include <esve/viewers/dimn/Minimal_Viewer.hxx>
#include <esve/components/dimn/Valuator_Handler.hxx>
#include <esve/components/dimn/Simple_UI.hxx>
#include <esve/ui/extra/Toggle_Handler.hxx>
#include <esve/ui/extra/File_Selector_Handler.hxx>
#include <esve/ui/base/Keyboard_Handler.hxx>
#include <esve/ui/base/Mouse_Handler.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>
#include <esve/types/Constants.hxx>
#include <string>

namespace esve { namespace viewers { namespace dimn {

///
/// @class Simple_Viewer esve/viewers/dimn/Simple_Viewer.hxx
/// @brief Stuff for Simple_Viewer.
///

class Simple_Viewer
    : virtual protected Minimal_Viewer,
      virtual protected components::dimn::Simple_UI,
      virtual protected types::Constants,
      protected components::dimn::Valuator_Handler<types::real>,
      protected components::dimn::Valuator_Handler<types::complex>,
      protected components::dimn::Valuator_Handler<types::pure>,
      protected components::dimn::Valuator_Handler<types::quat>,
      protected ui::extra::Toggle_Handler,
      protected ui::extra::File_Selector_Handler,
      protected ui::base::Keyboard_Handler,
      protected ui::base::Mouse_Handler
{
public:
    /// @typedef real
    /// @brief Real numbers.
    typedef types::real real ;

    /// @typedef complex
    /// @brief Complex numbers.
    typedef types::complex complex ;

    /// @typedef pure
    /// @brief Pure quaternions.
    typedef types::pure pure ;

    /// @typedef quat
    /// @brief Quaternions.
    typedef types::quat quat ;

    /// @typedef Valuator
    /// @brief Real valuator.
    typedef components::dimn::Valuator<real> Valuator ;

    /// @typedef Complex_Valuator
    /// @brief Complex valuator.
    typedef components::dimn::Valuator<complex> Complex_Valuator ;

    /// @typedef Pure_Valuator
    /// @brief Pure quaternion valuator.
    typedef components::dimn::Valuator<pure> Pure_Valuator ;

    /// @typedef Quat_Valuator
    /// @brief Quaternion valuator.
    typedef components::dimn::Valuator<quat> Quat_Valuator ;

    /// Some banal help text.
    virtual const std::string & help_text() const = 0 ;

    /// OpenGL initialization; called by the display.  Override if you wish.
    virtual void initialize() = 0 ;

    // defaults of 'return false'
    bool handle_key_push( Key, const Keyboard & ) ;
    bool handle_key_release( Key, const Keyboard & ) ;
    bool handle_mouse_move( const Mouse & ) ;
    bool handle_mouse_push( Button, const Mouse & ) ;
    bool handle_mouse_release( Button, const Mouse & ) ;
    bool handle_toggle( const Toggle & ) ;
    bool handle_file_selector( const File_Selector & ) ;
    bool handle_valuator( const Valuator & ) ;
    bool handle_valuator( const Complex_Valuator & ) ;
    bool handle_valuator( const Pure_Valuator & ) ;
    bool handle_valuator( const Quat_Valuator & ) ;

    virtual ~Simple_Viewer() = 0 ;

protected:
    Simple_Viewer() ;

private:
    Simple_Viewer( const Simple_Viewer & ) ;
    Simple_Viewer & operator=( const Simple_Viewer & ) ;
} ;

}}} // namespace esve::viewers::dimn

#endif
