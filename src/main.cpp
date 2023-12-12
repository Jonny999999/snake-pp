#include <stdio.h>
#include <time.h>

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





  time_t now;
  now = clock(); // Timer startet
  game.timestampLastCycle = now;

  while(game.gameState != EXIT) {
    if (game.gameState == RUNNING) {
        now = clock(); // Timer startet

        if (now - game.timestampLastCycle > config.cycleDurationMs){
          game.timestampLastCycle = now;
          runGameCycle();
        } else{
          DELAY(5);     //verhindert maximale Durchlaufgeschwindigkeit der Schleife
          processInputEvent();
        }
    }
  }


  DestroySDLWindow();
  SDL_Quit();
  return 0;
}
