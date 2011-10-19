
#ifndef esve_geom_dim3_Icosahedron_hxx
#define esve_geom_dim3_Icosahedron_hxx

namespace esve { namespace geom { namespace dim3 {

class Icosahedron
{
public:
    Icosahedron() ;
    virtual ~Icosahedron() ;

protected:
    virtual void draw() ;
    virtual void compute() ;

private:
    Icosahedron( const Icosahedron & ) ;
    Icosahedron & operator=( const Icosahedron & ) ;
} ;

}}} // namespace esve::geom::dim3

#endif

