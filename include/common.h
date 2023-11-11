#pragma once

#include <stdio.h>
#include <stdarg.h>
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
