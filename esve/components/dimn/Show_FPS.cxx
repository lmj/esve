
#include <esve/components/dimn/Show_FPS.hxx>
#include <iostream>

namespace esve { namespace components { namespace dimn {

Show_FPS::
Show_FPS()
    : Update_Receiver(),
      m_sampling_interval(1.0),
      m_elapsed(0),
      m_visit(0),
      m_output(&std::cerr)
{
}

Show_FPS::
~Show_FPS()
{
}

void
Show_FPS::
sampling_interval( double val )
{
    m_sampling_interval = val ;
    m_elapsed = 0 ;
    m_visit = 0 ;
}

void
Show_FPS::
update( double dt )
{
    m_visit += 1 ;
    m_elapsed += dt ;

    if( double(m_elapsed) > m_sampling_interval )
    {
        *m_output << "FPS: "
                  << double(m_visit)/double(m_elapsed)
                  << std::endl ;
        m_elapsed = 0 ;
        m_visit = 0 ;
    }
}

void
Show_FPS::
update()
{
}

const std::ostream &
Show_FPS::
output() const
{
    return *m_output ;
}

void
Show_FPS::
output( std::ostream & a )
{
    m_output = &a ;
}

}}} // namespace esve::components::dimn
