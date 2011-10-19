
#ifndef esve_tree_tick_hxx
#define esve_tree_tick_hxx

#include <esve/tree/generator.hxx>

namespace esve { namespace tree { namespace tick {

///////////////////////////////////////////////////////////
class Message
{
public:
    virtual ~Message()
    {
    }

protected:
    Message()
    {
    }

private:
    friend class Handler ;
    virtual void relay_hook( Handler & handler ) = 0 ;
} ;

///////////////////////////////////////////////////////////
class Handler
    :
    public generator::Handler<Message>
{
private:
    virtual void handle_hook( Message & message )
    {
        message.relay_hook(*this) ;
    }

    friend class Message_Default ;

protected:
    virtual void handle_hook( Message_Default & ) = 0 ;
} ;

///////////////////////////////////////////////////////////
class Emitter
    :
    public generator::Emitter<Message>
{
} ;

///////////////////////////////////////////////////////////
class Node
    :
    public generator::Node<Message>
{
} ;

///////////////////////////////////////////////////////////
class Message_Default
    :
    public Message
{
private:
    void relay_hook( Handler & handler )
    {
        handler.handle_hook(*this) ;
    }
} ;

}}} // namespace esve::tree::tick

#endif

