#include "menu.h"
#include "game.h"


void showStartScreen(){
    game.gameState = RUNNING;
    return;
}

void showLeaderboard(){
    game.gameState = EXIT;
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