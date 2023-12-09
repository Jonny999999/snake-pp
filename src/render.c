#include "render.h"
#include "SDL.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include <stdio.h>

void renderGame(SDL_Renderer* renderer){
  
  //Snake-Baustein kreieren_________________________________________________________________
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);   //RGB-Farbe Schlange

    SDL_Rect rect;
    rect.x = 500/*game.snake.headX * config_t.blockSizePx*/;   //Abstand links
    rect.y = 300/*game.snake.headY * config_t.blockSizePx*/;   //Abstand rechts
    rect.w = 20/*config_t.blockSizePx*/;
    rect.h = 20/*config_t.blockSizePx*/;

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern

  //Portal kreieren________________________________________________________________________
    SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);   //RGB-Farbe Portal

    rect.x = 500;   //Abstand links
    rect.y = 200;   //Abstand rechts

    SDL_RenderDrawRect(renderer, &rect);    //Rechteck rendern

    //Food kreieren_________________________________________________________________________
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);   //RGB-Farbe Food

    rect.x = 300/*foodX*/;   //Abstand links
    rect.y = 600/*foodY*/;   //Abstand rechts

    SDL_RenderFillRect(renderer, &rect);    //Rechteck rendern

    SDL_RenderPresent(renderer);    //Fenster aktualisieren
}




int CreateSDLWindow(){
    // Initialisiere SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL konnte nicht initialisiert werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Erstelle ein SDL-Fenster
    SDL_Window* window = SDL_CreateWindow("Snake", 350, 50, 800, 800, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Fenster konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    renderGame(renderer);

    // Warte
    SDL_Delay(5000);

    // Zerstöre das Fenster und beende SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
	}


	/*SDL_Event event;
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	int done = 0;
	atexit(SDL_Quit);
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		return 1;
	}
	
	window = SDL_CreateWindow(
                                  "SDL Tutorial", 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  640, 480, 
                                  SDL_WINDOW_SHOWN
                 );
	if (window == NULL){
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}
	
	surface = SDL_GetWindowSurface(window);
	if (surface == NULL){
		printf( "Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}
	
	while (done == 0)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = 1;
				break;
			}
		}
	}

	SDL_DestroyWindow(window);*/