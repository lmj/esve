
#include <esve/ui/base/Display_Details.hxx>

namespace esve { namespace ui { namespace base {

Display_Details::
Display_Details()
{
}

Display_Details::
~Display_Details()
{
}

void
Display_Details::
call_reshape( Display_Details & display,
              const Display::Rectangle & rectangle )
{
    display.reshape(rectangle) ;
}

}}} // namespace esve::ui::base
