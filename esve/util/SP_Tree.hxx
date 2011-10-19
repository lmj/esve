//
//  single-parent tree.
//

#ifndef esve_util_SP_Tree_hxx
#define esve_util_SP_Tree_hxx

#include <list>
#include <algorithm>
#include <cstddef>
#include <cassert>

namespace esve { namespace util {

// unused general versions
template< typename Parent, typename Child >
class SP_Tree_Child ;
template< typename Parent, typename Child >
class SP_Tree_Parent ;

// partial specialization for pointers

template< typename Parent, typename Child >
class SP_Tree_Parent<Parent*, Child*>  ;

template< typename Parent, typename Child >
class SP_Tree_Child<Parent*, Child*>
{
private:
    friend class SP_Tree_Parent<Parent*, Child*> ;

    SP_Tree_Child( const SP_Tree_Child & ) ;
    SP_Tree_Child & operator=( const SP_Tree_Child & ) ;

    SP_Tree_Parent<Parent*, Child*>* m_parent ;
    Child* m_data ;

protected:
    SP_Tree_Child( Child* data ) ;

public:
    const Parent* parent() const
    {
        return m_parent ? m_parent->m_data : 0 ;
    }

    Parent* parent()
    {
        return m_parent ? m_parent->m_data : 0 ;
    }

    void remove_parent() ;

    virtual ~SP_Tree_Child() ;
} ;

template< typename Parent, typename Child >
class SP_Tree_Parent<Parent*, Child*>
{
private:
    template< typename T_Iterator, typename T_Child >
    class children_iterator_
    {
    private:
        T_Iterator mi ;

    public:
        typedef T_Child value_type ;
        typedef value_type & reference ;
        typedef value_type* pointer ;
        typedef std::ptrdiff_t difference_type ;
        typedef std::forward_iterator_tag iterator_category ;

        children_iterator_( T_Iterator i )
            : mi(i) { }

        // compiler writes memberwise copy and assign

        reference operator*()
        {
            return *m_child_data(*mi) ;
        }

        pointer operator->()
        {
            return m_child_data(*mi) ;
        }

        children_iterator_ & operator++()
        {
            ++mi ;
            return *this ;
        }

        children_iterator_ operator++( int )
        {
            children_iterator_ tmp = *this ;
            ++mi ;
            return tmp ;
        }

        bool operator==( children_iterator_ a ) const
        {
            return a.mi == mi ;
        }

        bool operator!=( children_iterator_ a ) const
        {
            return a.mi != mi ;
        }
    } ;

    typedef
    std::list< SP_Tree_Child<Parent*, Child*>* >
    m_Child_List ;

    friend class SP_Tree_Child<Parent*, Child*> ;

    SP_Tree_Parent( const SP_Tree_Parent & ) ;
    SP_Tree_Parent & operator=( const SP_Tree_Parent & ) ;

    static Child* m_child_data( SP_Tree_Child<Parent*, Child*>* p )
    {
        return p->m_data ;
    }

    m_Child_List m_children ;
    Parent* m_data ;

protected:
    SP_Tree_Parent( Parent* data ) ;

public:
    typedef
    children_iterator_< typename m_Child_List::iterator, Child >
    children_iterator ;

    typedef
    children_iterator_< typename m_Child_List::const_iterator, const Child >
    children_const_iterator ;

    typedef typename m_Child_List::size_type size_type ;

    size_type children_size() const
    {
        return m_children.size() ;
    }

    children_const_iterator children_begin() const
    {
        return children_const_iterator(m_children.begin()) ;
    }

    children_const_iterator children_end() const
    {
        return children_const_iterator(m_children.end()) ;
    }

    children_iterator children_begin()
    {
        return children_iterator(m_children.begin()) ;
    }

    children_iterator children_end()
    {
        return children_iterator(m_children.end()) ;
    }

    void add_child( SP_Tree_Child<Parent*, Child*>* ) ;

    // trying to remove a non-existent child is not an error
    void remove_child( SP_Tree_Child<Parent*, Child*>* ) ;

    void remove_children() ;

    virtual ~SP_Tree_Parent() ;
} ;

template< typename Parent, typename Child >
SP_Tree_Child<Parent*, Child*>::
SP_Tree_Child( Child* data )
    : m_parent(0),
      m_data(data)
{
}

template< typename Parent, typename Child >
SP_Tree_Child<Parent*, Child*>::
~SP_Tree_Child()
{
    remove_parent() ;
}

template< typename Parent, typename Child >
void
SP_Tree_Child<Parent*, Child*>::
remove_parent()
{
    if( m_parent )
    {
        assert(std::find(m_parent->m_children.begin(),
                         m_parent->m_children.end(),
                         this)
               !=
               m_parent->m_children.end()) ;

        m_parent->m_children.erase(
            std::find(m_parent->m_children.begin(),
                      m_parent->m_children.end(),
                      this)) ;

        m_parent = 0 ;
    }
}

template< typename Parent, typename Child >
SP_Tree_Parent<Parent*, Child*>::
SP_Tree_Parent( Parent* data )
    : m_children(),
      m_data(data)
{
}

template< typename Parent, typename Child >
SP_Tree_Parent<Parent*, Child*>::
~SP_Tree_Parent()
{
    remove_children() ;
}

template< typename Parent, typename Child >
void
SP_Tree_Parent<Parent*, Child*>::
add_child( SP_Tree_Child<Parent*, Child*>* child )
{
    if( child )
    {
        if( child->m_parent )
        {
            child->remove_parent() ;
        }
        m_children.push_back(child) ;
        child->m_parent = this ;
    }
}

template< typename Parent, typename Child >
void
SP_Tree_Parent<Parent*, Child*>::
remove_child( SP_Tree_Child<Parent*, Child*>* child )
{
    if( child )
    {
        typename m_Child_List::iterator pos =
            std::find(m_children.begin(),
                      m_children.end(),
                      child) ;

        // trying to remove a non-existent child is not an error
        if( pos != m_children.end() )
        {
            (*pos)->m_parent = 0 ;
            m_children.erase(pos) ;
        }
    }
}

template< typename Parent, typename Child >
void
SP_Tree_Parent<Parent*, Child*>::
remove_children()
{
    for( typename m_Child_List::iterator i = m_children.begin() ;
         i != m_children.end() ;
         ++i )
    {
        (*i)->m_parent = 0 ;
    }

    m_children.clear() ;
}

}} // namespace esve::util

#endif


