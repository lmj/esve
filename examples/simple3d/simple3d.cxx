//
// Tutorial on Simple_Viewer and on defining three-dimensional objects
// for the engine.
//

#include <esve/viewers/dim3/Simple_Viewer.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/types/rgba.hxx>
#include <esve/gl/gl.hxx>
#include <iostream>

using esve::viewers::dim3::Simple_Viewer ;
using esve::engine::dim3::Make_Geom ;
using esve::types::rgba ;

////////////////////////////////////////////////////////////
//
// Square
//
////////////////////////////////////////////////////////////

class Square
{
private:
    double m_hue ;

public:
    Square()
        : m_hue(0) { }

    void hue( double a )
    {
        m_hue = a ;
    }

    double hue() const
    {
        return m_hue ;
    }

    virtual ~Square() { }

protected:
    void draw()
    {
        rgba color = rgba::from_hsva(m_hue, 1, 1, 1) ;

        glBegin(GL_QUADS) ;

        glColor3f(color.red(), color.green(), color.blue()) ;

        glNormal3d(0.0, 0.0, 1.0) ;

        glVertex3d( 1.0,  1.0,  0.0) ;
        glVertex3d(-1.0,  1.0,  0.0) ;
        glVertex3d(-1.0, -1.0,  0.0) ;
        glVertex3d( 1.0, -1.0,  0.0) ;

        glEnd() ;
    }

    void compute()
    {
        // put significant calculations here, if any
    }
} ;

////////////////////////////////////////////////////////////
//
// Viewer
//
////////////////////////////////////////////////////////////

class Viewer : public Simple_Viewer
{
private:
    typedef Simple_Viewer super ;
    
    // Give Square the appropriate engine hooks.
    Make_Geom<Square> square ;

    Valuator & hue_valuator ;

public:
    Viewer( int argc, char** argv )
        : super(argc, argv, "simple3d"),
          square(),
          hue_valuator(create_valuator(0.5, "hue").range(0, 1).step(0.001))
    {
        add_geom(square) ;
        create_scaling_valuator() ;
    }

protected:
    bool handle_key_push( Key key, const Keyboard & )
    {
        // return true if key was handled, false if ignored

        if( key == 'k' )
        {
            std::cout << "k pushed" << std::endl ;
            return true ;
        }

        return false ;
    }

    bool handle_valuator( const Valuator & valuator )
    {
        // return true if valuator was handled, false if ignored

        if( &valuator == &hue_valuator )
        {
            square.hue(valuator.value()) ;
            return true ;
        }

        return false ;
    }

    using super::handle_valuator ;
} ;

////////////////////////////////////////////////////////////
//
// main
//
////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    return Viewer(argc, argv).takeover() ;
}
