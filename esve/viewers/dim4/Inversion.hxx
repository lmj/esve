
#ifndef esve_viewers_dim4_Inversion_hxx
#define esve_viewers_dim4_Inversion_hxx

#include <esve/types/real.hxx>

namespace esve { namespace viewers { namespace dim4 {

class Inversion
{
public:
    virtual void inversion( types::real ) = 0 ;
    virtual types::real inversion() const = 0 ;

    virtual ~Inversion() = 0 ;

protected:
    Inversion() ;

private:
    Inversion( const Inversion & ) ;
    Inversion & operator=( const Inversion & ) ;
} ;

}}} // namespace esve::viewers::dim4

#endif
