
#ifndef apps_topeviewer_readers_Universal_Reader_hxx
#define apps_topeviewer_readers_Universal_Reader_hxx

#include "Tope_Reader.hxx"
#include <memory>

class Universal_Reader
    : virtual public Tope_Reader
{
public:
    Universal_Reader() ;
    
    std::auto_ptr<Tope_File> read( const std::string & filename ) ;
    
    ~Universal_Reader() ;

private:
    Universal_Reader( const Universal_Reader & ) ;
    Universal_Reader & operator=( const Universal_Reader & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif
