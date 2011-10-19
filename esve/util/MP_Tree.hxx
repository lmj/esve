//
//  multi-parent tree.
//

#ifndef esve_util_MP_Tree_hxx
#define esve_util_MP_Tree_hxx

#include <list>
#include <algorithm>
#include <cstddef>
#include <cassert>

namespace esve { namespace util {

// unused general versions
template< typename Parent, typename Child >
class MP_Tree_Child ;
template< typename Parent, typename Child >
class MP_Tree_Parent ;

// partial specialization for pointers

template< typename Parent, typename Child >
class MP_Tree_Parent<Parent*, Child*>  ;

template< typename Parent, typename Child >
class MP_Tree_Child<Parent*, Child*>
{
private:
    template< typename T_Iterator, typename T_Parent >
    class parents_iterator_
    {
    private:
        T_Iterator mi ;

    public:
        typedef T_Parent value_type ;
        typedef value_type & reference ;
        typedef value_type* pointer ;
        typedef std::ptrdiff_t difference_type ;
        typedef std::forward_iterator_tag iterator_category ;

        parents_iterator_( T_Iterator i )
            : mi(i) { }

        // compiler writes memberwise copy and assign

        reference operator*()
        {
            return *m_parent_data(*mi) ;
        }

        pointer operator->()
        {
            return m_parent_data(*mi) ;
        }

        parents_iterator_ & operator++()
        {
            ++mi ;
            return *this ;
        }

        parents_iterator_ operator++( int )
        {
            parents_iterator_ tmp = *this ;
            ++mi ;
            return tmp ;
        }

        bool operator==( parents_iterator_ a ) const
        {
            return a.mi == mi ;
        }

        bool operator!=( parents_iterator_ a ) const
        {
            return a.mi != mi ;
        }
    } ;

    typedef
    std::list< MP_Tree_Parent<Parent*, Child*>* >
    m_Parent_List ;

    friend class MP_Tree_Parent<Parent*, Child*> ;

    MP_Tree_Child( const MP_Tree_Child & ) ;
    MP_Tree_Child & operator=( const MP_Tree_Child & ) ;

    static Parent* m_parent_data( MP_Tree_Parent<Parent*, Child*>* p )
    {
        return p->m_data ;
    }

    m_Parent_List m_parents ;
    Child* m_data ;

protected:
    MP_Tree_Child( Child* data ) ;

public:
    typedef
    parents_iterator_< typename m_Parent_List::iterator, Parent >
    parents_iterator ;

    typedef
    parents_iterator_< typename m_Parent_List::const_iterator, const Parent >
    parents_const_iterator ;

    typedef typename m_Parent_List::size_type size_type ;

    size_type parents_size() const
    {
        return m_parents.size() ;
    }

    parents_const_iterator parents_begin() const
    {
        return parents_const_iterator(m_parents.begin()) ;
    }

    parents_const_iterator parents_end() const
    {
        return parents_const_iterator(m_parents.end()) ;
    }

    parents_iterator parents_begin()
    {
        return parents_iterator(m_parents.begin()) ;
    }

    parents_iterator parents_end()
    {
        return parents_iterator(m_parents.end()) ;
    }

    void remove_parents() ;

    virtual ~MP_Tree_Child() ;
} ;

template< typename Parent, typename Child >
class MP_Tree_Parent<Parent*, Child*>
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
    std::list< MP_Tree_Child<Parent*, Child*>* >
    m_Child_List ;

    friend class MP_Tree_Child<Parent*, Child*> ;

    MP_Tree_Parent( const MP_Tree_Parent & ) ;
    MP_Tree_Parent & operator=( const MP_Tree_Parent & ) ;

    static Child* m_child_data( MP_Tree_Child<Parent*, Child*>* p )
    {
        return p->m_data ;
    }

    m_Child_List m_children ;
    Parent* m_data ;

protected:
    MP_Tree_Parent( Parent* data ) ;

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

    void add_child( MP_Tree_Child<Parent*, Child*>* ) ;

    // trying to remove a non-existent child is not an error
    void remove_child( MP_Tree_Child<Parent*, Child*>* ) ;

    void remove_children() ;

    virtual ~MP_Tree_Parent() ;
} ;

template< typename Parent, typename Child >
MP_Tree_Child<Parent*, Child*>::
MP_Tree_Child( Child* data )
    : m_parents(),
      m_data(data)
{
}

template< typename Parent, typename Child >
MP_Tree_Child<Parent*, Child*>::
~MP_Tree_Child()
{
    remove_parents() ;
}

template< typename Parent, typename Child >
void
MP_Tree_Child<Parent*, Child*>::
remove_parents()
{

    for( typename m_Parent_List::iterator i = m_parents.begin() ;
         i != m_parents.end() ;
         ++i )
    {
        assert(std::find((*i)->m_children.begin(),
                         (*i)->m_children.end(),
                         this)
               !=
               (*i)->m_children.end()) ;

        (*i)->m_children.erase(std::find((*i)->m_children.begin(),
                                         (*i)->m_children.end(),
                                         this)) ;
    }

    m_parents.clear() ;
}

template< typename Parent, typename Child >
MP_Tree_Parent<Parent*, Child*>::
MP_Tree_Parent( Parent* data )
    :  m_children(),
       m_data(data)
{
}

template< typename Parent, typename Child >
MP_Tree_Parent<Parent*, Child*>::
~MP_Tree_Parent()
{
    remove_children() ;
}

template< typename Parent, typename Child >
void
MP_Tree_Parent<Parent*, Child*>::
add_child( MP_Tree_Child<Parent*, Child*>* child )
{
    m_children.push_back(child) ;
    child->m_parents.push_back(this) ;
}

template< typename Parent, typename Child >
void
MP_Tree_Parent<Parent*, Child*>::
remove_child( MP_Tree_Child<Parent*, Child*>* child )
{
    typename m_Child_List::iterator child_pos =
        std::find(m_children.begin(),
                  m_children.end(),
                  child) ;

    // trying to remove a non-existent child is not an error
    if( child_pos != m_children.end() )
    {
        assert(std::find((*child_pos)->m_parents.begin(),
                         (*child_pos)->m_parents.end(),
                         this)
               !=
               (*child_pos)->m_parents.end()) ;

        (*child_pos)->m_parents.erase(
            std::find((*child_pos)->m_parents.begin(),
                      (*child_pos)->m_parents.end(),
                      this)) ;

        m_children.erase(child_pos) ;
    }
}

template< typename Parent, typename Child >
void
MP_Tree_Parent<Parent*, Child*>::
remove_children()
{
    for( typename m_Child_List::iterator i = m_children.begin() ;
         i != m_children.end() ;
         ++i )
    {
        assert(std::find((*i)->m_parents.begin(),
                         (*i)->m_parents.end(),
                         this)
               !=
               (*i)->m_parents.end()) ;
               
        (*i)->m_parents.erase(
            std::find(
                (*i)->m_parents.begin(),
                (*i)->m_parents.end(),
                this)) ;
    }

    m_children.clear() ;
}

}} // namespace esve::util

#endif


