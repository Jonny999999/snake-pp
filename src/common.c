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
uint64_t get_current_time() {
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart / 10000;  // convert 100-nanoseconds to milliseconds
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;  // convert microseconds to milliseconds
#endif
}