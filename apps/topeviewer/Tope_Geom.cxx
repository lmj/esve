
#include "Tope_Geom.hxx"
#include "readers/Universal_Reader.hxx"
#include <cassert>

using esve::types::quat ;

namespace {

//////////////////////////////////////////////////
//
// Vector_To_Quat_Input_Iterator
//
//////////////////////////////////////////////////

template< typename Input_Iterator >
class Vector_To_Quat_Input_Iterator
{
private:
    Input_Iterator m_i ;
    unsigned int m_dim ;

public:
    Vector_To_Quat_Input_Iterator( Input_Iterator i,
                                   unsigned int dim )
        : m_i(i),
          m_dim(dim) { }

    quat operator*() const ;

    Vector_To_Quat_Input_Iterator & operator++()
    {
        ++m_i ;
        return *this ;
    }

    bool operator!=( Vector_To_Quat_Input_Iterator a ) const
    {
        return m_i != a.m_i ;
    }
} ;

template< typename Input_Iterator >
quat
Vector_To_Quat_Input_Iterator<Input_Iterator>::
operator*() const
{
    switch( m_dim )
    {
    case 1:
        return quat(0,
                    (*m_i)[0],
                    0,
                    0) ;

    case 2:
        return quat(0,
                    (*m_i)[0],
                    (*m_i)[1],
                    0) ;

    case 3:
        return quat(0,
                    (*m_i)[0],
                    (*m_i)[1],
                    (*m_i)[2]) ;

    case 4:
        return quat((*m_i)[0],
                    (*m_i)[1],
                    (*m_i)[2],
                    (*m_i)[3]) ;
        
    default:
        ;
    }

    assert(!"Too many dimensions for quat") ;
    return quat() ;
}

} // anon namespace

///////////////////////////////////////////////////////////

struct Tope_Geom::Private
{
    Universal_Reader reader ;
    std::auto_ptr<Tope_File> file ;
    unsigned int current_config ;

    Private() ;
    ~Private() ;
} ;

Tope_Geom::
Private::
Private()
    : reader(),
      file(0),
      current_config(0)
{
}

Tope_Geom::
Private::
~Private()
{
}

Tope_Geom::
Tope_Geom( const std::string & filename )
    : m(new Private())
{
    Tope_Geom::read(filename) ;
}

Tope_Geom::
~Tope_Geom()
{
}

void
Tope_Geom::
read( const std::string & filename )
{
    std::auto_ptr<Tope_File> next_file = m->reader.read(filename) ;

    if( next_file->dimension() == 0
        ||
        next_file->dimension() > 4 )
    {
        throw Tope_File::Read_Error(filename) ;
    }

    m->file = next_file ;

    m->current_config = 0 ;

    Vector_To_Quat_Input_Iterator<Tope_File::Points::const_iterator>
        begin(m->file->points().begin(), m->file->dimension()) ;

    Vector_To_Quat_Input_Iterator<Tope_File::Points::const_iterator>
        end(m->file->points().end(), m->file->dimension()) ;
    
    super::points(begin, end) ;
}

bool
Tope_Geom::
has_configs() const
{
    return m->file->configs().size() != 0 ;
}

const Tope_File::Config &
Tope_Geom::
current_config() const
{
    assert(m->file->configs().size() != 0
           &&
           "current_config() called but no configs present") ;

    assert(m->current_config < m->file->configs().size()) ;

    return m->file->configs().at(m->current_config) ;
}

void
Tope_Geom::
next_config()
{
    if( m->file->configs().size() != 0 )
    {
        m->current_config =
            (m->current_config + 1) % m->file->configs().size() ;
    }
}

void
Tope_Geom::
add_config( const Tope_File::Config & a )
{
    m->file->add_config(a) ;
    m->current_config = m->file->configs().size() - 1 ;
}

const std::string &
Tope_Geom::
filename() const
{
    return m->file->filename() ;
}

