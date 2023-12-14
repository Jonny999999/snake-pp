#include <stdint.h>
#include "sound.h"
#include "SDL.h"

#include "common.h"
#include "sound.h"



//===========================
//======== playSound ========
//===========================
//abstract function that plays sound with provided path to .wav file
//wait parameter blocks program until playback finished
int playSound(const char *filePath, bool wait)
{
    //TODO add volume % option

    //--- variables ---
    static bool soundInitialized = false;
    static bool deviceExists = false;
    static uint8_t *wavBuffer;
    static SDL_AudioDeviceID deviceId;
    SDL_AudioSpec wavSpec;
    uint32_t wavLength;
    

    //--- initialize SDL audio ---
    if (!soundInitialized)
    {
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            printf("SDL: could not init audio!\n");
            return 1;
        }
        LOGI("sound: initialized SDL audio\n");
    }


    //--- close device and free memory of previous sound ---
    //note: also cancels currently playing sound
    if (deviceExists)
    {
        SDL_CloseAudioDevice(deviceId);
        // free memory of previously played file
        SDL_FreeWAV(wavBuffer);
    }


    //--- load file ---
    if (SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength) == NULL)
    {
        printf("sound: file '%s' could not be loaded E:'%s'\n", filePath, SDL_GetError());
        return 1;
    }


    //--- play file ---
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    deviceExists = true;
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    LOGI("sound: success, playing file '%s'\n", filePath);


    //--- wait until playback is finished --- (if desired)
    while (wait && SDL_GetQueuedAudioSize(deviceId) > 0)
    {
        SDL_Delay(100);
    }

    return 0;
}