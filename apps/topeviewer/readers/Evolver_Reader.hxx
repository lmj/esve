
#ifndef apps_topeviewer_readers_Evolver_Reader_hxx
#define apps_topeviewer_readers_Evolver_Reader_hxx

#include "Line_Oriented_Reader.hxx"

class Evolver_Reader
    : public Line_Oriented_Reader
{
private:
    typedef Line_Oriented_Reader super ;

    Evolver_Reader( const Evolver_Reader & ) ;
    Evolver_Reader & operator=( const Evolver_Reader & ) ;

public:
    Evolver_Reader() ;
    ~Evolver_Reader() ;

protected:
    const std::string & start_comment() const ;
    bool test_read( std::istream & in, Tope_File::Points & ) ;
} ;

#endif

