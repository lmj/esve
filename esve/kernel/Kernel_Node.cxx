
#include <esve/kernel/Kernel_Node.hxx>
#include <esve/message/impl/Handle_Node.hxx>

namespace esve { namespace kernel {

struct Kernel_Node::Private
    : public message::impl::Handle_Node
{
    Kernel_Node & outside ;

    Private( Kernel_Node & outside_ )
        : outside(outside_) { }

    bool send_handle( const message::Handle_Args & args )
    {
        bool handled = false ;
        
        if( outside.active() )
        {
            handled = outside.dispatch_encoded(args) ;
        }

        return handled ;
    }

    bool base_send_handle( const message::Handle_Args & args )
    {
        return Handle_Node::send_handle(args) ;
    }
} ;

Kernel_Node::
Kernel_Node()
    : m(new Private(*this))
{
    add_decoder(*m) ;
    add_encoder(*m) ;
}

Kernel_Node::
~Kernel_Node()
{
}

bool
Kernel_Node::
dispatch_encoded( const message::Handle_Args & args )
{
    return m->base_send_handle(args) ;
}

}} // namespace esve::kernel
