#include <stdbool.h>

#include "snake.h"
#include "config.h"

typedef enum gameState_t
{
    PAUSED = 0,
    MENU,
    RUNNING
} gameState_t;

typedef struct portal_t
{
  int posX, posY;
  int targetX, targetY;

  char * color;
} portal_t;

typedef struct gameData_t
{
    snake_t snake;
    int mapCollisions[MAX_MAP_SIZE][MAX_MAP_SIZE]; // Position der Wände
    portal_t mapPortals[MAX_PORTALS];       
    int mapPortalCount;   // Anzahl der Portale

    int foodX, foodY;   // Positon des Futters (es gibt immer nur 1 Futter)
    int lifesRemaining; // implementieren wir nicht!!
    int timestampLastRun;
    bool isPaused;
    gameState_t gameState;
} gameData_t;

// global struct for storing all game data (defined in game.c)
extern gameData_t game;

void gameInit();
// berechnet BlockSizePx: windowSize/mapWidth
// ruft snakeInit auf
// ruft placeFood auf
// platziert Wände

bool checkIsCollided();
// Überprüft, ob Snake mit Gegenstand/Wand kollidiert ist
// if true -> gibt 1 an runGameCycle zurück


void handlePortals(); // optional
// Prüft, ob Snake sich auf einem Portal befindet
//if true: snakeSetHeadPos auf

void runGameCycle();
// macht immer: handleKeyboardEvents();
// optional: ruft checkCollision() auf
// ruft placeFood() auf
// ruft checkEaten() auf
// if checkEaten then snakeGrow()
// if TickDue: Snakemove(), TickTimerReset
// ruft snakeMove() auf
//ruft am Ende vom gameCycle renderGame() auf
