#include "game.h"
#include "map.h"

// global struct for storing all game data
gameData_t game;

//========================
//======= gameInit =======
//========================
void gameInit()
{
    //----- snake -----
    // defines initial values of game.snake
    // snakeInit(); FIXME: uncomment when implemented

    //----- load map -----
    //load default map if no map loaded yet
    if (!game.mapIsLoaded){
        char * defaultName = "default";
        loadMapByName("default");
    }
    // place initial food
    //placeFood(); FIXME uncomment when implemented

    //----- initialize variables -----
    game.lifesRemaining = 1;
    // game.lifesRemaining = config.maxLifes; TODO: add maxLifes to config
    // game.gameState = RUNNING; ??

    game.timestampLastCycle = -config.cycleDurationMs; // next cycle starts immediately
}

//=========================
//===== handlePortals =====
//=========================
void handlePortals()
{
    return;
}

//==========================
//====== runGameCycle ======
//==========================
void runGameCycle()
{
    if (checkCollides(game.snake.headX, game.snake.headY))
        return;
    return;
}