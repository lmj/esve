
#include <esve/components/dimn/Command_Line.hxx>

namespace esve { namespace components { namespace dimn {

Command_Line::
Command_Line( int argc, char** argv, const std::string & optstring )
    : super(argc, argv, optstring)
{
    if( super::error() != "" )
    {
        throw Error(super::error()) ;
    }
}

Command_Line::
~Command_Line()
{
}

Command_Line::
Error::
Error( const std::string & what )
    : std::runtime_error(what)
{
}

Command_Line::
Error::
~Error() throw()
{
}

}}} // namespace esve::components::dimn
