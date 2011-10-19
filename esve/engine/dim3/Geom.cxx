
#include <esve/engine/dim3/Geom.hxx>

namespace esve { namespace engine { namespace dim3 {

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

}}} // namespace esve::engine::dim3
