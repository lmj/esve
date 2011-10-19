//
// OpenGL-style RGBA color
//

#ifndef esve_base_dimn_rgba_hxx
#define esve_base_dimn_rgba_hxx

namespace esve { namespace base { namespace dimn {

template< typename T_value_type >
class rgba
{
private:
    typedef T_value_type m_value_type ;

    m_value_type mr ;
    m_value_type mg ;
    m_value_type mb ;
    m_value_type ma ;

public:
    typedef m_value_type value_type ;

    struct from_hsva
    {
        value_type h ;
        value_type s ;
        value_type v ;
        value_type a ;

        from_hsva( value_type h_,
                   value_type s_,
                   value_type v_,
                   value_type a_ )
            : h(h_),
              s(s_),
              v(v_),
              a(a_) { }
    } ;

    rgba()
        : mr(0),
          mg(0),
          mb(0),
          ma(0) { }

    rgba( value_type r,
          value_type g,
          value_type b,
          value_type a )
        : mr(r),
          mg(g),
          mb(b),
          ma(a) { }

    rgba( const from_hsva & ) ;

    // compiler writes memberwise copy and assign

    value_type red() const
    {
        return mr ;
    }

    value_type green() const
    {
        return mg ;
    }

    value_type blue() const
    {
        return mb ;
    }

    value_type alpha() const
    {
        return ma ;
    }

    void red( value_type s )
    {
        mr = s ;
    }

    void green( value_type s )
    {
        mg = s ;
    }

    void blue( value_type s )
    {
        mb = s ;
    }

    void alpha( value_type s )
    {
        ma = s ;
    }

    const value_type* data() const
    {
        return &mr ;
    }
} ;

}}} // namespace esve::base::dimn

#include <esve/base/dimn/rgba.template.cxx>

#endif

