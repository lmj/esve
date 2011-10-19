
#include "Viewer.hxx"
#include "Tope_File.hxx"
#include <esve/components/dimn/Command_Line.hxx>
#include <iostream>

using esve::components::dimn::Command_Line ;

int main( int argc, char** argv )
try
{
    return Viewer(argc, argv).takeover() ;
}
catch( Command_Line::Error & e )
{
    std::cerr << e.what() << std::endl ;
    return 1 ;
}
catch( Tope_File::Read_Error & e )
{
    std::cerr << e.what() << std::endl ;
    return 1 ;
}

