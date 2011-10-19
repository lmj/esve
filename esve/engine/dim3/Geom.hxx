
#ifndef esve_engine_dim3_Geom_hxx
#define esve_engine_dim3_Geom_hxx

#include <esve/engine/dim3/impl/Frame.hxx>
#include <esve/message/impl/Draw_Receiver.hxx>
#include <esve/message/impl/Compute_Receiver.hxx>

namespace esve { namespace engine { namespace dim3 {

///
/// @class Geom esve/engine/dim3/Geom.hxx
/// @brief An abstract geometric object.
///
/// A Geom is a Frame which receives the draw() and compute()
/// messages.  You probably want to use Make_Geom instead of using
/// this class directly.
///
class Geom
    : virtual public message::impl::Draw_Receiver,
      virtual public message::impl::Compute_Receiver,
      public impl::Frame
{
public:
    ~Geom() ;

protected:
    Geom() ;

private:
    Geom( const Geom & ) ;
    Geom & operator=( const Geom & ) ;
} ;

}}} // namespace esve::engine::dim3

#endif


