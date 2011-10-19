
#include "Evolver_Reader.hxx"
#include <cctype>
#include <sstream>

const std::string START_COMMENT = "//" ;

namespace {

bool equal_nocase( const std::string & a,
                   const std::string & b )
{
    if( a.size() != b.size() )
    {
        return false ;
    }

    std::string::const_iterator ai = a.begin() ;
    std::string::const_iterator bi = b.begin() ;

    for( ; ai != a.end() ; ++ai, ++bi )
    {
        if( std::tolower(*ai) != std::tolower(*bi) )
        {
            return false ;
        }
    }

    return true ;
}

} // anon namespace

Evolver_Reader::
Evolver_Reader()
    : super()
{
}

Evolver_Reader::
~Evolver_Reader()
{
}

const std::string &
Evolver_Reader::
start_comment() const
{
    return START_COMMENT ;
}

bool
Evolver_Reader::
test_read( std::istream & in, Tope_File::Points & points )
{
    unsigned int dim = 3 ;
    std::string line ;
    std::string token ;

    for(;;)
    {
        super::next_line(in, line) ;

        if( in.eof() || in.fail() )
        {
            return false ;
        }

        std::istringstream line_stream(line) ;
        line_stream >> token ;

        if( equal_nocase(token, "space_dimension") )
        {
            line_stream >> dim ;
            if( line_stream.fail() || dim == 0 )
            {
                return false ;
            }
        }
        else if( equal_nocase(token, "vertices") )
        {
            break ;
        }
    }

    for(;;)
    {
        super::next_line(in, line) ;

        if( in.eof() || in.fail() )
        {
            return false ;
        }

        {
            std::istringstream line_stream(line) ;
            line_stream >> token ;

            if( equal_nocase(token, "edges") ||
                equal_nocase(token, "faces") ||
                equal_nocase(token, "bodies") )
            {
                // end of vertices input
                break ;
            }
        }

        {
            std::istringstream line_stream(line) ;

            // (vertex index not used)
            {
                unsigned int vertex_index ;
                line_stream >> vertex_index ;
                if( line_stream.fail() )
                {
                    return false ;
                }
            }

            // read vertex
            points.push_back(Tope_File::Point()) ;
            points.back().resize(dim) ;
            for( unsigned int i = 0 ; i != dim ; ++i )
            {
                line_stream >> points.back()[i] ;
                if( line_stream.fail() )
                {
                    return false ;
                }
            }
        }
    }

    return true ;
}
