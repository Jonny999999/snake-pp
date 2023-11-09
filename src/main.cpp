#include "SDL.h"

extern "C" {
#include "food.h"
}

//initialize SDL window
//ruft showStartScreen
//initialize game
//main loop: processInputEvents, runGameCycle
//uninitialize SDL


int main(int argc, char *argv[])
{
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

  SDL_Delay(1000);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
