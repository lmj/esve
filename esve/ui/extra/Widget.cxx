
#include <esve/ui/extra/Widget_Emitter.hxx>
#include <esve/ui/extra/Widget.hxx>
#include <esve/message/impl/Handle_Sender.hxx>
#include <algorithm>
#include <cassert>
#include <vector>

namespace esve { namespace ui { namespace extra {

Widget::
Widget()
{
}

Widget::
~Widget()
{
}

//////////////////////////////////////////////

struct Widget_Emitter::Private
    : public message::impl::Handle_Sender
{
    struct Sentry
    {
        const Widget & widget ;
        Widget_Emitter::Private & m ;
        
        Sentry( const Widget & widget_,
              Widget_Emitter::Private & m_ )
            : widget(widget_),
              m(m_)
        {
            m.emitting.push_back(&widget) ;
        }

        ~Sentry()
        {
            assert(std::find(m.emitting.begin(),
                             m.emitting.end(),
                             &widget)
                   !=
                   m.emitting.end()) ;
            
            m.emitting.erase(std::find(m.emitting.begin(),
                                       m.emitting.end(),
                                       &widget)) ;
            
            assert(std::find(m.emitting.begin(),
                             m.emitting.end(),
                             &widget)
                   ==
                   m.emitting.end()) ;
        }
    } ;

    std::vector<const Widget*> emitting ;

    Private()
        : emitting() { }

    using Handle_Sender::send_handle ;
} ;

Widget_Emitter::
Widget_Emitter()
    : m(new Private())
{
    add_encoder(*m) ;
}

Widget_Emitter::
~Widget_Emitter()
{
}

bool
Widget_Emitter::
emit_widget( const Widget & widget,
             const message::Handle_Args & args )
{
    bool handled = false ;

    if( std::find(m->emitting.begin(),
                  m->emitting.end(),
                  &widget)
        ==
        m->emitting.end() )
    {
        Private::Sentry sentry(widget, *m) ;
        handled = m->send_handle(args) ;
    }

    return handled ;
}

}}} // namespace esve::ui::extra
