#include <stdio.h>
#include <time.h>

extern "C"
{
#include "game.h"
#include "common.h"
#include "input.h"
#include "render.h"
#include "menu.h"
}

//1. initialize SDL window
//2. call showStartScreen
//3. initialize game
//4. main loop: processInputEvents, runGameCycle
//5. uninitialize SDL

int main(int argc, char *argv[])
{ 
  // gameInit();     moved to menu.c

  // Initialisiere SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOGI("SDL: SDL konnte nicht initialisiert werden! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  // Initialisiere SDL_ttl, um Text ausgeben zu können
    if (TTF_Init() == -1) {
    LOGI("SDL: SDL_ttf konnte nicht initialisiert werden! SDL_Error: %s\n");
    return 1;
  }

  CreateSDLWindow();


  time_t now;
  now = GET_TIME_MS(); // Timer startet
  game.timestampLastCycle = now;
  int diff;

  while(game.gameState != EXIT) {
    if(game.gameState == MENU)
    {   
        manageMenu();
    } 
    if(game.gameState == PAUSED)
    {
      LOGI("Spielmodus: Pause\n");
    }
    if (game.gameState == RUNNING) {
        now = GET_TIME_MS(); // Timer startet
        diff = now-game.timestampLastCycle;

        if (diff > config.cycleDurationMs){
          game.timestampLastCycle = now;
          runGameCycle();
        }
    }
    DELAY(5);     //verhindert maximale Durchlaufgeschwindigkeit der Schleife
    processInputEvent();
  }



  DestroySDLWindow();
  SDL_Quit();
  return 0;
}
