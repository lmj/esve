
#ifndef esve_geom_dim3_Stars_hxx
#define esve_geom_dim3_Stars_hxx

namespace esve { namespace geom { namespace dim3 {

class Stars
{
public:
    Stars() ;
    virtual ~Stars() ;

protected:
    virtual void draw() ;
    virtual void compute() ;

private:
    Stars( const Stars & ) ;
    Stars & operator=( const Stars & ) ;
} ;

}}} // namespace esve::geom::dim3

#endif

