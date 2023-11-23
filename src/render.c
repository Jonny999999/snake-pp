#include "render.h"

void renderGame(){
    //note: maybe re-use renderGameToArray() from map.h?
    //e.g. as used in map.c for printMap()
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

    	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow
       ("Ein SDL2-Fenster", // Name des Fensters
	10, 25, // Koordinaten auf dem Bildschirm in Pixeln, ausgehend von links oben 
        840, 840, // Breite und Höhe des Fenster in Pixeln 
	SDL_WINDOW_OPENGL);

	SDL_Delay(30000); // Das Fenster bleibt drei Sekunden 
	SDL_DestroyWindow(window);
	SDL_Quit();


    return;
}