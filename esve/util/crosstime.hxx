//
// cross-platform time.
//
// ********* WARNING WARNING WARNING *********
//
// This file includes <windows.h> when the target platform is Windows.
// Don't become dependent on <windows.h>, else you will be harshly
// ridiculed.
//
// ********* WARNING WARNING WARNING *********
//

#ifndef esve_util_crosstime_hxx
#define esve_util_crosstime_hxx

#if defined(WIN32)
    #if !defined(USE_ANSI_CLOCK) && !defined(USE_WIN32_MMSYSTEM)
        #define USE_WIN32_MMSYSTEM
    #endif
#else
    #if !defined(USE_ANSI_CLOCK) && !defined(USE_SYS_TIMES)
        #define USE_SYS_TIMES
    #endif
#endif

#if defined(USE_ANSI_CLOCK)

    #include <ctime>

#elif defined(USE_SYS_TIMES)

    #include <sys/types.h>
    #include <sys/times.h>
    #include <unistd.h>

#elif defined(USE_WIN32_MMSYSTEM)

    #include <windows.h>
    #include <mmsystem.h>

#endif

namespace esve { namespace util {

namespace crosstime {

#if defined(USE_ANSI_CLOCK)

    typedef std::clock_t crosstime_t ;
    const crosstime_t CROSSTIME_CLOCKS_PER_SEC = CLOCKS_PER_SEC ;

#elif defined(USE_SYS_TIMES)

    typedef clock_t crosstime_t ;
    extern const crosstime_t CROSSTIME_CLOCKS_PER_SEC ;

#elif defined(USE_WIN32_MMSYSTEM)

    typedef DWORD crosstime_t ;
    const crosstime_t CROSSTIME_CLOCKS_PER_SEC = 1000 ;

#endif

crosstime_t crosstime() ;

} // namespace crosstime

}} // namespace esve::util

#endif
