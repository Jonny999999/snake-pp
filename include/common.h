#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "config.h"

//===========================
//========= LOGGING =========
//===========================
//conditional logging when DEBUG_OUTPUT_ENABLED is defined in config.h
//example: LOGD("game: %d", count)
#ifdef DEBUG_OUTPUT_ENABLED
#define LOGD(format, ...) printf("[D] " format, ##__VA_ARGS__)
#else
#define LOGD(format, ...) do {} while (0)
#endif

//conditional logging when INFO_OUTPUT_ENABLED is defined in config.h
//example: LOGI("game: %d", count)
#ifdef INFO_OUTPUT_ENABLED
#define LOGI(format, ...) printf("[I] " format, ##__VA_ARGS__)
#else
#define LOGI(format, ...) do {} while (0)
#endif

//conditional logging when ERROR_OUTPUT_ENABLED is defined in config.h
//also prints in text in red color (windows not supported)
//example: LOGE("game: %d", count)
#ifdef ERROR_OUTPUT_ENABLED
  #ifdef _WIN32 //print error output in default color (currently no color support for windows)
    #define LOGE(format, ...) printf("[E] " format, ##__VA_ARGS__)
  #else //print error output in red color
    #define RED_TEXT "\033[1;31m"
    #define RESET_TEXT "\033[0m"
    #define LOGE(format, ...) printf(RED_TEXT "[E] " format RESET_TEXT, ##__VA_ARGS__)
  #endif
#else
  #define LOGE(format, ...) do {} while (1)
#endif


//===========================
//========== DELAY ==========
//===========================
//macro for DELAY(ms) function that works on Windows and Linux
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#define DELAY(ms) Sleep(ms)
#else
#include <unistd.h>
#define DELAY(ms) usleep((ms) * 1000)
#endif


//===========================
//======= GET_TIME_MS =======
//===========================
// macro to get time in milliseconds
#define GET_TIME_MS() get_current_time()
// defined in common.c due to differences with windows and other systems
int64_t get_current_time();