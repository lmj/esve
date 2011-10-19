//
// Tope_Geom is a high-level class encompassing the low-level Tope
// geometric primitive along with file data.
//
// A valid file must be given in the constructor else an exception is
// thrown.  (The Default_Reader, included in the Universal_Reader,
// accepts the empty string.)
//

#ifndef apps_topeviewer_Tope_Geom_hxx
#define apps_topeviewer_Tope_Geom_hxx

#include "Tope_Mod.hxx"
#include "Tope_File.hxx"
#include <esve/components/dim4/Report_Min_Z.hxx>
#include <esve/engine/dim4/Make_Geom.hxx>

class Tope_Geom
    : public esve::components::dim4::Report_Min_Z
             <
                 esve::engine::dim4::Make_Geom
                 <
                     Tope_Mod
                 >
             >
{
private:
    typedef
    esve::components::dim4::Report_Min_Z
             <
                 esve::engine::dim4::Make_Geom
                 <
                     Tope_Mod
                 >
             >
    super ;

    Tope_Geom( const Tope_Geom & ) ;
    Tope_Geom & operator=( const Tope_Geom & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;

public:
    // throws if reading fails
    Tope_Geom( const std::string & filename ) ;

    // Read another file; throw on failure.
    void read( const std::string & filename ) ;

    // See Tope_File.
    void add_config( const Tope_File::Config & ) ;
    const std::string & filename() const ;

    // State info for Tope_File.
    bool has_configs() const ;
    void next_config() ;
    const Tope_File::Config & current_config() const ;

    ~Tope_Geom() ;
} ;

#endif
