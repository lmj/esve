
#include "Line_Oriented_Reader.hxx"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

const std::string TOPEVIEWER_FLAG = "topeviewer:" ;

namespace {

void strip_leading_whitespace( std::string & line )
{
    std::istringstream stream(line) ;
    stream >> std::ws ;
    std::getline(stream, line) ;
}

void strip_after( std::string & line, const std::string & start_comment )
{
    const std::string::size_type comment_pos =
        line.find(start_comment) ;

    if( comment_pos != std::string::npos )
    {
        line = line.substr(0, comment_pos) ;
    }
}

} // anon namespace

struct Line_Oriented_Reader::Private
{
    struct Parser
        : virtual public Tope_File
    {
        Line_Oriented_Reader::Private & m ;
        Points m_points ;
        Configs m_configs ;
        std::string m_filename ;
        std::string m_contents ;
        
        Parser( Line_Oriented_Reader::Private & m_ )
            : m(m_),
              m_points(),
              m_configs(),
              m_filename(),
              m_contents() { }

        // Tope_File
        
        unsigned int dimension() const
        {
            return m_points.size() == 0 ? 0 : m_points[0].size() ;
        }
        
        const Tope_File::Points & points() const
        {
            return m_points ;
        }
        
        const Tope_File::Configs & configs() const
        {
            return m_configs ;
        }
        
        const std::string & filename() const
        {
            return m_filename ;
        }
        
        void add_config( const Config & a )
        {
            m_configs.push_back(a) ;
            write() ;
        }
        
        // own stuff
        
        bool test_read( const std::string & filename ) ;
        void write() const ;
        void next_data_line( std::istream & in, std::string & line ) ;
    } ;

    struct Sentry
    {
        Line_Oriented_Reader::Private & m ;

        Sentry( Parser & parser,
                Line_Oriented_Reader::Private & m_ )
            : m(m_)
        {
            m.parser = &parser ;
        }
        
        ~Sentry()
        {
            m.parser = 0 ;
        }
    } ;

    Line_Oriented_Reader & outside ;
    Parser* parser ;
    
    Private( Line_Oriented_Reader & outside_ )
        : outside(outside_),
          parser(0) { }

private:
    Private( const Private & ) ;
    Private & operator=( const Private & ) ;
} ;

bool
Line_Oriented_Reader::Private::Parser::
test_read( const std::string & filename )
{
    std::ifstream in(filename.c_str()) ;

    if( in.fail() || in.eof() )
    {
        return false ;
    }

    const bool status = m.outside.test_read(in, m_points) ;

    if( status )
    {
        m_filename = filename ;

        std::string line ;

        // read configs in the unused portion
        while( !in.eof() )
        {
            m.outside.next_line(in, line) ;
        }
    }

    return status ;
}

void
Line_Oriented_Reader::Private::Parser::
write() const
{
    std::ofstream out(m_filename.c_str()) ;

    if( out.fail() )
    {
        throw Tope_File::Write_Error(m_filename) ;
    }

    out << m_contents ;

    for( Configs::const_iterator i = m_configs.begin() ;
         i != m_configs.end() ;
         ++i )
    {
        std::string config = *i ;
        strip_leading_whitespace(config) ;

        out << m.outside.start_comment()
            << " "
            << TOPEVIEWER_FLAG
            << " "
            << config
            << std::endl ;
    }
}

void
Line_Oriented_Reader::Private::Parser::
next_data_line( std::istream & in, std::string & line )
{
    // find the next line which contains some data

    while( !in.eof() )
    {
        std::getline(in, line) ;

        bool is_config_line = false ;

        // config lines must be begin with a comment
        if( line.size() >= m.outside.start_comment().size()
            &&
            line.substr(0, m.outside.start_comment().size())
            ==
            m.outside.start_comment() )
        {
            std::string comment =
                line.substr(m.outside.start_comment().size()) ;
            strip_leading_whitespace(comment) ;

            if( comment.size() >= TOPEVIEWER_FLAG.size() &&
                comment.substr(0, TOPEVIEWER_FLAG.size()) == TOPEVIEWER_FLAG )
            {
                std::string config = comment.substr(TOPEVIEWER_FLAG.size()) ;
                strip_leading_whitespace(config) ;
                m_configs.push_back(config) ;
                is_config_line = true ;
            }
        }

        if( !is_config_line )
        {
            m_contents += line ;
            m_contents += "\n" ;

            strip_after(line, m.outside.start_comment()) ;

            if( line != "" )
            {
                // found a line with some data
                break ;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////

Line_Oriented_Reader::
Line_Oriented_Reader()
    : m(new Private(*this))
{
}

Line_Oriented_Reader::
~Line_Oriented_Reader()
{
}

std::auto_ptr<Tope_File>
Line_Oriented_Reader::
read( const std::string & filename )
{
    assert(m->parser == 0 && "attempt to call read() while already parsing") ;

    std::auto_ptr<Private::Parser> topefile(new Private::Parser(*m)) ;

    Private::Sentry sentry(*topefile, *m) ;

    if( topefile->test_read(filename) == false )
    {
        throw Tope_File::Read_Error(filename) ;
    }

    // (convert to base)
    return std::auto_ptr<Tope_File>(topefile) ;
}

void
Line_Oriented_Reader::
next_line( std::istream & in,
           std::string & line )
{
    assert(m->parser && "attempt to call next_line() outside of test_read()") ;
    m->parser->next_data_line(in, line) ;
}

