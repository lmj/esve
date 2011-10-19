//
// 2x2 quaternion matrices.
//

#ifndef esve_math_matrix_2h_hxx
#define esve_math_matrix_2h_hxx

#include <istream>
#include <ostream>

namespace esve { namespace math {

namespace matrix_2h_namespace {

template< typename T_quat >
class matrix_2h
{
public:
    typedef T_quat quat ;
    typedef typename T_quat::value_type scalar ;

    //
    // [ 1  0 ]
    // [ 0  1 ]
    //
    matrix_2h() ;

    //
    // [ a  b ]
    // [ c  d ]
    //
    matrix_2h( const quat & a, const quat & b,
               const quat & c, const quat & d ) ;

    // compiler writes memberwise copy and assign

    /////////////////////////////////////
    // readers

    const quat & a() const
    {
        return ma ;
    }

    const quat & b() const
    {
        return mb ;
    }

    const quat & c() const
    {
        return mc ;
    }

    const quat & d() const
    {
        return md ;
    }

    /////////////////////////////////////
    // writers

    void a( const quat & a )
    {
        ma = a ;
    }

    void b( const quat & b )
    {
        mb = b ;
    }

    void c( const quat & c )
    {
        mc = c ;
    }

    void d( const quat & d )
    {
        md = d ;
    }

    /////////////////////////////////////
    // other 

    // *this := 1
    void identity() ;

    // *this := left * (*this)
    void left_act( const matrix_2h & left ) ;

    // *this := (*this) * right
    void right_act( const matrix_2h & right ) ;

    // *this := (*this)^(-1)
    void invert() ;

    // *this := transpose(conj(*this))
    void adjoint() ;

    // a*d - b*c
    quat det() const ;

    // det((*this)*adjoint(*this))
    scalar norm() const ;

    // elementwise compare
    bool operator==( const matrix_2h & ) const ;
    bool operator!=( const matrix_2h & ) const ;

private:
    quat ma ;
    quat mb ;
    quat mc ;
    quat md ;
} ;

template< typename T_quat, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & out,
            const matrix_2h<T_quat> & matrix ) ;

template< typename T_quat, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & in,
            matrix_2h<T_quat> & matrix ) ;

template< typename T_quat >
inline
typename T_quat::value_type
norm( const T_quat & a )
{
    return norm(a) ;
}

template< typename T_quat >
inline
matrix_2h<T_quat>::
matrix_2h()
    : ma(scalar(1)),
      mb(scalar(0)),
      mc(scalar(0)),
      md(scalar(1))
{
}

template< typename T_quat >
inline
matrix_2h<T_quat>::
matrix_2h( const quat & a, const quat & b,
           const quat & c, const quat & d )
    : ma(a),
      mb(b),
      mc(c),
      md(d)
{
}

template< typename T_quat >
inline
bool
matrix_2h<T_quat>::
operator==( const matrix_2h & f ) const
{
    return
        ma == f.ma &&
        mb == f.mb &&
        mc == f.mc &&
        md == f.md ;
}

template< typename T_quat >
inline
bool
matrix_2h<T_quat>::
operator!=( const matrix_2h & f ) const
{
    return
        ma != f.ma ||
        mb != f.mb ||
        mc != f.mc ||
        md != f.md ;
}

template< typename T_quat >
void
matrix_2h<T_quat>::
identity()
{
    ma = quat(scalar(1)) ;
    mb = quat(scalar(0)) ;
    mc = quat(scalar(0)) ;
    md = quat(scalar(1)) ;
}

template< typename T_quat >
void
matrix_2h<T_quat>::
left_act( const matrix_2h & left )
{
    const matrix_2h right = *this ;

    ma = left.ma*right.ma + left.mb*right.mc ;
    mb = left.ma*right.mb + left.mb*right.md ;
    mc = left.mc*right.ma + left.md*right.mc ;
    md = left.mc*right.mb + left.md*right.md ;
}

template< typename T_quat >
void
matrix_2h<T_quat>::
right_act( const matrix_2h & right )
{
    const matrix_2h left = *this ;

    ma = left.ma*right.ma + left.mb*right.mc ;
    mb = left.ma*right.mb + left.mb*right.md ;
    mc = left.mc*right.ma + left.md*right.mc ;
    md = left.mc*right.mb + left.md*right.md ;
}

template< typename T_quat >
T_quat
matrix_2h<T_quat>::
det() const
{
    return ma*md - mb*mc ;
}

template< typename T_quat >
void
matrix_2h<T_quat>::
adjoint()
{
    ma = conj(ma) ;
    md = conj(md) ;

    const quat tmp = mb ;
    mb = conj(mc) ;
    mc = conj(tmp) ;
}

template< typename T_quat >
typename matrix_2h<T_quat>::scalar
matrix_2h<T_quat>::
norm() const
{
    using matrix_2h_namespace::norm ;

    return
        norm(ma)*norm(md)
        +
        norm(mb)*norm(mc)
        -
        scalar(2)*dot(ma*conj(mc),
                      mb*conj(md)) ;
}

template< typename T_quat >
void
matrix_2h<T_quat>::
invert()
{
    using matrix_2h_namespace::norm ;

    const quat a = ma ;
    const quat b = mb ;
    const quat c = mc ;
    const quat d = md ;

    const scalar norm_a = norm(a) ;
    const scalar norm_b = norm(b) ;
    const scalar norm_c = norm(c) ;
    const scalar norm_d = norm(d) ;

    const quat a_conj_c = a*conj(c) ;
    const quat b_conj_d = b*conj(d) ;

    const scalar nm =
        norm_a*norm_d
        +
        norm_b*norm_c
        -
        scalar(2)
        *
        dot(a_conj_c, b_conj_d) ;

    ma = conj(a*norm_d - b_conj_d*c)/nm ;
    mb = conj(c*norm_b - conj(b_conj_d)*a)/nm ;
    mc = conj(b*norm_c - a_conj_c*d)/nm ;
    md = conj(d*norm_a - conj(a_conj_c)*b)/nm ;
}

template< typename T_quat, typename T_Char, typename T_Traits >
std::basic_ostream<T_Char, T_Traits> &
operator<<( std::basic_ostream<T_Char, T_Traits> & out,
            const matrix_2h<T_quat> & matrix )
{
    out << '('
        << matrix.a()
        << ','
        << matrix.b()
        << ','
        << matrix.c()
        << ','
        << matrix.d()
        << ')' ;

    return out ;
}

template< typename T_quat, typename T_Char, typename T_Traits >
std::basic_istream<T_Char, T_Traits> &
operator>>( std::basic_istream<T_Char, T_Traits> & in,
            matrix_2h<T_quat> & matrix )
{
    T_Char ch ;
    T_quat a ;
    T_quat b ;
    T_quat c ;
    T_quat d ;

    ch = 0 ;
    in >> ch ;
    if( ch != '(' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> a >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> b >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> c >> ch ;
    if( ch != ',' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    ch = 0 ;
    in >> d >> ch ;
    if( ch != ')' )
    {
        in.setstate(std::ios_base::failbit) ;
        return in ;
    }

    matrix.a(a) ;
    matrix.b(b) ;
    matrix.c(c) ;
    matrix.d(d) ;

    return in ;
}

} // namespace matrix_2h_namespace

using matrix_2h_namespace::matrix_2h ;

}} // namespace esve::math

#endif

