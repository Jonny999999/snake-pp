#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include "common.h"


//============================
//==== get_current_time() ====
//============================
// Function that returns current time in milliseconds (can be used on windows and other systems)
int64_t get_current_time()
{
#ifdef WIN32
    //=== WINDOWS ===
    FILETIME ft;
    LARGE_INTEGER li;
    // Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it to a LARGE_INTEGER structure.
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    uint64_t ret = li.QuadPart;
    ret -= 116444736000000000LL; // Convert from file time to UNIX epoch time.
    ret /= 10000;                // From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals
    return ret;

#else

    //=== LINUX ===
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t ret = tv.tv_usec;
    // Convert from micro seconds (10^-6) to milliseconds (10^-3)
    ret /= 1000;
    // Adds the seconds (10^0) after converting them to milliseconds (10^-3)
    ret += (tv.tv_sec * 1000);
    return ret;
#endif
}