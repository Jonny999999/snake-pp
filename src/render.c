#include "render.h"
#include "SDL.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include "config.h"
#include <stdio.h>



void renderGame(){
  SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game.renderer);

  SDL_Rect rect;    //Rechteck anlegen
  rect.w = config.blockSizePx;    //Breite festlegen
  rect.h = config.blockSizePx;    //Höhe festlegen

//_______Head kreieren__________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255);   //RGB-Farbe Kopf
  rect.x = (game.snake.headX * config.blockSizePx);   //Abstand links
  rect.y = (game.snake.headY * config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern


//______Tail kreieren_________________________________________________________________
  for(int i = 1; i<game.snake.length; i++){
    SDL_SetRenderDrawColor(game.renderer, 15, 179, 15, 255);   //RGB-Farbe Tail
    rect.x = (game.snake.tail[i][0] * config.blockSizePx);   //Abstand links
    rect.y = (game.snake.tail[i][1] * config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  }

//______Portal kreieren________________________________________________________________________
  for (int i = 0; i < game.map.portalCount; i++)
  {
    switch(i) {     //Farben je nach Start-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(game.renderer, 90, 150, 255, 255); break;   //Start: hellblau
      case 1: SDL_SetRenderDrawColor(game.renderer, 255, 150, 255, 255); break;      //Start: rosa
      default: SDL_SetRenderDrawColor(game.renderer, 255, 150, 150, 255); break;      //Start: hellrot
    }

    //Start-Portal
    rect.x = (game.map.portals[i].posX * config.blockSizePx);
    rect.y = (game.map.portals[i].posY * config.blockSizePx);

    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern

    switch(i) {   //Farben je nach Ausgangs-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(game.renderer, 45, 45, 255, 255); break;   //Ausgang: dunkelblau
      case 1: SDL_SetRenderDrawColor(game.renderer, 204, 0, 204, 255); break;      //Ausgang: violett
      default: SDL_SetRenderDrawColor(game.renderer, 255, 50, 0, 255); break;      //Ausgang: rot
    }

    //Ausgangs-Portal
    rect.x = (game.map.portals[i].targetX * config.blockSizePx);
    rect.y = (game.map.portals[i].targetY * config.blockSizePx);

    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern
  }


//_______Food kreieren_________________________________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 255, 200, 0, 255);   //RGB-Farbe Food
  rect.x = (game.foodX*config.blockSizePx);   //Abstand links
  rect.y = (game.foodY* config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
   SDL_SetRenderDrawColor(game.renderer, 255, 140, 0, 255);   //RGB-Farbe Food Rahmen
     SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern



//______Collisions kreieren_________________________________________________________________________
  for(int i = 0; i < game.map.collisionCount; i++){
    SDL_SetRenderDrawColor(game.renderer, 112, 128, 144, 255);   //RGB-Farbe Wand
    rect.x = (game.map.collisions[i].posX*config.blockSizePx);   //Abstand links
    rect.y = (game.map.collisions[i].posY* config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
    SDL_SetRenderDrawColor(game.renderer, 80, 90, 100, 255);   //RGB-Farbe Wand-Rand
    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern
  }

//_________________Augen___________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
  rect.w = config.blockSizePx/4;    //Breite festlegen
  rect.h = config.blockSizePx/4;    //Höhe festlegen
  if (game.snake.direction == LEFT || game.snake.direction == RIGHT){
  //oberes Auge  
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/2.5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  //unteres Auge
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/2.5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/1.7; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  
  } else {
  //linkes Auge  
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/2.5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  //rechtes Auge
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/1.7;   //Abstand links
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/2.5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  }
  SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern

//______Fenster aktualisieren____________________________________________
  SDL_RenderPresent(game.renderer);    //Fenster aktualisieren

}




int CreateSDLWindow(){


    // Erstelle ein SDL-Fenster
  game.window = SDL_CreateWindow("Snake", 350, 50, config.windowSize, config.windowSize, SDL_WINDOW_OPENGL);
    if (game.window == NULL) {
        printf("Fenster konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

  game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (game.renderer == NULL) {
        printf("Renderer konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
	}

void DestroySDLWindow(){
      // Zerstöre das Fenster und beende SDL
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
}