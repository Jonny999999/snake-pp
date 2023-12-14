#include "menu.h"
#include "game.h"
#include <stdio.h>


void showStartScreen(){
    game.gameState = RUNNING;
    return;
}

void showLeaderboard(){

    game.gameState = EXIT;

//____________Ton abspielen_________________

    // Lade die Audiodatei
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;

    //Prüfung, ob Datei geladen wurde
    if (SDL_LoadWAV("../sounds/rock-cinematic-161648.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("Die Audiodatei konnte nicht geladen werden: %s\n", SDL_GetError());
        return;
    }

    // Spiel die Audiodatei ab
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    printf("Audiodatei wird abgespielt");

    // Warte, bis die Wiedergabe abgeschlossen ist
    while (SDL_GetQueuedAudioSize(deviceId) > 0) {
        SDL_Delay(100);
    }

    // Aufräumen
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);

    return;
}

void showPauseScreen(){
    game.gameState = PAUSED;
    return;
}

void showSettings(){
    return;
}

void menuHandleInput(SDL_Event event){
    //compare 'handleInput_runningState(SDL_Event event)' in input.c
    return;
}