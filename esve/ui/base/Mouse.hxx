#ifndef esve_ui_base_Mouse_hxx
#define esve_ui_base_Mouse_hxx

namespace esve { namespace ui { namespace base {

///
/// @class Mouse esve/ui/base/Mouse.hxx
/// @brief The current state of the mouse.
///

class Mouse
{
public:
    /// Mouse position (positive y points down).
    struct Position
    {
        /// .
        int x ;

        /// .
        int y ;
        
        /// .
        Position( int x_, int y_ )
            : x(x_),
              y(y_) { }
    } ;

    /// Mouse buttons.
    enum Button
    {
        /// .
        LEFT,
        /// .
        MIDDLE,
        /// .
        RIGHT // determines NUM_BUTTONS
    } ;

    static const unsigned int NUM_BUTTONS = RIGHT + 1 ;

    /// Where is the pointer?
    virtual const Position & position() const = 0 ;

    /// Is this button pushed?
    virtual bool pushed( Button a ) const = 0 ;

    virtual ~Mouse() = 0 ;

protected:
    Mouse() ;

private:
    Mouse( const Mouse & ) ;
    Mouse & operator=( const Mouse & ) ;
} ;

}}} // namespace esve::ui::base

#endif

