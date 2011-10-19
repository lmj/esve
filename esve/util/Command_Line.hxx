//
// Command-line utility for unordered single-char options.
//
// This class does not throw exceptions.
//

#ifndef esve_util_Command_Line_hxx
#define esve_util_Command_Line_hxx

#include <string>
#include <map>
#include <vector>

namespace esve { namespace util {

class Command_Line
{
private:
    typedef std::vector<std::string> m_Arguments ;
    typedef std::map<char, const std::string> m_Options ;
    typedef std::pair<char, const std::string> m_Option_Pair ;

    void m_bail( const std::string & argv0, const std::string & error ) ;

    m_Arguments m_arguments ;
    m_Options m_options ;
    std::string m_error ;

public:
    typedef m_Arguments::const_iterator Arguments_iterator ;
    typedef m_Options::const_iterator Options_iterator ;

    // optstring is in standard getopt() format, e.g., "f:pqr:z"
    Command_Line( int argc, char** argv, const std::string & optstring ) ;

    // compiler writes memberwise copy and assign

    // true if option was read
    bool option( char ) const ;

    // the argument corresponding to this option
    std::string option_argument( char opt ) const ;

    // "" if no error
    std::string error() const ;

    //
    // options which were read.
    //
    // Options_iterator dereferences to
    //   pair<char, const std::string>(option_character, option_argument).
    //
    Options_iterator options_begin() const
    {
        return m_options.begin() ;
    }

    Options_iterator options_end() const
    {
        return m_options.end() ;
    }

    // normal arguments.
    // iterator dereferences to const std::string
    Arguments_iterator arguments_begin() const
    {
        return m_arguments.begin() ;
    }

    Arguments_iterator arguments_end() const
    {
        return m_arguments.end() ;
    }

    // manually set an option
    void set_option( char opt ) ;

    // manually set the argument corresponding to this option
    void set_option( char opt, const std::string & optarg ) ;

    // remove an option which was read or set
    void clear_option( char opt ) ;

    virtual ~Command_Line() ;
} ;

}} // namespace esve::util

#endif
