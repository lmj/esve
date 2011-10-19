
#include "Tope_Mod.hxx"
#include <esve/gl/gl.hxx>

using esve::gl::gl ;

Tope_Mod::
Tope_Mod()
    : super()
{
}

Tope_Mod::
~Tope_Mod()
{
}

void
Tope_Mod::
draw_balls()
{
    gl::PushAttrib sentry(GL_LIGHTING_BIT) ;

    glDisable(GL_COLOR_MATERIAL) ;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;

    const GLfloat material_ambient[] = { 1.0, 1.0, 1.0, 1.0 } ;
    const GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 } ;
    const GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 } ;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient) ;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse) ;
    glColor4fv(color) ;

    super::draw_balls() ;
}

void
Tope_Mod::
draw_tubes()
{
    gl::PushAttrib sentry(GL_LIGHTING_BIT) ;

    const GLfloat material_specular[] = { 0.6, 0.6, 0.6, 1.0 } ;
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR) ;
    glColor3fv(material_specular) ;
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;

    super::draw_tubes() ;
}

void
Tope_Mod::
draw_lines()
{
    gl::PushAttrib sentry(GL_LIGHTING_BIT) ;

    glDisable(GL_LIGHTING) ;
    glDisable(GL_COLOR_MATERIAL) ;
    
    super::draw_lines() ;
}

