//
// Iterate over a given data member in iterator::value_type.
//

#ifndef esve_util_member_iterator_hxx
#define esve_util_member_iterator_hxx

#include <iterator>

namespace esve { namespace util {

template< typename Forward_Iterator,
          typename T_Data,
          T_Data std::iterator_traits<Forward_Iterator>::value_type::* member >
class member_iterator
{
private:
    Forward_Iterator m ;

public:
    typedef T_Data value_type ;
    typedef value_type & reference ;
    typedef value_type* pointer ;
    typedef std::forward_iterator_tag iterator_category ;

    typedef
    typename std::iterator_traits<Forward_Iterator>::difference_type
    difference_type ;

    member_iterator( Forward_Iterator vi )
        : m(vi) { }

    // compiler writes memberwise copy and assign

    reference operator*()
    {
        return (*m).*member ;
    }

    pointer operator->()
    {
        return &((*m).*member) ;
    }

    member_iterator & operator++()
    {
        ++m ;
        return *this ;
    }

    member_iterator operator++( int )
    {
        member_iterator tmp = *this ;
        ++m ;
        return tmp ;
    }

    bool operator!=( member_iterator a ) const
    {
        return m != a.m ;
    }

    bool operator==( member_iterator a ) const
    {
        return m == a.m ;
    }
} ;

}} // namespace esve::util

#endif
