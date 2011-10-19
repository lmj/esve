//
// Command-line utility for unordered single-char options.
//
// Throws an exception if options are unrecognized or malformed.
//

#ifndef esve_components_dimn_Command_Line_hxx
#define esve_components_dimn_Command_Line_hxx

#include <esve/util/Command_Line.hxx>
#include <stdexcept>

namespace esve { namespace components { namespace dimn {

class Command_Line
    : public util::Command_Line
{
private:
    typedef util::Command_Line super ;

    Command_Line( const Command_Line & ) ;
    Command_Line & operator=( const Command_Line & ) ;
    
public:
    struct Error
        : public std::runtime_error
    {
        Error( const std::string & what ) ;
        ~Error() throw() ;
    } ;

    Command_Line( int argc, char** argv, const std::string & optstring ) ;

    ~Command_Line() ;
} ;

}}} // namespace esve::components::dimn

#endif
