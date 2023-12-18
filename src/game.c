#include "game.h"
#include "map.h"
#include "common.h"
#include "menu.h"
#include "food.h"
#include "render.h"
#include "sound.h"
#include "files.h"


// global struct for storing all game data
// default values where needed:
gameData_t game = {
    .snake.length = 2,
    .foodX = 0,
    .foodY = 0,
    .mapIsLoaded = false,
    .lifesRemaining = 1,
    .timestampLastCycle = 0,
    .gameState = MENU,
};


// list of audio files randomly played when food eaten
const char *eatSounds[] = {
    "../sounds/eat-bite1.wav",
    "../sounds/eat-bite2.wav",
    "../sounds/eat-crunch1.wav",
    "../sounds/eat-crunch2.wav"};
#define EAT_SOUNDS_COUNT 4


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
    //----- load map -----
    //load default map if no map loaded yet
    if (!game.mapIsLoaded){
        //loadMapByName("default");

        //loadMapByName(config.defaultMapName);
        loadMap(*storedMaps[ttlStorage.userSelectedMap - 1]);
    }
    
    //----- snake -----
    // defines initial values of game.snake
    snakeInit(); //TODO assign return value to game.snake?

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
            //-- update head pos ---
            snakeSetHeadPos(p.targetX, p.targetY);
            LOGI("game: entered portal i=%d at x=%d, y=%d -> set head to x=%d y=%d\n", i, p.posX, p.posY, p.targetX, p.targetY);
            //--- play sound ---
            //playSoundAsync("../sounds/portal1_short.wav"); //too short
            //playSoundAsync("../sounds/portal2_oscillate.wav"); //too much bass
            //playSoundAsync("../sounds/space-gun.wav"); //too loud
            playSoundAsync("../sounds/portal3_in-out.wav");
            //playSoundAsync("../sounds/portal4_ramp.wav");
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
        // TODO consider game.lifesRemaining and reset if still good?
        //--- play crash sound ---
        LOGI("game: collided with wall or self! => show leaderboard\n");
        playSound("../sounds/crash_rock-cinematic.wav", false); 
        DELAY(200);
        //--- leaderboard ---
        //game.gameState = MENU; //TODO add config.collisionEnabled option?
        savePlayerScore("../build/player_scores.bin"/*(game.snake.length - config.snakeDefaultLength), ttlStorage.userName, config.difficulty, *storedMaps[ttlStorage.userSelectedMap - 1]*/);
        readTopScores("../build/player_scores.bin");
        game.gameState = MENU;
        activeMenu = LEADERBOARD;
        return;
    }

    //--- handle portals ---
    handlePortals();

    //--- handle food ---
    if (checkEaten()) {
        LOGI("game: picked up food at x=%d y=%d -> growing, placing food\n", game.foodX, game.foodY);
        //play eat sound (picks random file from above list)
        playSound(eatSounds[rand() % EAT_SOUNDS_COUNT], false);
        // NOTE: order of place and grow is relevant, otherwise function in food.c will access invalid memory
        placeFood(); 
        snakeGrow();
    }

    //--- update frame ---
    renderGame();
#ifdef RENDER_GAME_TO_CONSOLE
    printMap(game.map); //render game to console
#endif
    return;
}
