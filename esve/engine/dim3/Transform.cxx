
#include <esve/engine/dim3/Transform.hxx>

namespace esve { namespace engine { namespace dim3 {

using types::real ;
using types::pure ;

const Transform
Transform::
IDENTITY ;

void
Transform::
rotate( real angle,
        const pure & axis,
        const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.rotate(angle, axis, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.rotate(angle, axis, m) ;
    }
    else
    {
        m.rotate(angle, axis, m_Transform(basis.rotation(),
                                          basis.translation(),
                                          basis.scaling())) ;
    }
}

void
Transform::
translate( const pure & dt,
           const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.translate(dt, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.translate(dt, m) ;
    }
    else
    {
        m.translate(dt,
                    m_Transform(basis.rotation(),
                                basis.translation(),
                                basis.scaling())) ;
    }
}

void
Transform::
scalate( real ds,
         const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.scalate(ds, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.scalate(ds, m) ;
    }
    else
    {
        m.scalate(ds,
                  m_Transform(basis.rotation(),
                              basis.translation(),
                              basis.scaling())) ;
    }
}

}}} // namespace esve::engine::dim3
