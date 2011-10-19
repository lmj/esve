
#include <esve/util/crosstime.hxx>

namespace esve { namespace util {

namespace crosstime {

crosstime_t
crosstime()
{
#if defined(USE_ANSI_CLOCK)
    return std::clock() ;
#elif defined(USE_SYS_TIMES)
    tms unused ;
    return times(&unused) ;
#elif defined(USE_WIN32_MMSYSTEM)
    return timeGetTime() ;
#endif
}

} // namespace crosstime

}} // namespace esve::util

