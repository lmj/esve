
#include <esve/engine/dim4/Geom.hxx>

namespace esve { namespace engine { namespace dim4 {

Geom::
Geom()
    : message::Draw_Receiver(),
      message::Compute_Receiver(),
      Frame()
{
}

Geom::
~Geom()
{
}

}}} // namespace esve::engine::dim4
