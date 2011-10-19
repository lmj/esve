
#include <esve/util/Command_Line.hxx>

namespace esve { namespace util {

Command_Line::
Command_Line( int argc,
              char** argv,
              const std::string & optstring )
    : m_arguments(),
      m_options(),
      m_error()
{
    // options signature
    typedef std::map<char, bool> Sig ;
    Sig sig ;

    // read options signature

    for( std::string::const_iterator p = optstring.begin() ;
         p != optstring.end() ;
         ++p )
    {
        if( *p != ':' )
        {
            if( p + 1 != optstring.end() && *(p + 1) == ':' )
            {
                sig[*p] = true ;
            }
            else
            {
                sig[*p] = false ;
            }
        }
    }

    for( int i = 1 ; i != argc ; ++i )
    {
        if( argv[i][0] == '-' && argv[i][1] != 0 && argv[i][1] == '-' )
        {
            // everything after '--' treated as normal arguments

            for( int j = i + i ; j != argc ; ++j )
            {
                m_arguments.push_back(argv[j]) ;
            }

            break ;
        }
        else if( argv[i][0] == '-' && argv[i][1] != 0 )
        {
            // option string

            for( const char* p = &argv[i][1] ; *p != '\0' ; ++p )
            {
                Sig::iterator found = sig.find(*p) ;

                if( found == sig.end() )
                {
                    // invalid option
                    m_bail(argv[0],
                           std::string("invalid option")
                           +
                           " -- "
                           +
                           p) ;
                    return ;
                }
                else if( (*found).second == true )
                {
                    // option requires an argument

                    if( *(p + 1) == '\0' )
                    {
                        // last char in option string

                        if( i == argc - 1 )
                        {
                            // no more arguments
                            m_bail(argv[0],
                                   std::string("option requires an argument")
                                   +
                                   " -- "
                                   +
                                   *p) ;
                            return ;
                        }
                        else if( argv[i + 1][0] == '-' )
                        {
                            // next word is an option string
                            m_bail(argv[0],
                                   std::string("option requires an argument")
                                   +
                                   " -- "
                                   +
                                   *p) ;
                            return ;
                        }
                        else
                        {
                            // next word is the option argument
                            ++i ;
                            m_options.insert(m_Option_Pair(*p, argv[i])) ;
                        }
                    }
                    else
                    {
                        // option argument is the remaining string
                        m_options.insert(m_Option_Pair(*p, p + 1)) ;
                    }

                    break ;
                }
                else
                {
                    // option does not require an argument
                    m_options.insert(m_Option_Pair(*p, "")) ;
                }
            }
        }
        else
        {
            // normal command-line argument
            m_arguments.push_back(argv[i]) ;
        }
    }
}

Command_Line::
~Command_Line()
{
}

void
Command_Line::
m_bail( const std::string & argv0,
        const std::string & error )
{
    m_error = argv0 + ": " + error ;
    m_arguments.clear() ;
    m_options.clear() ;
}

std::string
Command_Line::
option_argument( char opt ) const
{
    m_Options::const_iterator found = m_options.find(opt) ;

    if( found == m_options.end() )
    {
        return "" ;
    }

    return (*found).second ;
}

bool
Command_Line::
option( char opt ) const
{
    return m_options.find(opt) != m_options.end() ;
}

std::string
Command_Line::
error() const
{
    return m_error ;
}

void
Command_Line::
set_option( char opt )
{
    m_options.insert(m_Option_Pair(opt, "")) ;
}

void
Command_Line::
set_option( char opt, const std::string & s )
{
    m_options.insert(m_Option_Pair(opt, s)) ;
}

void
Command_Line::
clear_option( char opt )
{
    m_Options::iterator found = m_options.find(opt) ;
    if( found != m_options.end() )
    {
        m_options.erase(found) ;
    }
}

}} // namespace esve::util
