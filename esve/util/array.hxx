//
// A fixed-capacity replacement for std::vector.
//
// There are no capacity checks save for one inside reserve().
//
// NOTE: If value_type is not a built-in type then the default
// alignment is along 'int' boundaries, which suffices for most cases.
// You may specialize array_types::alignment<> to provide a different
// alignment for a given type.
//

#ifndef esve_util_array_hxx
#define esve_util_array_hxx

#include <new>
#include <cstddef>
#include <iterator>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <memory>

namespace esve { namespace util {

/////////////////////////////////////////////////////////////////
//
// array_types::alignment<>
//
/////////////////////////////////////////////////////////////////

namespace array_types {

template< typename T >
struct alignment
{
    typedef int type ;
} ;

} // namespace array_types

namespace array_private {

/////////////////////////////////////////////////////////////////
//
// traits
//
// Defaults are decided by numeric_limits.
//
/////////////////////////////////////////////////////////////////

struct true_type { } ;
struct false_type { } ;

template< bool >
struct select_bool ;

template<>
struct select_bool<true>
{
    typedef true_type type ;
} ;

template<>
struct select_bool<false>
{
    typedef false_type type ;
} ;

template< typename T >
struct traits
{
    typedef typename
    select_bool<std::numeric_limits<T>::is_specialized>::type
    is_pod ;

    typedef typename
    select_bool<std::numeric_limits<T>::is_integer>::type
    is_integer ;
} ;

/////////////////////////////////////////////////////////////////
//
// POD/non-POD compile-time dispatch
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// POD
/////////////////////////////////////////////////////////////////

template< typename T >
inline void construct_copy( T* p, const T & x, true_type )
{
    *p = x ;
}

template< typename T >
inline void destruct( T* , true_type )
{
}

template< typename T >
inline void destruct( T* , T* , true_type )
{
}

template< typename T >
inline bool compare( const T* a_begin, const T* a_end,
                     const T* b_begin, const T* b_end,
                     true_type )
{
    return
        a_end - a_begin == b_end - b_begin
        &&
        std::memcmp(a_begin,
                    b_begin,
                    a_end - a_begin) == 0 ;
}

/////////////////////////////////////////////////////////////////
// non-POD
/////////////////////////////////////////////////////////////////

template< typename T >
inline void construct_copy( T* p, const T & x, false_type )
{
    new(p) T(x) ;
}

template< typename T >
inline void destruct( T* p, false_type )
{
    (*p).~T() ;
}

template< typename T >
inline void destruct( T* first, T* last, false_type )
{
    for( ; first != last ; ++first )
    {
        (*first).~T() ;
    }
}

template< typename T >
inline bool compare( const T* a_begin, const T* a_end,
                     const T* b_begin, const T* b_end,
                     false_type )
{
    return
        a_end - a_begin == b_end - b_begin
        &&
        std::equal(a_begin,
                   a_end,
                   b_begin) ;
}

/////////////////////////////////////////////////////////////////
// data
/////////////////////////////////////////////////////////////////

template< typename T, std::size_t N, typename is_pod >
struct data ;

template< typename T, std::size_t N >
struct data<T, N, true_type>
{
    T begin[N] ;
} ;

template< typename T, std::size_t N >
struct data<T, N, false_type>
{
    typename array_types::alignment<T>::type
    begin[N*(sizeof(T) % sizeof(typename array_types::alignment<T>::type) == 0
             ?
             sizeof(T)/sizeof(typename array_types::alignment<T>::type)
             :
             sizeof(T)/sizeof(typename array_types::alignment<T>::type) + 1)] ;
} ;

} // namespace array_private

/////////////////////////////////////////////////////////////////
//
// array
//
/////////////////////////////////////////////////////////////////

template< typename T, std::size_t N >
class array
{
private:
    typedef T m_value_type ;
    typedef std::size_t m_size_type ;
    typedef std::ptrdiff_t m_difference_type ;
    typedef T* m_iterator ;
    typedef const T* m_const_iterator ;
    typedef std::reverse_iterator<m_iterator> m_reverse_iterator ;
    typedef std::reverse_iterator<m_const_iterator> m_const_reverse_iterator ;
    typedef T & m_reference ;
    typedef const T & m_const_reference ;
    typedef typename array_private::traits<T>::is_pod m_is_pod ;

    /////////////////////////////////////
    // data
    /////////////////////////////////////

    array_private::data<T, N, m_is_pod> m_data ;
    T* m_end ;

    /////////////////////////////////////
    // construct fill/range dispatch
    /////////////////////////////////////

    void m_construct_fill( m_size_type n, m_const_reference x )
    {
        std::uninitialized_fill(array::begin(), array::begin() + n, x) ;
        m_end = array::begin() + n ;
    }

    template< typename Input_Iterator >
    void m_construct_range( Input_Iterator first, Input_Iterator last ) ;

    template< typename T_Integer >
    void m_construct2( T_Integer n, T_Integer x,
                       array_private::true_type )
    {
        m_construct_fill(n, x) ;
    }

    template< typename Input_Iterator >
    void m_construct2( Input_Iterator first, Input_Iterator last,
                       array_private::false_type )
    {
        m_construct_range(first, last) ;
    }

    /////////////////////////////////////
    // insert fill/range dispatch
    /////////////////////////////////////

    void m_insert_fill( m_iterator p, m_size_type n, m_const_reference x ) ;

    template< typename Input_Iterator >
    void m_insert_range( m_iterator p,
                         Input_Iterator first,
                         Input_Iterator last ) ;

    template< typename T_Integer >
    void m_insert3( m_iterator p,
                    T_Integer n,
                    T_Integer x,
                    array_private::true_type )
    {
        m_insert_fill(p, n, x) ;
    }

    template< typename Input_Iterator >
    void m_insert3( m_iterator p,
                    Input_Iterator first,
                    Input_Iterator last,
                    array_private::false_type )
    {
        m_insert_range(p, first, last) ;
    }

    /////////////////////////////////////
    // assign fill/range dispatch
    /////////////////////////////////////

    void m_assign_fill( m_size_type n, m_const_reference x ) ;

    template< typename Input_Iterator >
    void m_assign_range( Input_Iterator first, Input_Iterator last ) ;

    template< typename T_Integer >
    void m_assign2( T_Integer n, T_Integer x,
                    array_private::true_type )
    {
        m_assign_fill(n, x) ;
    }

    template< typename Input_Iterator >
    void m_assign2( Input_Iterator first, Input_Iterator last,
                    array_private::false_type )
    {
        m_assign_range(first, last) ;
    }

    /////////////////////////////////////
    // clear pod/non-pod dispatch
    /////////////////////////////////////

    void m_clear( array_private::true_type )
    {
        m_end = array::begin() ;
    }

    void m_clear( array_private::false_type )
    {
        erase(array::begin(), array::end()) ;
    }

public:
    /////////////////////////////////////
    // member types
    /////////////////////////////////////

    typedef m_value_type value_type ;
    typedef m_size_type size_type ;
    typedef m_difference_type difference_type ;
    typedef m_iterator iterator ;
    typedef m_const_iterator const_iterator ;
    typedef m_reverse_iterator reverse_iterator ;
    typedef m_const_reverse_iterator const_reverse_iterator ;
    typedef m_reference reference ;
    typedef m_const_reference const_reference ;

    /////////////////////////////////////
    // iterators
    /////////////////////////////////////

    const_iterator begin() const
    {
        return reinterpret_cast<const T*>(m_data.begin) ;
    }

    iterator begin()
    {
        return reinterpret_cast<T*>(m_data.begin) ;
    }

    const_iterator end() const
    {
        return m_end ;
    }

    iterator end()
    {
        return m_end ;
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(array::end()) ;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(array::end()) ;
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(array::begin()) ;
    }

    reverse_iterator rend()
    {
        return reverse_iterator(array::begin()) ;
    }

    /////////////////////////////////////
    // element access
    /////////////////////////////////////

    const_reference front() const
    {
        return *array::begin() ;
    }

    reference front()
    {
        return *array::begin() ;
    }

    const_reference back() const
    {
        return *(array::end() - 1) ;
    }

    reference back()
    {
        return *(array::end() - 1) ;
    }

    const_reference operator[]( size_type i ) const
    {
        return *(reinterpret_cast<const T*>(m_data.begin) + i) ;
    }

    reference operator[]( size_type i )
    {
        return *(reinterpret_cast<T*>(m_data.begin) + i) ;
    }

    const_reference at( size_type i ) const
    {
        if( i >= array::size() ) throw std::out_of_range("array::at") ;
        return (*this)[i] ;
    }

    reference at( size_type i )
    {
        if( i >= array::size() ) throw std::out_of_range("array::at") ;
        return (*this)[i] ;
    }

    /////////////////////////////////////
    // stack operations
    /////////////////////////////////////

    void push_back( m_const_reference a )
    {
        array_private::construct_copy(array::end(), a, m_is_pod()) ; ++m_end ;
    }

    void pop_back()
    {
        array_private::destruct(array::end() - 1, m_is_pod()) ; --m_end ;
    }

    /////////////////////////////////////
    // list operations
    /////////////////////////////////////

    iterator insert( iterator p, const_reference x ) ;

    void insert( iterator p, size_type n, const_reference x )
    {
        m_insert_fill(p, n, x) ;
    }

    template< typename Q >
    void insert( iterator p, Q a, Q b )
    {
        typedef
            typename array_private::traits<Q>::is_integer
            is_integer ;
        m_insert3(p, a, b, is_integer()) ;
    }

    iterator erase( iterator p )
    {
        return erase(p, p + 1) ;
    }

    iterator erase( iterator first, iterator last ) ;

    void clear()
    {
        m_clear(m_is_pod()) ;
    }

    /////////////////////////////////////
    // other operations
    /////////////////////////////////////

    size_type size() const
    {
        return array::end() - array::begin() ;
    }

    bool empty() const
    {
        return array::end() == array::begin() ;
    }

    size_type max_size() const
    {
        return N ;
    }

    size_type capacity() const
    {
        return N ;
    }

    void reserve( size_type n )
    {
        if( n > N ) throw std::length_error("array::reserve") ;
    }

    void resize( size_type n )
    {
        resize(n, value_type()) ;
    }

    void resize( size_type n, const_reference x ) ;

    void swap( array & ) ;

    /////////////////////////////////////
    // constructors
    /////////////////////////////////////

    array()
        : m_end(array::begin()) { }

    explicit array( size_type n )
        : m_end(array::begin() + n)
    {
        std::uninitialized_fill(array::begin(), array::end(), value_type()) ;
    }

    array( size_type n, const_reference x )
        : m_end(array::begin() + n)
    {
        std::uninitialized_fill(array::begin(), array::end(), x) ;
    }

    template< typename Q >
    array( Q a, Q b )
    {
        typedef
            typename array_private::traits<Q>::is_integer
            is_integer ;
        m_construct2(a, b, is_integer()) ;
    }

    array( const array & a )
        : m_end(array::begin() + a.size())
    {
        std::uninitialized_copy(a.begin(), a.end(), array::begin()) ;
    }

    /////////////////////////////////////
    // assignments
    /////////////////////////////////////

    array & operator=( const array & ) ;

    void assign( size_type n, const_reference x )
    {
        m_assign_fill(n, x) ;
    }

    template< typename Q >
    void assign( Q a, Q b )
    {
        typedef
            typename array_private::traits<Q>::is_integer
            is_integer ;
        m_assign2(a, b, is_integer()) ;
    }

    /////////////////////////////////////
    // destructor
    /////////////////////////////////////

    ~array()
    {
        array_private::destruct(array::begin(), array::end(), m_is_pod()) ;
    }
} ;

template< typename T, std::size_t N >
inline bool operator==( const array<T, N> & a,
                        const array<T, N> & b )
{
    typedef typename array_private::traits<T>::is_pod is_pod ;
    return array_private::compare(a.begin(), a.end(),
                                  b.begin(), b.end(),
                                  is_pod()) ;
}

template< typename T, std::size_t N >
inline bool operator<( const array<T, N> & a,
                       const array<T, N> & b )
{
    return std::lexicographical_compare(a.begin(), a.end(),
                                        b.begin(), b.end()) ;
}

template< typename T, std::size_t N >
template< typename Input_Iterator >
void
array<T, N>::
m_construct_range( Input_Iterator first, Input_Iterator last )
{
    iterator i = array::begin() ;
    for( ; first != last ; ++i, ++first )
    {
        array_private::construct_copy(i, *first, m_is_pod()) ;
    }

    m_end = i ;
}

template< typename T, std::size_t N >
template< typename Input_Iterator >
void
array<T, N>::
m_assign_range( Input_Iterator first, Input_Iterator last )
{
    iterator p = array::begin() ;

    for( ; p != array::end() && first != last ; ++p, ++first )
    {
        *p = *first ;
    }

    if( p == array::end() )
    {
        for( ; first != last ; ++p, ++first )
        {
            array_private::construct_copy(p,
                                          *first,
                                          m_is_pod()) ;
        }
    }
    else // p != array::end()
    {
        array_private::destruct(p,
                                array::end(),
                                m_is_pod()) ;
    }

    m_end = p ;
}

template< typename T, std::size_t N >
void
array<T, N>::
m_assign_fill( size_type n, const_reference x )
{
    if( array::size() <= n )
    {
        std::fill(array::begin(),
                  array::end(),
                  x) ;

        std::uninitialized_fill(array::end(),
                                array::begin() + n,
                                x) ;
    }
    else // array::size() > n
    {
        std::fill(array::begin(),
                  array::begin() + n,
                  x) ;

        array_private::destruct(array::begin() + n,
                                array::end(),
                                m_is_pod()) ;
    }

    m_end = array::begin() + n ;
}

template< typename T, std::size_t N >
array<T, N> &
array<T, N>::
operator=( const array & a )
{
    if( array::size() <= a.size() )
    {
        std::copy(a.begin(),
                  a.begin() + array::size(),
                  array::begin()) ;

        std::uninitialized_copy(a.begin() + array::size(),
                                a.end(),
                                array::end()) ;
    }
    else // array::size() > a.size()
    {
        std::copy(a.begin(),
                  a.end(),
                  array::begin()) ;

        array_private::destruct(array::begin() + a.size(),
                                array::end(),
                                m_is_pod()) ;
    }

    m_end = array::begin() + a.size() ;
    return *this ;
}

template< typename T, std::size_t N >
void
array<T, N>::
resize( size_type n, const_reference x )
{
    if( array::size() <= n )
    {
        std::uninitialized_fill(array::end(),
                                array::begin() + n,
                                x) ;
    }
    else // array::size() > n
    {
        array_private::destruct(array::begin() + n,
                                array::end(),
                                m_is_pod()) ;
    }

    m_end = array::begin() + n ;
}

template< typename T, std::size_t N >
typename array<T, N>::iterator
array<T, N>::
erase( iterator first, iterator last )
{
    std::copy(last,
              array::end(),
              first) ;

    array_private::destruct(array::end() - (last - first),
                            array::end(),
                            m_is_pod()) ;

    m_end -= last - first ;

    return first ;
}

template< typename T, std::size_t N >
void
array<T, N>::
swap( array & other )
{
    array tmp = other ;
    other = *this ;
    *this = tmp ;
}

template< typename T, std::size_t N >
void
array<T, N>::
m_insert_fill( iterator p, size_type n, const_reference x )
{
    if( p + n <= array::end() )
    {
        std::uninitialized_copy(array::end() - n,
                                array::end(),
                                array::end()) ;

        std::copy(p,
                  array::end() - n,
                  p + n) ;

        std::fill(p,
                  p + n,
                  x) ;
    }
    else // p + n > array::end()
    {
        std::uninitialized_copy(p,
                                array::end(),
                                p + n) ;

        std::fill(p,
                  array::end(),
                  x) ;

        std::uninitialized_fill(array::end(),
                                p + n,
                                x) ;
    }

    m_end += n ;
}

template< typename T, std::size_t N >
template< typename Input_Iterator >
void
array<T, N>::
m_insert_range( iterator p, Input_Iterator first, Input_Iterator last )
{
    const typename std::iterator_traits<Input_Iterator>::difference_type
        n = std::distance(first, last) ;

    if( p + n <= array::end() )
    {
        std::uninitialized_copy(array::end() - n,
                                array::end(),
                                array::end()) ;

        std::copy(p,
                  array::end() - n,
                  p + n) ;

        std::copy(first,
                  last,
                  p) ;
    }
    else // p + n > array::end()
    {
        std::uninitialized_copy(p,
                                array::end(),
                                p + n) ;

        for( ; p != array::end() ; ++p, ++first )
        {
            *p = *first ;
        }

        std::uninitialized_copy(first,
                                last,
                                array::end()) ;
    }

    m_end += n ;
}

template< typename T, std::size_t N >
typename array<T, N>::iterator
array<T, N>::
insert( iterator p, const_reference x )
{
    if( array::begin() == array::end() )
    {
        array_private::construct_copy(array::end(),
                                      x,
                                      m_is_pod()) ;
    }
    else // array::size() != 0
    {
        array_private::construct_copy(array::end(),
                                      *(array::end() - 1),
                                      m_is_pod()) ;

        std::copy(p,
                  array::end() - 1,
                  p + 1) ;

        *p = x ;
    }

    m_end += 1 ;

    return p ;
}

}} // namespace esve::util

#endif
