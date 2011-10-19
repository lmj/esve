//
// Common file interface for Topes.
//

#ifndef apps_topeviewer_Tope_File_hxx
#define apps_topeviewer_Tope_File_hxx

#include <vector>
#include <string>
#include <stdexcept>

class Tope_File
{
public:
    struct Error
        : public std::runtime_error
    {
        std::string filename ;
        
        Error( const std::string & what,
               const std::string & filename ) ;
        ~Error() throw() ;
    } ;
    
    struct Read_Error
        : public Error
    {
        Read_Error( const std::string & filename ) ;
        ~Read_Error() throw() ;
    } ;
    
    struct Write_Error
        : public Error
    {
        Write_Error( const std::string & filename ) ;
        ~Write_Error() throw() ;
    } ;
    
    typedef std::vector<double> Point ;
    typedef std::vector<Point> Points ;
    typedef std::string Config ;
    typedef std::vector<Config> Configs ;

    // Filename.
    virtual const std::string & filename() const = 0 ;

    // Polytope points.
    virtual const Points & points() const = 0 ;

    // Ambient dimension.
    virtual unsigned int dimension() const = 0 ;

    // Configurations.
    virtual const Configs & configs() const = 0 ;
    virtual void add_config( const Config & ) = 0 ;

    virtual ~Tope_File() = 0 ;

protected:
    Tope_File() ;

private:
    Tope_File( const Tope_File & ) ;
    Tope_File & operator=( const Tope_File & ) ;
} ;

#endif

