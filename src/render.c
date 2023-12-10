#include "render.h"
#include "SDL.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include "config.h"
#include <stdio.h>

SDL_Renderer* renderer;
SDL_Window* window;

void renderGame(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
/*  SDL_RenderClear(renderer);

//Head__________________________________________________
    SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);   //RGB-Farbe Kopf
    SDL_Rect rect;
    rect.x = (game.snake.headX * config.blockSizePx);   //Abstand links
    rect.y = (game.snake.headY * config.blockSizePx);   //Abstand rechts
    rect.w = config.blockSizePx;
    rect.h = config.blockSizePx;

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern


 //Snake-Baustein kreieren_________________________________________________________________
  for(int i = 1; i>game.snake.length; i++){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   //RGB-Farbe Tail

    SDL_Rect rect;
    rect.x = (game.snake.tail[i][0] * config.blockSizePx);   //Abstand links
    rect.y = (game.snake.tail[i][0] * config.blockSizePx);   //Abstand rechts
    rect.w = config.blockSizePx;
    rect.h = config.blockSizePx;

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern
  }

  //Portal kreieren________________________________________________________________________
  for (int i = 0; i < game.map.portalCount; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);   //RGB-Farbe Portal
        rect.x = (game.map.portals[i].posX * config.blockSizePx);
        rect.y = (game.map.portals[i].posY * config.blockSizePx);

        SDL_RenderDrawRect(renderer, &rect);    //Rechteck rendern
    }



    //Food kreieren_________________________________________________________________________
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   //RGB-Farbe Food

    rect.x = (game.foodX*config.blockSizePx);   //Abstand links
    rect.y = (game.foodY* config.blockSizePx);   //Abstand rechts
    rect.w = config.blockSizePx;
    rect.h = config.blockSizePx;

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern

        SDL_RenderDrawRect(renderer, &rect);    //Rechteck rendern

    //Collisions kreieren_________________________________________________________________________
    for(int i = 0; i < game.map.collisionCount; i++){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   //RGB-Farbe Wand

    rect.x = (game.map.collisions[i].posX*config.blockSizePx);   //Abstand links
    rect.y = (game.map.collisions[i].posY* config.blockSizePx);   //Abstand rechts
    rect.w = config.blockSizePx;
    rect.h = config.blockSizePx;

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern
    }
*/
    SDL_RenderPresent(renderer);    //Fenster aktualisieren

}




int CreateSDLWindow(){


    // Erstelle ein SDL-Fenster
  SDL_Window* window = SDL_CreateWindow("Snake", 350, 50, config.windowSize, config.windowSize, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Fenster konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
	}

void DestroyWindow(){
      // Zerstöre das Fenster und beende SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}