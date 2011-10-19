
#include <esve/base/dimn/rgba.hxx>
#include <cmath>

namespace esve { namespace base { namespace dimn {

template< typename T_value_type >
rgba<T_value_type>::
rgba( const from_hsva & z )
    // delay data initialization
{
    const value_type h = z.h*value_type(6) ;
    const value_type t = std::floor(h) ;
    const value_type f = h - t ;

    switch( int(t) )
    {
    case 0:
    case 6:
    default:
        mr = z.v ;
        mg = z.v*(value_type(1) - z.s*(value_type(1) - f)) ;
        mb = z.v*(value_type(1) - z.s) ;
        ma = z.a ;
        return ;

    case 1:
        mr = z.v*(value_type(1) - z.s*f) ;
        mg = z.v ;
        mb = z.v*(value_type(1) - z.s) ;
        ma = z.a ;
        return ;

    case 2:
        mr = z.v*(value_type(1) - z.s) ;
        mg = z.v ;
        mb = z.v*(value_type(1) - z.s*(value_type(1) - f)) ;
        ma = z.a ;
        return ;

    case 3:
        mr = z.v*(value_type(1) - z.s) ;
        mg = z.v*(value_type(1) - z.s*f) ;
        mb = z.v ;
        ma = z.a ;
        return ;

    case 4:
        mr = z.v*(value_type(1) - z.s*(value_type(1) - f)) ;
        mg = z.v*(value_type(1) - z.s) ;
        mb = z.v ;
        ma = z.a ;
        return ;

    case 5:
        mr = z.v ;
        mg = z.v*(value_type(1) - z.s) ;
        mb = z.v*(value_type(1) - z.s*f) ;
        ma = z.a ;
        return ;
    }
}

}}} // namespace esve::base::dimn
