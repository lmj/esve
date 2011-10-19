//
// Color/lighting modifications to Tope
//

#ifndef apps_topeviewer_Tope_Mod_hxx
#define apps_topeviewer_Tope_Mod_hxx

#include "Tope.hxx"

class Tope_Mod
    : public Tope
{
private:
    typedef Tope super ;
    
public:
    Tope_Mod() ;

    // compiler writes memberwise copy and assign
    
    ~Tope_Mod() ;

protected:
    void draw_balls() ;
    void draw_tubes() ;
    void draw_lines() ;
} ;

#endif
