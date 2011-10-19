
#ifndef esve_message_diagnostic_hxx
#define esve_message_diagnostic_hxx

#if defined(ESVE_DIAGNOSTIC)

#if defined(ESVE_DEMANGLE)
#include <cxxabi.h>
#endif

#include <iostream>
#include <string>
#include <typeinfo>

namespace esve { namespace message {

namespace diagnostic {

inline
void
indent()
{
    std::cerr.fill(' ') ;
    std::cerr.width(24) ;
    std::cerr.setf(std::ios_base::right, std::ios_base::adjustfield) ;
}

template< typename Key >
void
key( const Key & k )
{
    indent() ;
    std::cerr << k << ": " ;
}

template< typename Value >
void
value( const Value & v )
{
    indent() ;
    std::cerr << " " << "  " << v << std::endl ;
}

template< typename Value >
void
pair( const std::string & k,
      const Value & v )
{
    key(k) ;
    std::cerr << v << std::endl ;
}

template< typename Value1, typename Value2 >
void
triple( const std::string & k,
        const Value1 & v1,
        const Value2 & v2 )
{
    key(k) ;
    std::cerr << v1 << '\t' << v2 << std::endl ;
}

#define esve_report(expr) \
    esve::message::diagnostic::pair(#expr, (expr))

inline
void
header_begin( const std::string & message_name )
{
    std::cerr.fill('_') ;
    std::cerr.width(79) ;
    std::cerr << "_" << std::endl ;
    std::cerr << message_name << "()" << std::endl ;
}

template< typename Sender, typename Receiver >
void
header( const std::string & message_name,
        const Sender & sender,
        const Receiver & receiver )
{
    header_begin(message_name) ;
#if defined(ESVE_DEMANGLE)
    int status = 0 ;
    triple("from",
           dynamic_cast<const void*>(&sender),
           abi::__cxa_demangle(typeid(sender).name(), 0, 0, &status)) ;
    triple("to",
           dynamic_cast<const void*>(&receiver),
           abi::__cxa_demangle(typeid(receiver).name(), 0, 0, &status)) ;
#else
    triple("from",
           dynamic_cast<const void*>(&sender),
           typeid(sender).name()) ;
    triple("to",
           dynamic_cast<const void*>(&receiver),
           typeid(receiver).name()) ;
#endif
}

template< typename Receiver >
void
header_receiver_only( const std::string & message_name,
                      const Receiver & receiver )
{
    header_begin(message_name) ;
#if defined(ESVE_DEMANGLE)
    int status = 0 ;
    triple("to",
           dynamic_cast<const void*>(&receiver),
           abi::__cxa_demangle(typeid(receiver).name(), 0, 0, &status)) ;
#else
    triple("to",
           dynamic_cast<const void*>(&receiver),
           typeid(receiver).name()) ;
#endif
}

} // namespace diagnostic

}} // namespace esve::message

#endif // defined(ESVE_DIAGNOSTIC)

#endif
