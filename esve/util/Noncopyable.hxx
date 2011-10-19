
#ifndef esve_util_Noncopyable_hxx
#define esve_util_Noncopyable_hxx

class Noncopyable
{
protected:
    Noncopyable()
    {
    }
    
    ~Noncopyable()
    {
    }
    
private:
    Noncopyable( const Noncopyable & ) ;
    Noncopyable & operator=( const Noncopyable & ) ;
} ;

#endif
