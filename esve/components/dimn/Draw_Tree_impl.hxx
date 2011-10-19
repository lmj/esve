
#ifndef esve_components_dimn_Draw_Tree_impl_hxx
#define esve_components_dimn_Draw_Tree_impl_hxx

#include <esve/components/dimn/Check_Error.hxx>
#include <esve/message/impl/Draw_Node.hxx>

namespace esve { namespace components { namespace dimn {

///
/// @class Draw_Tree_impl esve/components/dimn/Draw_Tree_impl.hxx
/// @brief A starter draw tree.
///
/// This is an example configuration for implementers building an
/// application from scatch.
///
/// @verbatim
///
///                              root_draw_node
///                              /  /  / \  \                               .
/// draw_intialize_node <-------+  /  /   \  \                              .
///                               /  /     \  \                             .
///                 +------------+  /       \  +------------+               .
///                /               /  draw() \               \              .
///               /               /           \               \             .
///              /               /             \               \            .
///             /               /               \               \           .
///            /               /                 \               \          .
///           /               /                   \               \         .
///          /               /                     \               \        .
///         |               |                       |               |
///        \|/             \|/                     \|/             \|/
///         *               *                       *               *
///   check_error   clear_buffers_node       unlit_draw_node   lit_draw_node
///
/// @endverbatim
///

struct Draw_Tree_impl
{
public:
    /// Root draw node.
    message::impl::Draw_Node root_draw_node ;

    /// OpenGL initialization.
    message::impl::Draw_Node draw_initialize_node ;

    /// Checks for OpenGL errors.
    components::dimn::Check_Error check_error ;

    /// Placeholder node for clearing buffers.
    message::impl::Draw_Node clear_buffers_node ;

    /// Placeholder node for unlit drawing, such as a background.
    message::impl::Draw_Node unlit_draw_node ;

    /// Placeholder node for lit (lighted) drawing.  Add lights here.
    message::impl::Draw_Node lit_draw_node ;

    Draw_Tree_impl() ;
    ~Draw_Tree_impl() ;

private:
    Draw_Tree_impl( const Draw_Tree_impl & ) ;
    Draw_Tree_impl & operator=( const Draw_Tree_impl & ) ;
} ;

}}} // namespace esve::components::dimn

#endif

