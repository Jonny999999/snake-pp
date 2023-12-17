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
    .fontSize_20 = 20,      // size of font
    .fontSize_30 = 30,      // size of font
    .fontSize_200 = 200,    // size of font
    .cycleDuration = 500,   // time between show and not showing ENTER in start screen
    .showEnter = false
};   

// Default
menus_t activeMenu = START;

// is called by main function if  game.gameState == MENU
// choose between the selected menu functions
void manageMenu()
{
    switch(activeMenu)
    {
        case START:
            showStartScreen();
            break;
        
        case SETTINGS:
            showSettings();
            break;
        
        case INFOSCREEN:
            showInfoScreen();
            break;
        
        case LEADERBOARD:
            showLeaderboard();
            break;
        
        case PAUSE:
            showPauseScreen();
            break;
    }
}


// shows start screen with blinking ENTER
void showStartScreen()
{
    LOGI("menu: showing start-screen\n");

    time_t now =  GET_TIME_MS();

    // is used to make ENTER blink
    if(now > (ttlStorage.lastTimeStep + ttlStorage.cycleDuration))
    {   
        ttlStorage.showEnter = !ttlStorage.showEnter;       
        renderStartMenu();
    }
    return;
}


void showLeaderboard()
{
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

void showPauseScreen()
{
    LOGI("menu: showing leaderboard\n");
    game.gameState = PAUSED;
    return;
}


void showSettings()
{
    LOGI("menu: showing settings\n");

    
    time_t now =  GET_TIME_MS();

    // is used to make ENTER blink
    if(now > (ttlStorage.lastTimeStep + ttlStorage.cycleDuration))
    {   
        ttlStorage.showEnter = !ttlStorage.showEnter;       
        renderSettings();
    }

    return;
}


void showInfoScreen()
{   
    LOGI("menu: showing info-screen\n");

    time_t now =  GET_TIME_MS();

    // is used to make ENTER blink
    if(now > (ttlStorage.lastTimeStep + ttlStorage.cycleDuration))
    {   
        ttlStorage.showEnter = !ttlStorage.showEnter;       
        renderInfoScreen();
    }
    
    return;
}

// handle input over keyboard
// delete text at the and of one menu section
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
            activeMenu = SETTINGS;
            ttlStorage.lastTimeStep = 0;
            // delete text
            for (int i = 0; i < MAX_LINES_TFF; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }
        }
        break;

        
    case SETTINGS:
        switch(event.key.keysym.sym)
        {
        case SDLK_q: // q: quit
            game.gameState = EXIT;
            break;

        case SDLK_F1:   // go to info screen
            activeMenu = INFOSCREEN;
            ttlStorage.lastTimeStep = 0;
            // delete text
            for (int i = 0; i < MAX_LINES_TFF; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }
            break;

        case SDLK_RETURN:    //start game
            activeMenu = NONE;
            game.gameState = RUNNING;
            // delete text
            for (int i = 0; i < MAX_LINES_TFF; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }  
            break;
        } 
        
        break;
    
    case INFOSCREEN:
        switch(event.key.keysym.sym)
        {
        case SDLK_q: // q: quit
            game.gameState = EXIT;
            break;

        case SDLK_RETURN:   // go return to settings
            activeMenu = SETTINGS;
            ttlStorage.lastTimeStep = 0;
            // delete text
            for (int i = 0; i < MAX_LINES_TFF; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }  
        } 
        break;
    }
    

    return;
}

