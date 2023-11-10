#include "map.h"
#include "game.h"

// generate random map based on difficulty level
map_t generateMap(int difficulty)
{
    map_t newMap;
    return newMap;
    // TODO add map generator
}

// search and load map by name (if not found loads default map)
void loadMapByName(char *name)
{
    return;
    // TODO add map presets
}

// load map by passed definition
void loadMap(map_t map)
{
    game.map = map;
    game.mapIsLoaded = true;
    return;
}

// check if there is collision at certain coordinate
bool checkCollides(int x, int y)
{
    // loop through all collision boxes on the map
    for (int i = 0; i < game.map.collisionCount; i++)
    {
        // return true if match found
        if (game.map.collisions[i].posX == x && game.map.collisions[i].posY == y)
            return true;
    }
    return false;
}


//TODO add map presets here: