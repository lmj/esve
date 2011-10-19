
#ifndef esve_tree_event_hxx
#define esve_tree_event_hxx

#include <esve/tree/generator.hxx>

namespace esve { namespace tree { namespace event {

///////////////////////////////////////////////////////////
class Message
{
public:
    virtual ~Message() = 0 ;

protected:
    Message()
    {
    }
} ;

inline
Message::
~Message()
{
}

///////////////////////////////////////////////////////////
class Handler
    :
    public generator::Handler<Message, bool>
{
} ;

///////////////////////////////////////////////////////////
class Emitter
    :
    public generator::Emitter<Message, bool>
{
} ;

///////////////////////////////////////////////////////////
class Node
    :
    public generator::Node<Message, bool>
{
} ;

}}} // namespace esve::tree::event

#endif

