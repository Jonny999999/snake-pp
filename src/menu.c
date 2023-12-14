#include "menu.h"
#include "game.h"
#include "sound.h"
#include "common.h"
#include <stdio.h>
//#include <Windows.h>


void showStartScreen(){
    LOGI("menu: showing start-screen\n");
    game.gameState = RUNNING;
    return;
}

void showLeaderboard(){
    LOGI("menu: showing leaderboard\n");

    //--- play crash sound ---
    //play audio file, wait until playback is finished
    //note: when displaying actual leaderboard, the second parameter should be 'false' to not block the program
    playSound("../sounds/crash_rock-cinematic.wav", true); 
    DELAY(100);

    //--- quit game ---
    game.gameState = EXIT;
    return;
}

void showPauseScreen(){
    LOGI("menu: showing leaderboard\n");
    game.gameState = PAUSED;
    return;
}

void showSettings(){
    LOGI("menu: showing settings\n");
    return;
}

void menuHandleInput(SDL_Event event){
    //compare 'handleInput_runningState(SDL_Event event)' in input.c
    return;
}