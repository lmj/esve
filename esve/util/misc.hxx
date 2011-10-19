
#ifndef esve_util_misc_hxx
#define esve_util_misc_hxx

namespace esve { namespace util {

namespace misc {

template< class U >
inline void unused( const U & )
{
}

template< class T, class U >
inline T implicit_cast( const U & u )
{
    return u ;
}

class Complete_Object_Flag
{
public:
    Complete_Object_Flag()
        :
        m_flag(false)
    {
    }
    
    operator bool() const
    {
        return m_flag ;
    }
    
private:
    friend class Complete_Object_Guard ;
    
    Complete_Object_Flag( const Complete_Object_Flag & ) ;
    Complete_Object_Flag & operator=( const Complete_Object_Flag & ) ;
    
    bool m_flag ;
} ;

class Complete_Object_Guard
{
public:
    Complete_Object_Guard( Complete_Object_Flag & flag )
        :
        m_flag(flag.m_flag)
    {
        m_flag = true ;
    }
    
    ~Complete_Object_Guard()
    {
        m_flag = false ;
    }
    
private:
    Complete_Object_Guard( const Complete_Object_Guard & ) ;
    Complete_Object_Guard & operator=( const Complete_Object_Guard & ) ;
    
    bool & m_flag ;
} ;

} // namespace misc

}} // namespace esve::util

#endif
