
#ifndef esve_ui_base_Display_hxx
#define esve_ui_base_Display_hxx

#include <esve/ui/base/Display_Details_Stowed.hxx>
#include <esve/ui/base/Display.hxx>
#include <esve/ui/base/Keyboard_Emitter.hxx>
#include <esve/ui/base/Mouse_Emitter.hxx>
#include <esve/kernel/Catcher.hxx>
#include <esve/kernel/Emitter.hxx>
#include <esve/message/Compute_Sender_Stowed.hxx>
#include <esve/message/Draw_Sender_Stowed.hxx>
#include <esve/message/impl/Update_Receiver.hxx>
#include <string>
#include <memory>
#include <exception>

namespace esve { namespace platform { class Representation ; } }

namespace esve { namespace ui { namespace base {

///
/// @class Display esve/ui/base/Display.hxx
/// @brief An area for drawing.
///
/// A Display holds message::Draw_Receiver objects, passing draw()
/// messages to them when the system deems appropriate.  The user
/// should not initiate a draw() message.
///
/// Display is an Emitter --- a source of handle_*() messages which
/// are sent to its child Handlers.
///
/// Display is also a Compute_Sender.  The compute() message is sent
/// to its compute()-children immediately before the draw() message is
/// sent.  (See message::Compute_Receiver.)
///
/// Display is also a leaf in the update() tree; the update() message
/// marks the display as needing to be redrawn.
///

class Display
    : virtual public Display_Details_Stowed,
      virtual public kernel::Catcher,
      virtual public message::Compute_Sender_Stowed,
      virtual public message::Draw_Sender_Stowed,
      virtual public message::impl::Update_Receiver,
      public Mouse_Emitter,
      public Keyboard_Emitter
{
public:
    ///
    /// @struct Rectangle esve/ui/base/Display.hxx
    /// @brief Rectangular dimensions.
    ///
    struct Rectangle
    {
        /// .
        unsigned int width ;
        
        /// .
        unsigned int height ;
        
        /// .
        Rectangle( unsigned int width_,
                   unsigned int height_ )
            : width(width_),
              height(height_) { }
    } ;
    
    /// Constructor.
    Display( const std::string & label, const Rectangle & ) ;

    ///@{
    const Display_Details & peek_display_details() const ;
    Display_Details & peek_display_details() ;
    ///@}

    message::Compute_Sender & peek_compute_sender() ;
    message::Draw_Sender & peek_draw_sender() ;

    Catch_Function catch_function() const ;
    void catch_function( Catch_Function ) ;

    virtual void reinitialize() ;

    ~Display() ;

protected:
    void update() ;
    void update( double dt ) ;

private:
    Display( const Display & ) ;
    Display & operator=( const Display & ) ;

    // Back door to grab the underlying representation.
    friend class platform::Representation ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::ui::base

#endif

