#include <math.h>
#include "render.h"
#include "input.h"
#include "common.h"
#include "SDL.h"
#include "game.h"
#include "menu.h"
#include "snake.h"
#include "map.h"



//--------------------------------
//--- handleInput_runningState ---
//--------------------------------
// local function that handles keyboard input when in RUNNING gameState
// - control snake via WASD or arrow-keys
// - quit with q
// - pause with p
void handleInput_runningState(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_q: // q: quit
        game.gameState = EXIT;
        break;

    case SDLK_p: // p: pause
    case SDLK_ESCAPE:
    case SDLK_SPACE:
        if(game.gameState == RUNNING)
        {
            game.gameState = PAUSED;
            showPauseScreen();
        }

        break;

        //--- control snake direction ---
    case SDLK_UP:
    case SDLK_w:
        snakeSetDir(UP);
        break;

    case SDLK_DOWN:
    case SDLK_s:
        snakeSetDir(DOWN);
        break;

    case SDLK_LEFT:
    case SDLK_a:
        snakeSetDir(LEFT);
        break;

    case SDLK_RIGHT:
    case SDLK_d:
        snakeSetDir(RIGHT);
        break;

    // case SDLK_m: // m: cycle through maps
    //     rotateMapNext();
    //     break;

    // case SDLK_2: // 2: speed up game by increment
    //     config.cycleDurationMs -= sqrt(config.cycleDurationMs) + 1;
    //     if (config.cycleDurationMs < 20)
    //         config.cycleDurationMs = 20;
    //     break;

    // case SDLK_1: // 1: slow down game by increment
    //     config.cycleDurationMs += 50;
    //     break;

    default:
        LOGD("input: key %d is not handled in RUNNING mode\n", event.key.keysym.sym);
    }
    return;
}

//=============================
//===== processInputEvent =====
//=============================
// checks for and processes queued SDL input events and passes them 
// to menu.c or controls snake depending on current game.gameState 
// => has to be run repeatedly from main()
void processInputEvent()
{
    SDL_Event event;

    // loop through all queued input events that occoured since last run
    while (SDL_PollEvent(&event))
    {
        // LOGD("event: %d detected", event.type);
        //--- quit event ---
        if (event.type == SDL_QUIT)
        {
            game.gameState = EXIT;
            return;
        }
        //--- key pressed ---
        // TODO also send mouse-events to menu?
        else if (event.type == SDL_KEYDOWN)
        {
            //LOGD("keydown event key=%d\n", event.key.keysym.sym);
            // run functions that handle the input depending on game.state
            switch (game.gameState)
            {
            case RUNNING:
                // control snake with keys (function above)
                handleInput_runningState(event);
                break;
            case PAUSED:
                game.gameState = RUNNING;
            case MENU:
                // pass key event to menu handle function which updates menu
                menuHandleInput(event);
                break;
            }
        }
        //--- key text input ---
        // not possible to make this check in the else if query before
        else if(event.type == SDL_TEXTINPUT && game.gameState == MENU)
        {
            menuHandleInput(event);
        }
    }

    return;
}