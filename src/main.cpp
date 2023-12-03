#include "SDL.h"

extern "C" {
#include "food.h"
#include "game.h"
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


#ifdef TEST__FOOD_PLACEMENT
  // --- test food.c ---
  startFoodPlacementTest();
#endif



  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    0
  );

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);





#ifdef TEST__GAME_WITH_CONSOLE_OUTPUT
  // --- test game with render to console ---
  game.gameState = RUNNING;
  while (game.gameState != EXIT)
  {
    processInputEvent();
    SDL_Delay(600);
    processInputEvent();
    runGameCycle();
  }
#endif




#ifdef TEST__SDL_INPUT
  // --- test input.c ---
  game.gameState = RUNNING;
  while (game.gameState != EXIT)
  {
    processInputEvent();
    SDL_Delay(100);
  }
#endif





  SDL_Delay(500);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
