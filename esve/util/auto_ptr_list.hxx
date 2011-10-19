//
// A std::list which owns its pointer elements.
//
// A raw pointer is returned from accessors such as back() with the
// understanding that the user should not delete it.  Remove elements
// with release().
//
// Note the template parameter differs from std::list,
//
//      std::list<T*>   <----->   auto_ptr_list<T>
//

#ifndef esve_util_auto_ptr_list_hxx
#define esve_util_auto_ptr_list_hxx

#include <list>
#include <memory>
#include <algorithm>

namespace esve { namespace util {

template< typename T, typename A = std::allocator<T*> >
class auto_ptr_list
{
private:
    typedef std::list<T*, A> m_Base ;
    
    // disallowed
    typedef typename m_Base::pointer pointer ;
    typedef typename m_Base::iterator iterator ;
    typedef typename m_Base::reverse_iterator reverse_iterator ;
    typedef typename m_Base::reference reference ;

    // disallowed
    auto_ptr_list & operator=( const auto_ptr_list & ) ;
    auto_ptr_list( const auto_ptr_list & ) ;

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
    // auto_ptr_list-specific methods
    ///////////////////////////////////////////////////

    //
    // The only constructor.
    //
    explicit auto_ptr_list( const allocator_type & = allocator_type() ) ;

    //
    // Delete all elements (back to front).
    //
    ~auto_ptr_list() ;

    //
    // Hand off ownership to the list.
    //
    void push_front( std::auto_ptr<T> ) ;

    //
    // Hand off ownership to the list.
    //
    void push_back( std::auto_ptr<T> ) ;

    //
    // Release ownership of the first element and remove it from the
    // container.
    //
    std::auto_ptr<T> release_front() ;

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
    // selected std::list methods
    ///////////////////////////////////////////////////

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
auto_ptr_list<T, A>::
auto_ptr_list( const allocator_type & a )
    : m(a)
{
}

template< typename T, typename A >
auto_ptr_list<T, A>::
~auto_ptr_list()
{
    auto_ptr_list::clear() ;
}

template< typename T, typename A >
std::auto_ptr<T>
auto_ptr_list<T, A>::
release_front()
{
    T* result = m.front() ;
    m.pop_front() ;
    return std::auto_ptr<T>(result) ;
}

template< typename T, typename A >
std::auto_ptr<T>
auto_ptr_list<T, A>::
release_back()
{
    T* result = m.back() ;
    m.pop_back() ;
    return std::auto_ptr<T>(result) ;
}

template< typename T, typename A >
std::auto_ptr<T>
auto_ptr_list<T, A>::
release( const_iterator a )
{
    T* result = *a ;

    //
    // This sucks.  Since we've restricted access to non-const
    // iterators, we should be able to safely cast.  But how?
    //
    m.erase(std::find(m.begin(), m.end(), *a)) ;

    return std::auto_ptr<T>(result) ;
}

template< typename T, typename A >
void
auto_ptr_list<T, A>::
push_back( std::auto_ptr<T> a )
{
    m.push_back(a.get()) ;
    a.release() ;
}

template< typename T, typename A >
void
auto_ptr_list<T, A>::
push_front( std::auto_ptr<T> a )
{
    m.push_front(a.get()) ;
    a.release() ;
}

template< typename T, typename A >
void
auto_ptr_list<T, A>::
clear()
{
    while( m.size() != 0 )
    {
        auto_ptr_list::release_back() ;
    }
}

}} // namespace esve::util

#endif

