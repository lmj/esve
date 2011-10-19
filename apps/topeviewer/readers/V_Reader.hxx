
#ifndef apps_topeviewer_readers_V_Reader_hxx
#define apps_topeviewer_readers_V_Reader_hxx

#include "Line_Oriented_Reader.hxx"

class V_Reader
    : public Line_Oriented_Reader
{
private:
    typedef Line_Oriented_Reader super ;

    V_Reader( const V_Reader & ) ;
    V_Reader & operator=( const V_Reader & ) ;

public:
    V_Reader() ;
    ~V_Reader() ;

protected:
    const std::string & start_comment() const ;
    bool test_read( std::istream & in, Tope_File::Points & ) ;
} ;

#endif

