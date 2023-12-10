#include <stdio.h>

extern "C" {
#include "food.h"
}

extern "C"{
  #include "render.h"
}

extern "C"{
  #include "game.h"
  #include "common.h"
}

//initialize SDL window
//ruft showStartScreen
//initialize game
//main loop: processInputEvents, runGameCycle
//uninitialize SDL


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
        DELAY(config.cycleDurationMs);
        runGameCycle();
    }

  } else {SDL_Quit(); return 0;}
  }


  return 0;
}
