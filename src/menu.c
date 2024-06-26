#include "menu.h"
#include "game.h"
#include "sound.h"
#include "common.h"
#include <stdio.h>
#include <math.h>
#include "render.h"



//define global struct for tllStorage values
//default values defined here: (note: gets modified by render.c or menu.c)
ttlData_t ttlStorage =
{   
    .fontSize_20 = 20,      // size of font
    .fontSize_30 = 30,      // size of font
    .fontSize_200 = 200,    // size of font
    .cycleDuration = 500,   // time between show and not showing ENTER in start screen
    .showEnter = false,
    .inputStatus = 0,
    .textInput[0] = '\0'


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
    LOGD("menu: showing start-screen\n");

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
    LOGD("menu: showing leaderboard\n");


    //--- play crash sound ---
    //play audio file, wait until playback is finished
    //note: when displaying actual leaderboard, the second parameter should be 'false' to not block the program
    
    time_t now =  GET_TIME_MS();

    // is used to make ENTER blink
    if(now > (ttlStorage.lastTimeStep + ttlStorage.cycleDuration))
    {   
        ttlStorage.showEnter = !ttlStorage.showEnter;       
        renderLeaderboard();
    }

    return;
}

void showPauseScreen()
{
    LOGD("menu: showing leaderboard\n");
    game.gameState = PAUSED;
    return;
}


void showSettings()
{
    LOGD("menu: showing settings\n");

    
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
    LOGD("menu: showing info-screen\n");

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
// delete text at the end of one menu section
void menuHandleInput(SDL_Event event){
    //compare 'handleInput_runningState(SDL_Event event)' in input.c

    int numberOfContents = 0;   // count number of entered numbers by the user 

    switch(activeMenu)
    {  
    // start
    case START:
        switch (event.key.keysym.sym)
        {
        case SDLK_q: // q: quit
            // game.gameState = EXIT;
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

    // settings
    case SETTINGS:
        switch(event.key.keysym.sym)
        {
        // case SDLK_q: // q: quit
        //     game.gameState = EXIT;
        //     break;

        case SDLK_F1:   // go to info screen
            activeMenu = INFOSCREEN;
            ttlStorage.lastTimeStep = 0;
            // delete text
            for (int i = 0; i < MAX_LINES_TFF; ++i) 
            {
                SDL_DestroyTexture(ttlStorage.textTextures[i]);
            }
            break;

        case SDLK_RETURN:    // confirm user input or start game

            switch(ttlStorage.inputStatus)
            {
            case 0:     // confirm user name
                // user must enter at least one letter
                if(ttlStorage.textInput[0] != '\0')
                {
                    ttlStorage.inputStatus++;
                    strcpy(ttlStorage.userName, ttlStorage.textInput);                  // copy textInput to userName
                    memset(ttlStorage.textInput, 0, sizeof(ttlStorage.textInput));      // clear textInput[]
                }
                break;

            case 1:     // confirm difficulty level
                // count number of entered numbers
                while (ttlStorage.textInput[numberOfContents] != '\0' && numberOfContents < sizeof(ttlStorage.textInput)) 
                {
                    numberOfContents++;
                }

                // user input must be between 1 and 3
                if((ttlStorage.textInput[0] > '0') && (ttlStorage.textInput[0]  <= '3') && numberOfContents == 1)      
                {   
                    ttlStorage.inputStatus++;
                    strcpy(ttlStorage.numbers[0], ttlStorage.textInput);               // copy textInput to userDifficultyLevel     
                    ttlStorage.userDifficultyLevel = ttlStorage.textInput[0] - '0';    // copy textInput to userDifficultyLevel
                }
                memset(ttlStorage.textInput, 0, sizeof(ttlStorage.textInput));      // clear textInput[]
                break;  

            case 2:     // confirm map
                // count number of entered numbers
                while (ttlStorage.textInput[numberOfContents] != '\0' && numberOfContents < sizeof(ttlStorage.textInput)) 
                {
                    numberOfContents++;
                }

                // user input must be between 1 and 3
                if((ttlStorage.textInput[0] > '0') && (ttlStorage.textInput[0]  <= '3') && numberOfContents == 1)      
                {   
                    ttlStorage.inputStatus++;
                    strcpy(ttlStorage.numbers[1], ttlStorage.textInput);               // copy textInput to userSelectedMap
                    ttlStorage.userSelectedMap = ttlStorage.textInput[0] - '0';        // copy textInput to userSelectedMap
                } 
                memset(ttlStorage.textInput, 0, sizeof(ttlStorage.textInput));      // clear textInput[]
                break;

            case 3:     // start game
                activeMenu = NONE;
                game.gameState = RUNNING;
                // delete text
                for (int i = 0; i < MAX_LINES_TFF; ++i) 
                {
                    SDL_DestroyTexture(ttlStorage.textTextures[i]);
                }  

                // initialize game
                LOGI("Schwierigkeitslevel: %d\n", ttlStorage.userDifficultyLevel);
                config.difficulty = ttlStorage.userDifficultyLevel;
                config.cycleDurationMs = CYCLE_DURATIONS_MS / sqrt(config.difficulty);
                
                gameInit();
          
                break;
            }
            break;
 

        default:   // for user inputs
            // keyboard input
            if (event.type == SDL_TEXTINPUT)
            {
                strcat(ttlStorage.textInput, event.text.text);
            }
            // delete single inputs via backspace
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(ttlStorage.textInput) > 0)
            {
                ttlStorage.textInput[strlen(ttlStorage.textInput) - 1] = '\0';
            }
            break;
        } 
        
        break;
    
    // info screen
    case INFOSCREEN:
        switch(event.key.keysym.sym)
        {
        case SDLK_q: // q: quit
            // game.gameState = EXIT;
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

    case LEADERBOARD:
        switch(event.key.keysym.sym)
        {
        case SDLK_q:       // q: quit
            // game.gameState = EXIT;  
            break;

        case SDLK_RETURN:   // go to first page
            game.gameState = MENU;
            activeMenu = START;
            ttlStorage.lastTimeStep = 0;
            ttlStorage.inputStatus = 0;
            ttlStorage.userDifficultyLevel = 0;
            ttlStorage.userSelectedMap = 0;
            game.mapIsLoaded = false;
            break;
        } 
        break;
    }
    
    return;
}

