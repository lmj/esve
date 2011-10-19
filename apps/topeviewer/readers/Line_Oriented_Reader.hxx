
#ifndef apps_topeviewer_readers_Line_Oriented_Reader_hxx
#define apps_topeviewer_readers_Line_Oriented_Reader_hxx

#include "Tope_File.hxx"
#include "Tope_Reader.hxx"
#include <memory>
#include <iosfwd>
#include <string>

class Line_Oriented_Reader
    : virtual public Tope_Reader
{
public:
    Line_Oriented_Reader() ;

    std::auto_ptr<Tope_File> read( const std::string & filename ) ;

    ~Line_Oriented_Reader() ;

protected:
    // Hook to subclass.
    // What comments look like, e.g., "#" or "//"
    virtual const std::string & start_comment() const = 0 ;

    // Hook to subclass.
    // Read file format associated with this particular class.
    // Return false if format is unrecognized.
    virtual bool test_read( std::istream & , Tope_File::Points & ) = 0 ;

    //
    // Returns the next non-blank line after comments are stripped.
    //
    // Use this in the implementation of test_read().  In fact it is
    // invalid to use this function outside of test_read().
    //
    void next_line( std::istream & , std::string & ) ;

private:
    Line_Oriented_Reader( const Line_Oriented_Reader & ) ;
    Line_Oriented_Reader & operator=( const Line_Oriented_Reader & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

