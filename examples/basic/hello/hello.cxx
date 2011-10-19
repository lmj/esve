
#include <esve/viewers/dim3/Basic_Viewer.hxx>
#include <esve/components/dim3/Rotation_Handler.hxx>
#include <esve/engine/dim3/Make_Geom.hxx>
#include <esve/geom/dim3/Icosahedron.hxx>

using esve::viewers::dim3::Basic_Viewer ;
using esve::components::dim3::Rotation_Handler ;
using esve::engine::dim3::Make_Geom ;
using esve::geom::dim3::Icosahedron ;

int main()
{
    Make_Geom<Icosahedron> icos ;
    Rotation_Handler rotation_handler(icos.peek_transform()) ;

    Basic_Viewer viewer ;
    viewer.add_geom(icos) ;
    viewer.add_handler(rotation_handler) ;
    viewer.create_light() ;
    viewer.create_camera("Hello, world!") ;

    return viewer.takeover() ;
}
