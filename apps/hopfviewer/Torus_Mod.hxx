//
// Color/lighting modifications to Torus.
//

#ifndef apps_hopfviewer_Torus_Mod_hxx
#define apps_hopfviewer_Torus_Mod_hxx

#include "Torus.hxx"

class Torus_Mod
    : public Torus
{
private:
    typedef Torus super ;
    
public:
    Torus_Mod() ;

    // compiler writes memberwise copy and assign

    ~Torus_Mod() ;

protected:
    // override
    void draw() ;
} ;

#endif
