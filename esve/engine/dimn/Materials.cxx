
#include <esve/engine/dimn/Materials.hxx>

namespace esve { namespace engine { namespace dimn {

using types::rgba ;

Materials::
Materials()
    : m_ambient(1, 1, 1, 1),
      m_diffuse(1, 1, 1, 1),
      m_specular(1, 1, 1, 1)
{
}

Materials::
~Materials()
{
}

const rgba &
Materials::
ambient() const
{
    return m_ambient ;
}

const rgba &
Materials::
diffuse() const
{
    return m_diffuse ;
}

const rgba &
Materials::
specular() const
{
    return m_specular ;
}

void
Materials::
ambient( const rgba & a )
{
    m_ambient = a ;
}

void
Materials::
diffuse( const rgba & a )
{
    m_diffuse = a ;
}

void
Materials::
specular( const rgba & a )
{
    m_specular = a ;
}

}}} // namespace esve::engine::dimn
