
#ifndef esve_message_Handle_Args_hxx
#define esve_message_Handle_Args_hxx

#include <esve/message/diagnostic.hxx>
#include <memory>

namespace esve { namespace message {

class Handle_Args
{
public:
    // for caching.
    virtual std::auto_ptr<Handle_Args> clone() const = 0 ;

#ifdef ESVE_DIAGNOSTIC
    virtual void diagnostic() const = 0 ;
#endif

    virtual ~Handle_Args() = 0 ;

protected:
    Handle_Args() ;

private:
    Handle_Args( const Handle_Args & ) ;
    Handle_Args & operator=( const Handle_Args & ) ;
} ;

}} // namespace esve::message

#endif
