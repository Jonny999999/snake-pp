#pragma once
#include <stdbool.h>
#include <string.h>

#include "snake.h"
#include "config.h"
#include "map.h"
#include "SDL.h"


// Enum that defines the current game state
typedef enum gameState_t
{
  EXIT = 0,
  RUNNING,
  MENU,
  PAUSED
} gameState_t;


// Struct that stores all data of the running game (all game-related functions access it globally)
typedef struct gameData_t
{
  snake_t snake;      // data describing snake
  map_t map;          // loaded map
  bool mapIsLoaded;   // true when game.map is valid
  int foodX, foodY;   // current position of food
  int lifesRemaining; // not implemented
  int timestampLastCycle; // time last game cycle started
  SDL_Renderer* renderer; // used by render.c and menu.c
  SDL_Window *window;     // used by render.c and menu.c
  gameState_t gameState;  // state the game is in
} gameData_t;


// struct that store player score at the end of the game
typedef struct playerScore_t
{
    int score;
    char playerName[30];
    int difficulty;
    char map[30];
} playerScore_t;


// global struct for storing all game data (defined in game.c)
extern gameData_t game;

// run once at game start and does the following:
// - init snake
// - load map
// - place initial food
void gameInit();


// when snake head is on a portal-input, sets snake head to portal-target
void handlePortals(); //(ran in gameCycle)


// function that is repeatedly run at every game tick
// - moves snake to next position
// - handles collision, portals, food
// - triggers frame update (render.c)
void runGameCycle();

// function which saves score in a .csv file
  // void savePlayerScore()