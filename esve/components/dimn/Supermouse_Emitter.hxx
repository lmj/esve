
#ifndef esve_components_dimn_Supermouse_Emitter_hxx
#define esve_components_dimn_Supermouse_Emitter_hxx

#include <esve/components/dimn/Supermouse.hxx>
#include <esve/kernel/Emitter.hxx>
#include <esve/types/pure.hxx>
#include <memory>

namespace esve { namespace components { namespace dimn {

///
/// @class Supermouse_Emitter esve/components/dimn/Supermouse_Emitter.hxx
/// @brief Send handle_supermouse_*() messages.
///
/// @see Supermouse_Handler 
///

class Supermouse_Emitter
    : virtual public kernel::Emitter
{
public:
    ~Supermouse_Emitter() ;

protected:
    Supermouse_Emitter() ;

    /// @brief You have somehow figured out that the supermouse moved;
    /// send that information.
    virtual bool emit_supermouse_move( const types::pure & position ) ;

    /// @brief You have somehow figured out that a supermouse button was
    /// pushed; send that information.
    virtual bool emit_supermouse_push( Supermouse::Button,
                                       const types::pure & position ) ;

    /// @brief You have somehow figured out that a supermouse button was
    /// released; send that information.
    virtual bool emit_supermouse_release( Supermouse::Button,
                                          const types::pure & position ) ;

private:
    Supermouse_Emitter( const Supermouse_Emitter & ) ;
    Supermouse_Emitter & operator=( const Supermouse_Emitter & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::components::dimn

#endif
