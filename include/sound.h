#pragma once

#include <stdbool.h>


//===========================
//======== playSound ========
//===========================
//abstract function that plays sound with provided path to .wav file
//wait parameter blocks program until playback finished (otherwise launched in another thread)
int playSound(const char * filePath, bool wait);


//==========================
//===== playSoundAsync =====
//==========================
//launches playSound in another thread to prevent delay
//due to loading file taking up to 300ms
//(equivalent to playsound() with parameter wait=false)
void playSoundAsync(const char *filePath);