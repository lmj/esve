//
// Tutorial on Simple_Viewer and on defining four-dimensional objects
// for the engine.
//
// Defines a canonical 4D cube.
//
// If you are just interested in the 4D cube, run
//
//     ./topeviewer ./data/8-cell.v
//
// from the topeviewer directory.
//

#include <esve/viewers/dim4/Simple_Viewer.hxx>
#include <esve/engine/dim4/Make_Geom.hxx>
#include <esve/types/rgba.hxx>
#include <esve/types/quat.hxx>
#include <esve/types/real.hxx>
#include <esve/gl/gl.hxx>
#include <iostream>

using esve::viewers::dim4::Simple_Viewer ;
using esve::engine::dim4::Make_Geom ;
using esve::types::rgba ;
using esve::types::quat ;
using esve::types::real ;

////////////////////////////////////////////////////////////
//
// Cube
//
////////////////////////////////////////////////////////////

class Cube
{
private:
    quat m_points[16] ;
    quat m_transformed_points[16] ;
    real m_hue ;

public:
    Cube()
        : m_hue(0)
    {
        const real r = real(0.5) ;

        m_points[0]  = quat( r,  r,  r,  r) ;
        m_points[1]  = quat( r,  r,  r, -r) ;
        m_points[2]  = quat( r,  r, -r,  r) ;
        m_points[3]  = quat( r,  r, -r, -r) ;
        m_points[4]  = quat( r, -r,  r,  r) ;
        m_points[5]  = quat( r, -r,  r, -r) ;
        m_points[6]  = quat( r, -r, -r,  r) ;
        m_points[7]  = quat( r, -r, -r, -r) ;

        m_points[8]  = quat(-r,  r,  r,  r) ;
        m_points[9]  = quat(-r,  r,  r, -r) ;
        m_points[10] = quat(-r,  r, -r,  r) ;
        m_points[11] = quat(-r,  r, -r, -r) ;
        m_points[12] = quat(-r, -r,  r,  r) ;
        m_points[13] = quat(-r, -r,  r, -r) ;
        m_points[14] = quat(-r, -r, -r,  r) ;
        m_points[15] = quat(-r, -r, -r, -r) ;
    }

    real hue() const
    {
        return m_hue ;
    }

    void hue( real a )
    {
        m_hue = a ;
    }

    virtual ~Cube() { }

protected:
    // Frame system. See esve/engine/dim4/Make_Frame.hxx

    // Any iterator which dereferences to quat is accepted (not just
    // quat pointers).

    const quat* points_begin() const
    {
        return m_points ;
    }

    const quat* points_end() const
    {
        return m_points + 16 ;
    }

    quat* transformed_points_begin()
    {
        return m_transformed_points ;
    }

    virtual bool changed() const
    {
        // return true if m_points needs to be recalculated.
        return false ;
    }

    virtual void pretransform()
    {
        // calculate m_points here, if you wish
    }

    virtual void posttransform()
    {
        // calculate normals here, if any
    }

    // OpenGL drawing routine

    virtual void draw()
    {
        // the engine has transformed m_points and placed the result in
        // m_transformed_points.

        rgba color = rgba::from_hsva(m_hue, 1, 1, 1) ;

        glPushAttrib(GL_LIGHTING) ;
        glDisable(GL_LIGHTING) ;
        glBegin(GL_LINES) ;

        glColor3f(color.red(), color.green(), color.blue()) ;

        for( int i = 0 ; i != 16 - 1 ; ++i )
        {
            for( int j = i + 1 ; j != 16 ; ++j )
            {
                const real len = abs(m_points[i] - m_points[j])  ;

                if( len > 0.9 && len < 1.1 )
                {
                    glVertex3f(m_transformed_points[i].x(),
                               m_transformed_points[i].y(),
                               m_transformed_points[i].z()) ;

                    glVertex3f(m_transformed_points[j].x(),
                               m_transformed_points[j].y(),
                               m_transformed_points[j].z()) ;
                }
            }
        }

        glEnd() ;
        glPopAttrib() ;
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
    
    // Give Cube the appropriate engine hooks.
    Make_Geom<Cube> cube ;

    Valuator & hue_valuator ;

public:
    Viewer( int argc, char** argv )
        : super(argc, argv, "simple4d"),
          cube(),
          hue_valuator(create_valuator(0.5, "hue").range(0, 1).step(0.001))
    {
        add_geom(cube) ;

        create_scaling_valuator() ;
        create_inversion_valuator().value(1).range(0, 1) ;
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
            cube.hue(valuator.value()) ;
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
