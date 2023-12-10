#include "game.h"
#include "map.h"
#include "common.h"
#include "menu.h"
#include "food.h"
#include "render.h"


// global struct for storing all game data
// default values where needed:
gameData_t game = {
    .snake.length = 2,
    .foodX = 0,
    .foodY = 0,
    .mapIsLoaded = false,
    .lifesRemaining = 1,
    .timestampLastCycle = 0,
    .gameState = RUNNING,
};



//========================
//======= gameInit =======
//========================
// run once at game start and does the following:
// - init snake
// - load map
// - place initial food
void gameInit()
{
    LOGI("game: initializing game...\n");
    //----- snake -----
    // defines initial values of game.snake
    snakeInit(); //TODO assign return value to game.snake?

    //----- load map -----
    //load default map if no map loaded yet
    if (!game.mapIsLoaded){
        //loadMapByName("default");
        loadMapByName(config.defaultMapName);
    }
    
    //--- place initial food ---
    placeFood();
    LOGI("game: placed initial food at x=%d, y=%d\n", game.foodX, game.foodY);
}



//=========================
//===== handlePortals =====
//=========================
// when snake head is on a portal-input, sets snake head to portal-target
void handlePortals()
{
    LOGD("game: handling portals...\n");
    // loop through all existin portals in current map (game.map)
    for (int i=0; i < game.map.portalCount; i++){
        portal_t p = game.map.portals[i]; //copy curren portal (code more readable)
        // is at portal
        if (game.snake.headX == p.posX && game.snake.headY == p.posY){
            snakeSetHeadPos(p.targetX, p.targetY);
            LOGI("game: entered portal i=%d at x=%d, y=%d -> set head to x=%d y=%d\n", i, p.posX, p.posY, p.targetX, p.targetY);
            return;
        }
    }
    // snake not on any portal
    return;
}



//==========================
//====== runGameCycle ======
//==========================
// function that is repeatedly run at every game tick
// - moves snake to next position
// - handles collision, portals, food
// - triggers frame update (render.c)
void runGameCycle()
{
    LOGD("game: starting GameCycle %d\n", game.timestampLastCycle);

    //--- move snake ---
    // move snake to next position
    snakeMove();

    //--- handle collision ---
    //collision with map object or snake tail
    if (checkCollides(game.map, game.snake.headX, game.snake.headY) || !snakeIsAlive()){
        // show leaderboard when collided
        // TODO consider game.lifesRemaining and reset if still good?
        LOGI("game: collided with wall or self! => show leaderboard\n");
        LOGI("DEBUG: collision currently disabled, game will continue in 1s...\n");
        DELAY(1000);
        //game.gameState = MENU; //TODO add config.collisionEnabled option?
        //showLeaderboard();
        return;
    }

    //--- handle portals ---
    handlePortals();

    //--- handle food ---
    if (checkEaten()) {
        LOGI("game: picked up food at x=%d y=%d -> growing, placing food\n", game.foodX, game.foodY);
        // NOTE: order of place and grow is relevant, otherwise function in food.c will access invalid memory
        placeFood(); 
        snakeGrow();
}

    //--- update frame ---
    renderGame();
    printMap(game.map); //render game to console
    return;
}