
#ifndef apps_topeviewer_readers_Default_Reader_hxx
#define apps_topeviewer_readers_Default_Reader_hxx

#include "Tope_Reader.hxx"

class Default_Reader
    : virtual public Tope_Reader
{
public:
    Default_Reader() ;

    // returns a default polytope when passed the empty string
    std::auto_ptr<Tope_File> read( const std::string & filename ) ;

    ~Default_Reader() ;

private:
    Default_Reader( const Default_Reader & ) ;
    Default_Reader & operator=( const Default_Reader & ) ;
} ;


#endif
