//
// Handle custom user-interface messages.
//

#ifndef apps_polynomialviewer_UI_Handler_hxx
#define apps_polynomialviewer_UI_Handler_hxx

#include "UI_Emitter.hxx"
#include <esve/kernel/Handler.hxx>
#include <memory>

class UI_Handler
    : virtual public esve::kernel::Handler
{
public:
    typedef UI_Emitter::Widget Widget ;
    
    UI_Handler() ;
    ~UI_Handler() ;

protected:
    virtual bool handle_widget( Widget ) = 0 ;

private:
    UI_Handler( const UI_Handler & ) ;
    UI_Handler & operator=( const UI_Handler & ) ;

    class Private ;
    const std::auto_ptr<Private> m ;
} ;

#endif

