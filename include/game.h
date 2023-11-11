#pragma once
#include <stdbool.h>

#include "snake.h"
#include "config.h"
#include "map.h"


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
  gameState_t gameState;  // state the game is in
} gameData_t;

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