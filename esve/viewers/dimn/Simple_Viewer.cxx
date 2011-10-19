
#include <esve/viewers/dimn/Simple_Viewer.hxx>

namespace esve { namespace viewers { namespace dimn {

Simple_Viewer::
Simple_Viewer()
{
}

Simple_Viewer::
~Simple_Viewer()
{
}

bool
Simple_Viewer::
handle_key_push( Key, const Keyboard & )
{
    return false ;
}

bool
Simple_Viewer::
handle_key_release( Key, const Keyboard & )
{
    return false ;
}

bool
Simple_Viewer::
handle_mouse_move( const Mouse & )
{
    return false ;
}

bool
Simple_Viewer::
handle_mouse_push( Button, const Mouse & )
{
    return false ;
}

bool
Simple_Viewer::
handle_mouse_release( Button, const Mouse & )
{
    return false ;
}

bool
Simple_Viewer::
handle_valuator( const Valuator & )
{
    return false ;
}

bool
Simple_Viewer::
handle_toggle( const Toggle & )
{
    return false ;
}

bool
Simple_Viewer::
handle_file_selector( const File_Selector & )
{
    return false ;
}

bool
Simple_Viewer::
handle_valuator( const Complex_Valuator & )
{
    return false ;
}

bool
Simple_Viewer::
handle_valuator( const Pure_Valuator & )
{
    return false ;
}

bool
Simple_Viewer::
handle_valuator( const Quat_Valuator & )
{
    return false ;
}

}}} // namespace esve::viewers::dimn

