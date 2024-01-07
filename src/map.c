#include <string.h>
#include "map.h"
#include "game.h"
#include "common.h"

int indexLoadedMap = 0;

//===========================
//==== renderGameToArray ====
//===========================
// function that renders all current game objects to one 2d int array
// NOTE: passed Array has to be zero-initialized! (int arr[][] = {{0}})
// useful for rendering game to console or sdl
// 1=collision, 2=portalIn, 3=portalOut, 4=snakeHead, 5=snakeTail
void renderGameToArray(int mapFrame[MAX_MAP_SIZE][MAX_MAP_SIZE], map_t map, snake_t snake)
{
    // copy collisions
    for (int i = 0; i < map.collisionCount; i++)
    {
        mapFrame[map.collisions[i].posY][map.collisions[i].posX] = 1;
    }
    // copy portals
    for (int i = 0; i < map.portalCount; i++)
    {
        mapFrame[map.portals[i].posY][map.portals[i].posX] = 2;
        mapFrame[map.portals[i].targetY][map.portals[i].targetX] = 3;
    }
    // copy snake tail
    for (int i = 0; i < snake.length; i++)
    {
        mapFrame[snake.tail[i][1]][snake.tail[i][0]] = 5;
    }
     // copy food
    mapFrame[game.foodY][game.foodX] = 6;
    // copy snake head (last element -> head overwrites previous elements)
    mapFrame[snake.headY][snake.headX] = 4;
    return;
}



//========================
//======= printMap =======
//========================
// function that prints a map to console (stdout)
// note: currently also prints snake and food which may be bugged/unintended
#define PRINT_SNAKE_ENABLED
void printMap(map_t map)
{
    LOGI("map: Preview of map '%s' (%dx%d):\n", map.name, map.width, map.height);
    int mapFrame[MAX_MAP_SIZE][MAX_MAP_SIZE] = {{0}};
    renderGameToArray(mapFrame, map, game.snake);
    // --- print top line ---
    printf("+");
    for (int i = 0; i < map.width; i++) printf("-");
    printf("+\n");
    // --- print field ---
    // loop through rows (y)
    for (int row = 0; row < map.height; row++)
    {
        printf("|"); // vert line left
        // loop through line (x)
        for (int column = 0; column < map.width; column++)
        {
            switch (mapFrame[row][column])
            {
            case 1: printf("X"); // collistion
                break;
            case 2: printf("O"); // portal-in
                break;
            case 3: printf("T"); // portal-out
                break;
#ifdef PRINT_SNAKE_ENABLED
            case 4: printf("H"); // snake-head
                break;
            case 5: printf("S"); // snake-tail
                break;
#endif
            case 6: printf("F"); // food
                break;
            default: printf(" "); // empty
                break;
            }
        }
        printf("|\n"); // vert line right
    }
    // --- print bot line ---
    printf("+");
    for (int i = 0; i < map.width; i++)
        printf("-");
    printf("+\n");
}



//===========================
//======= generateMap =======
//===========================
// generate random map based on difficulty level
// NOT IMPLEMENTED
map_t generateMap(int difficulty, int sizeX, int sizeY)
{
    map_t newMap;
    return newMap;
    // TODO add map generator
}



//===========================
//==== updateBlockSizePx ====
//===========================
// calculates width in pixels of one block in the SDL window according to currently loaded map and configured window size and updates the config.
void updateBlockSizePx(){
    // due to square pixel requirement
    // larger dimension of the map has to be used if map is not square
    if (game.map.height >= game.map.width) {
        config.blockSizePx = config.windowSize / game.map.height;
    }
    else
    {
        config.blockSizePx = config.windowSize / game.map.width;
    }
}



//===========================
//====== loadMapByName ======
//===========================
// search and load map by name in storedMaps[] (map.c) 
// stops program when map not found!
void loadMapByName(const char *name)
{
    // loop through all stored maps
    for (int i = 0; i < storedMapsCount; i++)
    {
        // compare name
        if (strcmp(name, storedMaps[i]->name) == 0)
        {
            // load matched map
            LOGI("map: found map '%s'\n", name);
            loadMap(*storedMaps[i]);
            return;
        }
    }
    // map not found
    LOGE("[FATAL] map: could not find '%s' in storedMaps!\n", name);
    game.gameState = EXIT;
    return;
}


//===========================
//========= loadMap =========
//===========================
// load map by passed definition
void loadMap(map_t map)
{
    LOGI("map: loading map '%s':\n", map.name);
#ifdef DEBUG_OUTPUT_ENABLED
    printMap(map);
#endif
    game.map = map;
    // update rendered pixel size (due to new map size)
    updateBlockSizePx();
    game.mapIsLoaded = true;
    return;
}


//===========================
//====== rotateMapNext ======
//===========================
//load next map in stored maps (rotate through stored maps)
void rotateMapNext(){
    if (indexLoadedMap >= storedMapsCount -1 ){
        indexLoadedMap = 0;
    } else {
        indexLoadedMap ++;
    }
    loadMap(*storedMaps[indexLoadedMap]);
}



//===========================
//====== checkCollides ======
//===========================
// check if there is collision box at a certain coordinate
bool checkCollides(map_t map, int x, int y)
{
    // loop through all collision boxes on the map
    for (int i = 0; i < map.collisionCount; i++)
    {
        // LOGD("map: checking collision i=%d at x=%d y=%d\n", i, map.collisions[i].posX, map.collisions[i].posY);
        if (map.collisions[i].posX == x && map.collisions[i].posY == y)
            return true;
    }
    return false;
}



//===========================
//======= MAP PRESETS =======
//===========================
// stored map presets
// TODO add more maps or map generator
static const map_t map_default = {
    .width = 10,
    .height = 10,
    .name = "default",
    .collisions = {{8, 9}, {8, 8}, {4, 5}, {0, 1}},
    .collisionCount = 4,
    .portals = {
        {.posX = 5,
         .posY = 8,
         .targetX = 7,
         .targetY = 1,
         .color = "blue"}},
    .portalCount = 1};


static const map_t map_empty = {
    .width = 20,
    .height = 20,
    .name = "empty",
    .collisions = {},
    .collisionCount = 0,
    .portals = {
        {.posX = 5,
         .posY = 8,
         .targetX = 7,
         .targetY = 1,
         .color = "blue"}},
    .portalCount = 1};


static const map_t map_intermediate = {
    .width = 15,
    .height = 15,
    .name = "intermediate",
    .collisions = {{8, 9}, {8, 8}, {4, 6}, {0, 1}, {9, 9}, {7, 6}, {4, 0}, {3, 0}, {12, 11}, {14, 13}},
    .collisionCount = 10,
    .portals = {
        {.posX = 5,
         .posY = 8,
         .targetX = 13,
         .targetY = 2,
         .color = "blue"},
        {.posX = 2,
         .posY = 2,
         .targetX = 3,
         .targetY = 12,
         .color = "red"}},
    .portalCount = 2};

// global variables for accessing the stored maps
const map_t *storedMaps[16] = {&map_default, &map_empty, &map_intermediate};
const int storedMapsCount = 3;