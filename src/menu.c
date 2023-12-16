#include "menu.h"
#include "game.h"
#include "sound.h"
#include "common.h"
#include <stdio.h>
//#include <Windows.h>



//define global struct for tllStorage values
//default values defined here: (note: gets modified by render.c or menu.c)
ttlData_t ttlStorage =
{
    .fontSize_30 = 30,
    .fontSize_200 = 200,
    .lastTimeStep = 0,
    .cycleDuration = 500,
    .showEnter = false
};   

// Default
menus_t activeMenu = START;

// is called by main function
// choose between the selected menu-rendering functions
void manageMenu()
{
    switch(activeMenu)
    {
        case START:
            showStartScreen();
            break;
    }
}


void showStartScreen()
{
    LOGI("menu: showing start-screen\n");
    time_t now =  GET_TIME_MS();
    if(now > (ttlStorage.lastTimeStep + ttlStorage.cycleDuration))
    {   
        ttlStorage.showEnter = !ttlStorage.showEnter;       // is used to make ENTER blink
        renderStartMenu();
    }

    //------------------------------------------------------------------------------------

    return;
}




void showLeaderboard(){
    LOGI("menu: showing leaderboard\n");

    //--- play crash sound ---
    //play audio file, wait until playback is finished
    //note: when displaying actual leaderboard, the second parameter should be 'false' to not block the program
    playSound("../sounds/crash_rock-cinematic.wav", true); 
    DELAY(100);

    //--- quit game ---
    game.gameState = EXIT;
    return;
}

void showPauseScreen(){
    LOGI("menu: showing leaderboard\n");
    game.gameState = PAUSED;
    return;
}

void showSettings(){
    LOGI("menu: showing settings\n");
    return;
}

void menuHandleInput(SDL_Event event){
    //compare 'handleInput_runningState(SDL_Event event)' in input.c
    switch(activeMenu)
    {
    case START:
        switch (event.key.keysym.sym)
        {
        case SDLK_q: // q: quit
            game.gameState = EXIT;
            break;

        case SDLK_RETURN:   // Enter key  
            game.gameState = RUNNING;
            activeMenu = NONE;
            // delete text
            for (int i = 0; i < 5; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }
        }
        break;

        
    case SETTINGS:
        break;
    }
        
    return;
}

