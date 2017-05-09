
#include <esve/util/crosstime.hxx>

namespace esve { namespace util {

namespace crosstime {

#if defined(USE_SYS_TIMES)
const crosstime_t CROSSTIME_CLOCKS_PER_SEC = sysconf(_SC_CLK_TCK) ;
#endif

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

