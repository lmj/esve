
#ifndef esve_tree_update_hxx
#define esve_tree_update_hxx

#include <esve/tree/generator.hxx>

namespace esve { namespace tree { namespace update {

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

    friend class Message_Timed ;
    friend class Message_Async ;

protected:
    virtual void handle_hook( Message_Async & ) = 0 ;
    virtual void handle_hook( Message_Timed & ) = 0 ;
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
class Message_Async
    :
    public Message
{
private:
    void relay_hook( Handler & handler )
    {
        handler.handle_hook(*this) ;
    }
} ;

///////////////////////////////////////////////////////////
class Message_Timed
    :
    public Message
{
public:
    Message_Timed( double dt )
        :
        Message(),
        m_dt(dt)
    {
    }

    double dt() const
    {
        return m_dt ;
    }

private:
    void relay_hook( Handler & handler )
    {
        handler.handle_hook(*this) ;
    }

    double m_dt ;
} ;

}}} // namespace esve::tree::update

#endif

