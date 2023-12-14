#include "menu.h"
#include "game.h"
#include <stdio.h>
#include <Windows.h>


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
    //Alternativ ("../sounds/rock-cinematic-161648.wav") -> beide Ordner sind angelegt und die Datei befindet sich in beiden Ordnern
    if (SDL_LoadWAV("../SDL2/sounds/rock-cinematic-161648.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("Die Audiodatei konnte nicht geladen werden: %s\n", SDL_GetError());
        return;
    }

    // Spiel die Audiodatei ab
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0); //(Standard-Audiogerät,1 für Aufnahme/ 0 für Wiedergabe,Zeiger auf eine SDL_AudioSpec-Struktur,NULL: In diesem Fall wird kein Zeiger auf eine SDL_AudioSpec-Struktur übergeben, die die tatsächlich verwendeten Audio-Eigenschaften speichert,0: allowed_changes ist ein Bitfeld, das Änderungen an den geöffneten Eigenschaften erlaubt)
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

    printf("\n\aalarm sound mit a\n");
    printf("\7alarm sound mit 7\n");
    // Spiele einen System-Sound ab (Exclamation-Sound)
    MessageBeep(MB_ICONEXCLAMATION);    //nur dieser Ton wird bei mir abgespielt

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