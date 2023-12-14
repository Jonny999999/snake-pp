#pragma once

#include <stdbool.h>


//===========================
//======== playSound ========
//===========================
//abstract function that plays sound with provided path to .wav file
//wait parameter blocks program until playback finished
int playSound(const char * filePath, bool wait);