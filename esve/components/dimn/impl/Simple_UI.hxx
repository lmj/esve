
#ifndef esve_components_dimn_impl_Simple_UI_hxx
#define esve_components_dimn_impl_Simple_UI_hxx

#include <esve/components/dimn/Valuator_Emitter.hxx>
#include <esve/components/dimn/Simple_UI.hxx>
#include <esve/ui/extra/Modal_Tie.hxx>
#include <esve/ui/extra/File_Selector_Emitter.hxx>
#include <esve/ui/extra/Toggle_Emitter.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/pure.hxx>
#include <esve/types/complex.hxx>
#include <memory>

namespace esve { namespace ui { namespace base {

class Display ;

}}} // namespace esve::ui::base

namespace esve { namespace components { namespace dimn { namespace impl {

///
/// @class Simple_UI esve/components/dimn/impl/Simple_UI.hxx
/// @brief Implements components::dimn::Simple_UI.
///

class Simple_UI
    : virtual public components::dimn::Simple_UI,
      virtual public ui::extra::Modal_Tie,
      public ui::extra::Toggle_Emitter,
      public ui::extra::File_Selector_Emitter,
      public Valuator_Emitter<types::real>,
      public Valuator_Emitter<types::complex>,
      public Valuator_Emitter<types::pure>,
      public Valuator_Emitter<types::quat>
{
public:
    Simple_UI( ui::base::Display & ) ;

    void toggle_modal_visible() ;
    void toggle_display_fullscreen() ;

    void create_label( const std::string & label ) ;

    ui::extra::File_Selector &
    create_file_selector( const std::string & initial_value = "",
                          const std::string & label = "file",
                          const std::string & selector_label = "select a file",
                          const std::string & initial_directory = ".",
                          const std::string & filter = "*" ) ;

    void create_help( const std::string & text,
                      const std::string & label = "help" ) ;

    ui::extra::Toggle &
    create_toggle( bool initial_value,
                   const std::string & label ) ;

    Valuator<types::real> &
    create_valuator( types::real initial_value,
                     const std::string & label = "" ) ;

    Valuator<types::complex> &
    create_valuator( const types::complex & initial_value,
                     const std::string & label = "" ) ;

    Valuator<types::pure> &
    create_valuator( const types::pure & initial_value,
                     const std::string & label = "" ) ;

    Valuator<types::quat> &
    create_valuator( const types::quat & initial_value,
                     const std::string & label = "" ) ;

    Catch_Function catch_function() const ;
    void catch_function( Catch_Function ) ;

    ~Simple_UI() ;

protected:
    using Valuator_Emitter<types::real>::emit_valuator ;
    using Valuator_Emitter<types::complex>::emit_valuator ;
    using Valuator_Emitter<types::pure>::emit_valuator ;
    using Valuator_Emitter<types::quat>::emit_valuator ;

private:
    Simple_UI( const Simple_UI & ) ;
    Simple_UI & operator=( const Simple_UI & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}}} // namespace esve::components::dimn::impl

#endif

