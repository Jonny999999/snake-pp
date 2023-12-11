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
  SDL_RenderClear(renderer);

  SDL_Rect rect;    //Rechteck anlegen
  rect.w = config.blockSizePx;    //Breite festlegen
  rect.h = config.blockSizePx;    //Höhe festlegen

//_______Head kreieren__________________________________________________
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   //RGB-Farbe Kopf
  rect.x = (game.snake.headX * config.blockSizePx);   //Abstand links
  rect.y = (game.snake.headY * config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern


//______Tail kreieren_________________________________________________________________
  for(int i = 1; i<game.snake.length; i++){
    SDL_SetRenderDrawColor(renderer, 15, 179, 15, 255);   //RGB-Farbe Tail
    rect.x = (game.snake.tail[i][0] * config.blockSizePx);   //Abstand links
    rect.y = (game.snake.tail[i][1] * config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern
  }

//______Portal kreieren________________________________________________________________________
  for (int i = 0; i < game.map.portalCount; i++)
  {
    switch(i) {     //Farben je nach Start-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(renderer, 90, 150, 255, 255); break;   //Start: hellblau
      case 1: SDL_SetRenderDrawColor(renderer, 255, 150, 255, 255); break;      //Start: rosa
      default: SDL_SetRenderDrawColor(renderer, 255, 150, 150, 255); break;      //Start: hellrot
    }

    //Start-Portal
    rect.x = (game.map.portals[i].posX * config.blockSizePx);
    rect.y = (game.map.portals[i].posY * config.blockSizePx);

    SDL_RenderDrawRect(renderer, &rect);    //Rechteck rendern

    switch(i) {   //Farben je nach Ausgangs-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(renderer, 45, 45, 255, 255); break;   //Ausgang: dunkelblau
      case 1: SDL_SetRenderDrawColor(renderer, 204, 0, 204, 255); break;      //Ausgang: violett
      default: SDL_SetRenderDrawColor(renderer, 255, 50, 0, 255); break;      //Ausgang: rot
    }

    //Ausgangs-Portal
    rect.x = (game.map.portals[i].targetX * config.blockSizePx);
    rect.y = (game.map.portals[i].targetY * config.blockSizePx);

    SDL_RenderDrawRect(renderer, &rect);    //Rechteck rendern
  }


//_______Food kreieren_________________________________________________________________________
  SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);   //RGB-Farbe Food
  rect.x = (game.foodX*config.blockSizePx);   //Abstand links
  rect.y = (game.foodY* config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern



//______Collisions kreieren_________________________________________________________________________
  for(int i = 0; i < game.map.collisionCount; i++){
    SDL_SetRenderDrawColor(renderer, 112, 128, 144, 255);   //RGB-Farbe Wand
    rect.x = (game.map.collisions[i].posX*config.blockSizePx);   //Abstand links
    rect.y = (game.map.collisions[i].posY* config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern
  }

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

void DestroySDLWindow(){
      // Zerstöre das Fenster und beende SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}