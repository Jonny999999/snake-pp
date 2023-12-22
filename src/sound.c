#include <stdint.h>
#include <pthread.h>
#include "SDL.h"

#include "common.h"
#include "sound.h"


//--- global variables in sound.c ---
// mutex to prevent segfaults while working with multiple threads
pthread_mutex_t mutexSoundPlaying;
// initialize audio only once
static bool audioIsInitialized = false;



//---------------------------
//-------- initAudio --------
//---------------------------
// initialize SDL audio and mutex if not done already
int initAudio()
{
    if (!audioIsInitialized)
    {
        //--- initialize mutex ---
        pthread_mutex_init(&mutexSoundPlaying, NULL);
        //--- initialize SDL audio ---
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
        {
            LOGE("sound: SDL - could not init audio!\n");
            return 1;
        }
        audioIsInitialized = true;
        LOGI("sound: initialized SDL audio\n");
    }
    return 0;
}


//===========================
//======== playSound ========
//===========================
//abstract function that plays sound with provided path to .wav file
//wait parameter blocks program until playback finished
int playSound(const char *filePath, bool wait)
{
    //--- variables ---
    static bool deviceExists = false;
    static uint8_t *wavBuffer;
    static SDL_AudioDeviceID deviceId;
    SDL_AudioSpec wavSpec;
    uint32_t wavLength;

    //--- initialize audio --- 
    // initializes if not done already, exit if failed
    if (initAudio()) return 1;

    //--- run async when wait is not set ---
    if (!wait){
        return playSoundAsync(filePath);
    }

    //=== lock mutex ===
    pthread_mutex_lock(&mutexSoundPlaying);

    //--- load file ---
    if (SDL_LoadWAV(filePath, &wavSpec, &wavBuffer, &wavLength) == NULL)
    {
        LOGE("sound: file '%s' could not be loaded E:'%s'\n", filePath, SDL_GetError());
        pthread_mutex_unlock(&mutexSoundPlaying);
        return 1;
    }

    //--- play file ---
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    deviceExists = true;
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    LOGD("sound: playing file '%s'\n", filePath);

    //--- wait until playback is finished ---
    while (SDL_GetQueuedAudioSize(deviceId) > 0)
    {
        SDL_Delay(100);
    }

    //--- close device and free memory ---
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);

    //=== unlock mutex ===
    pthread_mutex_unlock(&mutexSoundPlaying);

    return 0;
}




//-------------------------------
//------- playSoundThread -------
//-------------------------------
// thread that runs playSound() and exits when done
void *playSoundThread(void *filePath) {
    // run (slow) playSound function
    playSound((const char *)filePath, true);
    // Clean up and exit the thread
    free(filePath);
    pthread_exit(NULL);
}


//==========================
//===== playSoundAsync =====
//==========================
// play audio file asynchronously
// creates separate thread which runs playSound 
// -> program does not get blocked by up to 300ms for loading the file
int playSoundAsync(const char *filePath) {
    //--- initialize audio --- 
    // initializes if not done already, exit if failed
    if (initAudio()) return 1;

    //--- allocate memory for filePath ---
    char *filePathCopy = strdup(filePath);
    if (filePathCopy == NULL) {
        LOGE("sound: Memory allocation failed\n");
        return 1;
    }

    //--- create new thread ---
    pthread_t thread;
    if (pthread_create(&thread, NULL, playSoundThread, filePathCopy) != 0) {
        LOGE("sound: Failed to create thread\n");
        free(filePathCopy);
        return 1;
    } else {
        // detach the thread to clean up automatically when it exits
        pthread_detach(thread);
        return 0;
    }
}