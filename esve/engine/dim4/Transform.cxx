
#include <esve/engine/dim4/Transform.hxx>

namespace esve { namespace engine { namespace dim4 {

using types::real ;
using types::quat ;
using types::pure ;

const Transform
Transform::
IDENTITY ;

void
Transform::
rotate( real alpha,
        real beta,
        const quat & r,
        const quat & s,
        const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.rotate(alpha, beta, r, s, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.rotate(alpha, beta, r, s, m) ;
    }
    else
    {
        m.rotate(alpha,
                 beta,
                 r,
                 s,
                 m_Transform(basis.a(),
                             basis.b(),
                             basis.c(),
                             basis.d())) ;
    }
}

void
Transform::
rotate( real alpha,
        real beta,
        const pure & u,
        const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.rotate(alpha, beta, u, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.rotate(alpha, beta, u, m) ;
    }
    else
    {
        m.rotate(alpha,
                 beta,
                 u,
                 m_Transform(basis.a(),
                             basis.b(),
                             basis.c(),
                             basis.d())) ;
    }
}

void
Transform::
translate( const quat & r,
           const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.translate(r, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.translate(r, m) ;
    }
    else
    {
        m.translate(r,
                    m_Transform(basis.a(),
                                basis.b(),
                                basis.c(),
                                basis.d())) ;
    }
}

void
Transform::
invertate( const quat & r,
           const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.invertate(r, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.invertate(r, m) ;
    }
    else
    {
        m.invertate(r,
                    m_Transform(basis.a(),
                                basis.b(),
                                basis.c(),
                                basis.d())) ;
    }
}

void
Transform::
scalate( real gamma,
         const Transform & basis )
{
    if( &basis == &IDENTITY )
    {
        m.scalate(gamma, m_Transform::IDENTITY) ;
    }
    else if( &basis == this )
    {
        m.scalate(gamma, m) ;
    }
    else
    {
        m.scalate(gamma,
                  m_Transform(basis.a(),
                              basis.b(),
                              basis.c(),
                              basis.d())) ;
    }
}

}}} // namespace esve::engine::dim4
