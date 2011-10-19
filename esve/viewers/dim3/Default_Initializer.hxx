
#ifndef esve_viewers_dim3_Default_Initializer_hxx
#define esve_viewers_dim3_Default_Initializer_hxx

#include <esve/message/impl/Draw_Receiver.hxx>

namespace esve { namespace viewers { namespace dim3 {

class Default_Initializer
    : virtual public message::impl::Draw_Receiver
{
public:
    Default_Initializer() ;

    ~Default_Initializer() ;

protected:
    void draw() ;
    void draw_initialize() ;

private:
    Default_Initializer( const Default_Initializer & ) ;
    Default_Initializer & operator=( const Default_Initializer & ) ;
} ;

}}} // namespace esve::viewers::dim3

#endif

