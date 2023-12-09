#include "render.h"
#include "SDL.h"

void renderGame(){}

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

    // Warte drei Sekunden
    SDL_Delay(10000);

    // Zerstöre das Fenster und beende SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
	}


