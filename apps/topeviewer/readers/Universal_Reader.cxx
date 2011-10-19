
#include "Universal_Reader.hxx"
#include "V_Reader.hxx"
#include "Evolver_Reader.hxx"
#include "Default_Reader.hxx"
#include <esve/util/auto_ptr_vector.hxx>

struct Universal_Reader::Private
{
    typedef esve::util::auto_ptr_vector<Tope_Reader> Readers ;
    Readers readers ;

    Private()
        : readers()
    {
        readers.push_back(std::auto_ptr<Tope_Reader>(
            new Default_Reader())) ;

        readers.push_back(std::auto_ptr<Tope_Reader>(
            new V_Reader())) ;

        readers.push_back(std::auto_ptr<Tope_Reader>(
            new Evolver_Reader())) ;

        //
        // put additional formats here  <----------------------------
        //
    }
} ;

Universal_Reader::
Universal_Reader()
    : m(new Private())
{
}

Universal_Reader::
~Universal_Reader()
{
}

std::auto_ptr<Tope_File>
Universal_Reader::
read( const std::string & filename )
{
    for( Private::Readers::const_iterator i =
             m->readers.begin() ;
         i != m->readers.end() ;
         ++i )
    {
        try
        {
            return (**i).read(filename) ;
        }
        catch( Tope_File::Read_Error & )
        {
            // try the next one
        }
    }

    // nobody recognized the format
    throw Tope_File::Read_Error(filename) ;
}
