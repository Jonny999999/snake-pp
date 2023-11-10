#pragma once
#include <stdbool.h>
#include "config.h"


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
    const char *name[128];
    collisionBox_t collisions[MAX_MAP_FIELDS];
    int collisionCount;
    portal_t portals[MAX_MAP_FIELDS];
    int portalCount;
} map_t;

//return true when provided coordinate matches a collision box
bool checkCollides(int x, int y);

//generate random map based on difficulty level
map_t generateMap(int difficulty);

//search and load map by name (if not found loads default map)
void loadMapByName(char *name);

//load map by passed definition
void loadMap(map_t map);

