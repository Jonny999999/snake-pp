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
#define LOGD(format, ...) printf(format, ##__VA_ARGS__)
#else
#define LOGD(format, ...) do {} while (0)
#endif

//conditional logging when INFO_OUTPUT_ENABLED is defined in config.h
//example: LOGD("game: %d", count)
#ifdef INFO_OUTPUT_ENABLED
#define LOGI(format, ...) printf(format, ##__VA_ARGS__)
#else
#define LOGI(format, ...) do {} while (0)
#endif
