
#ifndef esve_ui_base_Keyboard_hxx
#define esve_ui_base_Keyboard_hxx

namespace esve { namespace ui { namespace base {

///
/// @class Keyboard esve/ui/base/Keyboard.hxx
/// @brief The current state of the keyboard.
///

class Keyboard
{
public:
    /// @enum Key
    /// @brief Keyboard keys.
    enum Key
    {
        // ...
        // ascii 0-127
        // ...

        /// (placeholder)
        NUM_ASCII_KEYS = 128,

        /// .
        ENTER = NUM_ASCII_KEYS,
        /// .
        ESCAPE,
        /// .
        META_LEFT,
        /// .
        META_RIGHT,
        /// .
        ALT_LEFT,
        /// .
        ALT_RIGHT,
        /// .
        CTRL_LEFT,
        /// .
        CTRL_RIGHT,
        /// .
        SHIFT_LEFT,
        /// .
        SHIFT_RIGHT,
        /// .
        BACKSPACE,
        /// .
        TAB,
        /// .
        RIGHT_ARROW,
        /// .
        LEFT_ARROW,
        /// .
        UP_ARROW,
        /// .
        DOWN_ARROW  // determines NUM_KEYS
    } ;

    static const unsigned int NUM_KEYS = DOWN_ARROW + 1 ;

    /// Is this key pushed?
    virtual bool pushed( Key a ) const = 0 ;

    virtual ~Keyboard() = 0 ;

protected:
    Keyboard() ;

private:
    Keyboard( const Keyboard & ) ;
    Keyboard & operator=( const Keyboard & ) ;
} ;

}}} // namespace esve::ui::base

#endif

