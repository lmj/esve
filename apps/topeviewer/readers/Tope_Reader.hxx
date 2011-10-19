
#ifndef apps_topeviewer_readers_Tope_Reader_hxx
#define apps_topeviewer_readers_Tope_Reader_hxx

#include <string>
#include <memory>

class Tope_File ;

class Tope_Reader
{
public:
    //
    // Return a new'd Tope_File, or throw Tope_File::Read_Error if the
    // format was not recognized (or some other issue).
    //
    // The input is not an istream because config data may be written
    // to the file.
    //
    virtual std::auto_ptr<Tope_File> read( const std::string & filename ) = 0 ;

    virtual ~Tope_Reader() = 0 ;

protected:
    Tope_Reader() ;

private:
    Tope_Reader( const Tope_Reader & ) ;
    Tope_Reader & operator=( const Tope_Reader & ) ;
} ;

#endif

