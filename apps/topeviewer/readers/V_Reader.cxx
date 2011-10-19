
#include "V_Reader.hxx"
#include <sstream>

const std::string START_COMMENT = "#" ;

V_Reader::
V_Reader()
{
}

V_Reader::
~V_Reader()
{
}

const std::string &
V_Reader::
start_comment() const
{
    return START_COMMENT ;
}

bool
V_Reader::
test_read( std::istream & in, Tope_File::Points & points )
{
    unsigned int num_points = 0 ;
    unsigned int dim = 0 ;
    std::string line ;

    super::next_line(in, line) ;
    if( in.eof() || in.fail() )
    {
        return false ;
    }

    {
        std::istringstream line_stream(line) ;
        line_stream >> num_points >> dim ;
        if( line_stream.fail() ||
            num_points == 0 ||
            dim == 0 )
        {
            return false ;
        }
    }

    points.reserve(num_points) ;

    for( unsigned int i = 0 ; i != num_points ; ++i )
    {
        super::next_line(in, line) ;
        if( in.eof() || in.fail() )
        {
            return false ;
        }

        std::istringstream line_stream(line) ;

        // read vertex
        points.push_back(Tope_File::Point()) ;
        points.back().resize(dim) ;
        for( unsigned int j = 0 ; j != dim ; ++j )
        {
            line_stream >> points.back()[j] ;
            if( line_stream.fail() )
            {
                return false ;
            }
        }
    }

    return true ;
}

