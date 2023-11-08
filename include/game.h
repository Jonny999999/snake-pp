#include <stdbool.h>

#include "snake.h"
#include "config.h"

typedef enum gameState_t
{
    PAUSED = 0,
    MENU,
    RUNNING
} gameState_t;

typedef struct gameData_t
{
    snake_t snake;
    int mapCollisions[MAX_MAP_SIZE][MAX_MAP_SIZE]; // Position der Wände
    int mapPortals[MAX_MAP_SIZE][MAX_MAP_SIZE];    // Position der Portale

    int foodX, foodY;   // Positon des Futters (es gibt immer nur 1 Futter)
    int lifesRemaining; // implementieren wir nicht!!
    int timestampLastRun;
    bool isPaused;
    gameState_t gameState;
} gameData_t;

// global struct for storing all game data (defined in game.c)
extern gameData_t game;

void gameInit();
// ruft snakeInit auf
// ruft place Food auf

void handleCollision();
// Überprüft, ob Snake mit Gegenstand/Wand kollidiert ist

void handlePortals(); // optional
// Prüft, ob Snake sich auf einem Portal befindet

void runGameCycle();
// macht immer: handleKeyboardEvents();
// if TickDue: Snakemove(), TickTimerReset
// optional: ruft checkCollision auf
// ruft place food auf
// ruft checkEaten auf
// if checkEaten then snakeGrow
// ruft snakeMove auf
