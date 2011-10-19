
#include <esve/viewers/dim3/Default_Initializer.hxx>
#include <esve/gl/gl.hxx>

namespace esve { namespace viewers { namespace dim3 {

Default_Initializer::
Default_Initializer()
{
}

Default_Initializer::
~Default_Initializer()
{
}

void
Default_Initializer::
draw()
{
}

void
Default_Initializer::
draw_initialize()
{
    const GLfloat global_ambient[] = { 0.0, 0.0, 0.0, 1.0 } ;
    const GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 } ;
    const GLfloat material_shininess[] = { 35.0 } ;
    const GLfloat back_color[] = { 0.7, 0.7, 0.7, 1.0 } ;

    glEnable(GL_LIGHTING) ;
    glEnable(GL_COLOR_MATERIAL) ;
    glEnable(GL_DEPTH_TEST) ;
    glEnable(GL_NORMALIZE) ;

    glShadeModel(GL_SMOOTH) ;

    glClearColor(0, 0, 0, 0) ;

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient) ;

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess) ;

    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR) ;
    glColor3fv(material_specular) ;
    glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE) ;
    glColor3fv(back_color) ;
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
}

}}} // namespace esve::viewers::dim3
