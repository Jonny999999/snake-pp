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
  snake_t snake;
  map_t map;          // definition der geladenen karte
  bool mapIsLoaded; // true when config.map is valid
  int foodX, foodY;   // Positon des Futters (es gibt immer nur 1 Futter)
  int lifesRemaining; // implementieren wir nicht!!
  int timestampLastCycle;
  gameState_t gameState;
} gameData_t;

// global struct for storing all game data (defined in game.c)
extern gameData_t game;

void gameInit();
// berechnet BlockSizePx: windowSize/mapWidth
// ruft snakeInit auf
// ruft placeFood auf
// platziert Wände

void handlePortals(); //(local)
// Prüft, ob Snake sich auf einem Portal befindet
//if true: snakeSetHeadPos auf

void runGameCycle();
// checkCollision() auf
// ruft placeFood() auf
// ruft checkEaten() auf
// if checkEaten then snakeGrow()
// Snakemove(), TickTimerReset
//ruft am Ende vom gameCycle renderGame() auf
