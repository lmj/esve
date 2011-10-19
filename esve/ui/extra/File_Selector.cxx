
#include <esve/ui/extra/File_Selector.hxx>
#include <esve/ui/extra/File_Selector_Emitter.hxx>
#include <esve/ui/extra/File_Selector_Handler.hxx>
#include <esve/message/impl/Handle_Receiver.hxx>
#include <esve/message/Handle_Args.hxx>
#include <esve/message/diagnostic.hxx>
#include <cassert>
#include <algorithm>
#include <vector>

namespace esve { namespace ui { namespace extra {

namespace {

struct File_Selector_Handle_Args : public message::Handle_Args
{
    const File_Selector & file_selector ;

    File_Selector_Handle_Args( const File_Selector & file_selector_ )
        : file_selector(file_selector_) { }

    File_Selector_Handle_Args( const File_Selector_Handle_Args & a )
        : Handle_Args(),
          file_selector(a.file_selector) { }

    std::auto_ptr<message::Handle_Args> clone() const
    {
        return
            std::auto_ptr<message::Handle_Args>(
                new File_Selector_Handle_Args(file_selector)) ;
    }

#ifdef ESVE_DIAGNOSTIC
    void diagnostic() const
    {
        esve_report(&file_selector) ;
        esve_report(file_selector.value()) ;
    }
#endif
} ;

} // anon namespace

///////////////////////////////////////////////////////////////

File_Selector::
File_Selector()
{
}

File_Selector::
~File_Selector()
{
}

///////////////////////////////////////////////////////////////

File_Selector_Emitter::
File_Selector_Emitter()
{
}

File_Selector_Emitter::
~File_Selector_Emitter()
{
}

bool
File_Selector_Emitter::
emit_file_selector( const File_Selector & file_selector )
{
    return emit_widget(file_selector,
                       File_Selector_Handle_Args(file_selector)) ;
}

///////////////////////////////////////////////////////////////

struct File_Selector_Handler::Private
    : public message::impl::Handle_Receiver
{
    File_Selector_Handler & outside ;

    Private( File_Selector_Handler & outside_ )
        : outside(outside_) { }
    
    bool handle( const message::Handle_Args & ) ;
} ;

File_Selector_Handler::
File_Selector_Handler()
    : m(new Private(*this))
{
    add_decoder(*m) ;
}

File_Selector_Handler::
~File_Selector_Handler()
{
}

bool
File_Selector_Handler::Private::
handle( const message::Handle_Args & generic_args )
{
    bool handled = false ;

    if( const File_Selector_Handle_Args* file_selector_args =
        dynamic_cast<const File_Selector_Handle_Args*>(&generic_args) )
    {
        handled =
            outside.handle_file_selector(file_selector_args->file_selector) ;
    }

    return handled ;
}

}}} // namespace esve::ui::extra
