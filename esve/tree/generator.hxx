
#ifndef esve_tree_generator_hxx
#define esve_tree_generator_hxx

#include <esve/tree/generic.hxx>
#include <cassert>

#if !defined(NDEBUG)
#include <iostream>
#endif

namespace esve { namespace tree { namespace generator {

template< typename Message, typename return_type = void >
class Handler ;

///////////////////////////////////////////////////////////
template< typename Message >
class Handler<Message, bool>
    :
    private generic::Handler
{
public:
    Handler()
        :
        generic::Handler()
    {
    }
    
protected:
    bool handle( Message & message )
    {
        return handle_hook(message) ;
    }

    virtual bool handle_hook( Message & ) = 0 ;

private:
    bool handle_hook( void* message )
    {
        return handle(*static_cast<Message*>(message)) ;
    }
} ;

///////////////////////////////////////////////////////////
template< typename Message >
class Handler<Message, void>
    :
    private generic::Handler
{
public:
    Handler()
        :
        generic::Handler()
    {
    }
    
protected:
    void handle( Message & message )
    {
        return handle_hook(message) ;
    }

    virtual void handle_hook( Message & ) = 0 ;

private:
    bool handle_hook( void* message )
    {
        handle(*static_cast<Message*>(message)) ;
        return true ;
    }
} ;

///////////////////////////////////////////////////////////
template< typename Message, typename return_type = void >
class Emitter
    :
    private generic::Emitter
{
public:
    Emitter()
        :
        generic::Emitter()
    {
    }

    return_type emit( Message & message )
    {
#if !defined(NDEBUG)
        std::cerr << "____________________________________\n" ;
        std::cerr << "emitting message:\n" ;
        std::cerr << "    emitter: " << typeid(*this).name() << " "
                  << dynamic_cast<void*>(this) << "\n" ;
        std::cerr << "    message: " << typeid(message).name() << " "
                  << static_cast<void*>(&message) << "\n" ;
        std::cerr << "____________________________________\n" ;
#endif
        assert("polymorphic non-virtual base required"
               &&
               dynamic_cast<void*>(&message)
               ==
               static_cast<void*>(&message)) ;

        return return_type(generic::Emitter::emit(&message)) ;
    }

    void add_child( Handler<Message, return_type> & handler )
    {
        add_child_hook(handler) ;
    }

    void remove_child( Handler<Message, return_type> & handler )
    {
        remove_child_hook(handler) ;
    }

    void remove_children()
    {
        remove_children_hook() ;
    }

protected:
    virtual void add_child_hook( Handler<Message, return_type> & handler )
    {
        generic::Emitter::add_child(
            *reinterpret_cast<generic::Handler*>(&handler)) ;
    }

    virtual
    void
    remove_child_hook( Handler<Message, return_type> & handler )
    {
        generic::Emitter::remove_child(
            *reinterpret_cast<generic::Handler*>(&handler)) ;
    }

    virtual void remove_children_hook()
    {
        generic::Emitter::remove_children() ;
    }
} ;
    
///////////////////////////////////////////////////////////
template< typename Message, typename return_type = void >
class Node
    :
    public Handler<Message, return_type>,
    public Emitter<Message, return_type>
{
public:
    Node()
        :
        Handler<Message, return_type>()
    {
    }

protected:
    return_type handle_hook( Message & message )
    {
        // pass to children
        return emit(message) ;
    }
} ;

}}} // namespace esve::tree::generator

#endif



