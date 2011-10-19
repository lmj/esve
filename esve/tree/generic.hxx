
#ifndef esve_tree_generic_hxx
#define esve_tree_generic_hxx

#include <esve/util/Noncopyable.hxx>
#include <memory>

namespace esve { namespace tree { namespace generic {

///////////////////////////////////////////////////////////
class Handler
    :
    private Noncopyable
{
protected:
    Handler() ;

    void remove_parents() ;

    bool handle( void* message )
    {
        return handle_hook(message) ;
    }
    
    virtual bool handle_hook( void* ) = 0 ;

    virtual ~Handler() ;

private:
    friend class Emitter ;
    struct Private ;
    const std::auto_ptr<Private> m ;
} ;

///////////////////////////////////////////////////////////
class Emitter
    :
    private Noncopyable
{
protected:
    Emitter() ;

    void add_child( Handler & ) ;
    void remove_child( Handler & ) ;
    void remove_children() ;

    bool emit( void* message ) ;
    
    virtual ~Emitter() ;

private:
    friend class Handler ;
    struct Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::tree::generic

#endif

