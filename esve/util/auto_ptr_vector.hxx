//
// A std::vector which owns its pointer elements.
//
// A raw pointer is returned from accessors such as back() with the
// understanding that the user should not delete it.  Remove elements
// with release().
//
// Note the template parameter differs from std::vector,
//
//      std::vector<T*>   <----->   auto_ptr_vector<T>
//

#ifndef esve_util_auto_ptr_vector_hxx
#define esve_util_auto_ptr_vector_hxx

#include <vector>
#include <memory>

namespace esve { namespace util {

template< typename T, typename A = std::allocator<T*> >
class auto_ptr_vector
{
private:
    typedef std::vector<T*, A> m_Base ;
    
    // disallowed
    typedef typename m_Base::pointer pointer ;
    typedef typename m_Base::iterator iterator ;
    typedef typename m_Base::reverse_iterator reverse_iterator ;
    typedef typename m_Base::reference reference ;

    // disallowed
    auto_ptr_vector & operator=( const auto_ptr_vector & ) ;
    auto_ptr_vector( const auto_ptr_vector & ) ;

    m_Base m ;

public:
    ///////////////////////////////////////////////////
    // types
    ///////////////////////////////////////////////////

    typedef typename m_Base::value_type value_type ;
    typedef typename m_Base::const_pointer const_pointer ;
    typedef typename m_Base::const_iterator const_iterator ;
    typedef typename m_Base::const_reverse_iterator const_reverse_iterator ;
    typedef typename m_Base::const_reference const_reference ;
    typedef typename m_Base::size_type size_type ; 
    typedef typename m_Base::difference_type difference_type ;
    typedef typename m_Base::allocator_type allocator_type ;

    ///////////////////////////////////////////////////
    // auto_ptr_vector-specific methods
    ///////////////////////////////////////////////////

    //
    // The only constructor.
    //
    explicit auto_ptr_vector( const allocator_type & = allocator_type() ) ;

    //
    // Delete all elements (back to front).
    //
    ~auto_ptr_vector() ;

    //
    // Hand off ownership to the vector.
    //
    void push_back( std::auto_ptr<T> ) ;

    //
    // Release ownership of the last element and remove it from the
    // container.
    //
    std::auto_ptr<T> release_back() ;

    //
    // Release ownership of this element and remove it from the
    // container.
    //
    std::auto_ptr<T> release( const_iterator ) ;

    //
    // Delete all elements (back to front).
    //
    void clear() ;

    ///////////////////////////////////////////////////
    // selected std::vector methods
    ///////////////////////////////////////////////////

    void reserve( size_type n )
    {
        m.reserve(n) ;
    }

    const_reference operator[]( size_type n ) const
    {
        return m.operator[](n) ;
    }

    const_reference at( size_type n ) const
    {
        return m.at(n) ;
    }

    const_reference front() const
    {
        return m.front() ;
    }

    const_reference back() const
    {
        return m.back() ;
    }

    const_iterator begin() const
    {
        return m.begin() ;
    }

    const_iterator end() const
    {
        return m.end() ;
    }

    const_reverse_iterator rbegin() const
    {
        return m.rbegin() ;
    }

    const_reverse_iterator rend() const
    {
        return m.rend() ;
    }

    size_type size() const
    {
        return m.size() ;
    }

    size_type max_size() const
    {
        return m.max_size() ;
    }

    size_type capacity() const
    {
        return m.capacity() ;
    }

    bool empty() const
    {
        return m.empty() ;
    }

    allocator_type get_allocator() const
    {
        return m.get_allocator() ;
    }
} ;

template< typename T, typename A >
auto_ptr_vector<T, A>::
auto_ptr_vector( const allocator_type & a )
    : m(a)
{
}

template< typename T, typename A >
auto_ptr_vector<T, A>::
~auto_ptr_vector()
{
    auto_ptr_vector::clear() ;
}

template< typename T, typename A >
std::auto_ptr<T>
auto_ptr_vector<T, A>::
release( const_iterator pos )
{
    T* result = *pos ;
    
    // const_iterator workaround
    m.erase(m.begin() + (pos - m.begin())) ;
    
    return std::auto_ptr<T>(result) ;
}

template< typename T, typename A >
std::auto_ptr<T>
auto_ptr_vector<T, A>::
release_back()
{
    T* result = m.back() ;
    m.pop_back() ;
    return std::auto_ptr<T>(result) ;
}

template< typename T, typename A >
void
auto_ptr_vector<T, A>::
push_back( std::auto_ptr<T> a )
{
    m.push_back(a.get()) ;
    a.release() ;
}

template< typename T, typename A >
void
auto_ptr_vector<T, A>::
clear()
{
    while( m.size() != 0 )
    {
        auto_ptr_vector::release_back() ;
    }
}

}} // namespace esve::util

#endif

