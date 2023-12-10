#include <stdio.h>

extern "C"
{
#include "game.h"
#include "common.h"
#include "input.h"
#include "render.h"
}

//initialize SDL window
//ruft showStartScreen
//initialize game
//main loop: processInputEvents, runGameCycle
//uninitialize SDL



//==========================
//====== enabled test ======
//==========================
//uncomment one test at a time to run the corresponding code in main()
//#define TEST__FOOD_PLACEMENT
//#define TEST__SDL_INPUT
#define TEST__GAME_WITH_CONSOLE_OUTPUT




int main(int argc, char *argv[])
{
  gameInit();

  // Initialisiere SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL konnte nicht initialisiert werden! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  CreateSDLWindow();

  while(1){
  if(game.gameState != EXIT) {
    if (game.gameState == RUNNING) {
        processInputEvent();
        DELAY(config.cycleDurationMs);
        processInputEvent();
        runGameCycle();
    }

  } else {
    DestroySDLWindow();
    SDL_Quit(); 
    return 0;}
  }


  return 0;
}
