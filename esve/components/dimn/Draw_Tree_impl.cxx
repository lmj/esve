
#include <esve/components/dimn/Draw_Tree_impl.hxx>

namespace esve { namespace components { namespace dimn {

Draw_Tree_impl::
Draw_Tree_impl()
    : root_draw_node(),
      draw_initialize_node(),
      check_error(),
      clear_buffers_node(),
      unlit_draw_node(),
      lit_draw_node()
{
    root_draw_node.add(check_error) ;
    root_draw_node.add(draw_initialize_node) ;
    root_draw_node.add(clear_buffers_node) ;
    root_draw_node.add(unlit_draw_node) ;
    root_draw_node.add(lit_draw_node) ;
}

Draw_Tree_impl::
~Draw_Tree_impl()
{
}

}}} // namespace esve::components::dimn
