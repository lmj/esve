
#include <esve/viewers/dim4/Basic_Viewer.hxx>
#include <esve/engine/dim4/impl/Frame.hxx>
#include <esve/engine/dim4/Geom.hxx>
#include <esve/kernel/Simple_Kernel.hxx>
#include <esve/message/Compute_Sender.hxx>
#include <esve/message/Draw_Sender.hxx>

namespace esve { namespace viewers { namespace dim4 {

struct Basic_Viewer::Private
{
    engine::dim4::impl::Frame root_frame ;

    Private()
        : root_frame() { }
} ;

Basic_Viewer::
Basic_Viewer()
    : m(new Private())
{
    super::peek_kernel().add_update_receiver(m->root_frame) ;
}

Basic_Viewer::
~Basic_Viewer()
{
}

void
Basic_Viewer::
add_geom( engine::dim4::Geom & a )
{
    super::peek_compute_sender().add(a) ;
    super::peek_draw_sender().add(a) ;
    m->root_frame.add(a) ;
}

void
Basic_Viewer::
remove_geom( engine::dim4::Geom & a )
{
    super::peek_compute_sender().remove(a) ;
    super::peek_draw_sender().remove(a) ;
    m->root_frame.remove(a) ;
}

void
Basic_Viewer::
add_frame( engine::dim4::Frame & a )
{
    m->root_frame.add(a) ;
}

void
Basic_Viewer::
remove_frame( engine::dim4::Frame & a )
{
    m->root_frame.remove(a) ;
}

}}} // namespace esve::viewers::dim4
