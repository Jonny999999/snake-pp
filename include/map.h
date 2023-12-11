#pragma once

#include <stdbool.h>
#include "config.h"
#include "snake.h"


// Struct that stores all information needed for one Portal on the map
typedef struct portal_t
{
  int posX, posY;
  int targetX, targetY;
  char *color;
} portal_t;


// Struct that stores all information needed for one Collision box on the map
typedef struct collisionBox_t
{
  int posX, posY;
} collisionBox_t;


// Struct that describes an entire map
typedef struct map_t {
    int width;
    int height;
    char name[128];
    collisionBox_t collisions[MAX_MAP_FIELDS];
    int collisionCount;
    portal_t portals[MAX_MAP_FIELDS];
    int portalCount;
} map_t;


// calculates width in pixels of one block in the SDL window according to currently loaded map and configured window size and updates the config.
void updateBlockSizePx();


// search and load map by name in storedMaps[] (map.c) 
// stops program when map not found!
void loadMapByName(char *name);


//load map by passed definition
void loadMap(map_t map);


//load next map in stored maps (rotate through stored maps)
void rotateMapNext();


//return true when provided coordinate matches the position of a collision box
bool checkCollides(map_t map, int x, int y);


// generate random map based on difficulty level
// NOT IMPLEMENTED
map_t generateMap(int difficulty, int sizeX, int sizeY);


void printMap(map_t map);
// function that prints a map to console (stdout)
// note: currently also prints snake and food which may be bugged/unintended


// function that renders all current game objects to one 2d int array
// NOTE: passed Array has to be zero-initialized! (int arr[][] = {{0}})
// useful for rendering game to console or sdl
// 1=collision, 2=portalIn, 3=portalOut, 4=snakeHead, 5=snakeTail
void renderGameToArray(int mapFrame[MAX_MAP_SIZE][MAX_MAP_SIZE], map_t map, snake_t snake);


// stored map presets can be globally accessed (maybe needed by menu.c)
// not: maps defined in map.c end of file
 extern const map_t * storedMaps[16];
 extern const int storedMapsCount;