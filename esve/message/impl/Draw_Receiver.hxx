
#ifndef esve_message_impl_Draw_Receiver_hxx
#define esve_message_impl_Draw_Receiver_hxx

#include <esve/message/Draw_Receiver.hxx>
#include <memory>

namespace esve { namespace message { namespace impl {

///
/// @class Draw_Receiver esve/message/impl/Draw_Receiver.hxx
/// @brief Implements Draw_Receiver.
///

class Draw_Receiver
    : virtual public message::Draw_Receiver
{
public:
    Draw_Receiver() ;

    impl::Draw_Receiver & draw_receiver() ;

protected:
    ~Draw_Receiver() ;

private:
    Draw_Receiver( const Draw_Receiver & ) ;
    Draw_Receiver & operator=( const Draw_Receiver & ) ;

    // Coupled implementation with Draw_Sender (mutual linking).
    friend class Draw_Sender ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

}}} // namespace esve::message::impl

#endif

