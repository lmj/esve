
#ifndef esve_message_impl_Draw_Sender_hxx
#define esve_message_impl_Draw_Sender_hxx

#include <esve/message/Draw_Sender.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Draw_Sender esve/message/impl/Draw_Sender.hxx
/// @brief Implements message::Draw_Sender.
///

class Draw_Sender
    : virtual public message::Draw_Sender
{
public:
    void add( message::Draw_Receiver & ) ;
    void remove( message::Draw_Receiver & ) ;
    void remove_all() ;

    ~Draw_Sender() ;

protected:
    Draw_Sender() ;

    void send_draw() ;
    void send_draw_initialize() ;

private:
    Draw_Sender( const Draw_Sender & ) ;
    Draw_Sender & operator=( const Draw_Sender & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

