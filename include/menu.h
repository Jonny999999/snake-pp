#pragma once

#include <stdbool.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "common.h"

#define MAX_COLOURS 10
#define MAX_LINES_TFF 20                //max lines (of ttf) for the whole project
#define MAX_LINES_STARTSCREEN 6   
#define MAX_LINES_SETTINGS 7
#define MAX_LINE_INFOSCREEN 17
#define TIME_BETWEEN_UPDATE_MENU 1000   // [ms] 

// Enum that defines the active menu
typedef enum menus_t 
{
    NONE = 0, 
    START, 
    SETTINGS, 
    INFOSCREEN,
    LEADERBOARD, 
    PAUSE
} menus_t;

// Struct that include pointer for ttl-functions in menu.c and render.c
typedef struct tllData_t
{   
    TTF_Font *ptrFont_20;
    TTF_Font *ptrFont_30;             // used by menu.c and render.c
    TTF_Font *ptrFont_200;             // used by menu.c and render.c
    SDL_Surface *textSurface;     // used by menu.c and render.c
    SDL_Texture *textTexture;     // used by menu.c and render.c
    SDL_Texture *textTextures[MAX_LINES_TFF];
    SDL_Color textColour[MAX_COLOURS];            // colour in which the text is printed
    const int fontSize_20;
    const int fontSize_30;
    const int fontSize_200;
    int64_t lastTimeStep;
    int lineHeight;            // to print text in middle
    int totalHeight;           // to print text in middle
    int textPrintPosition;     // where first line is printed
    const time_t cycleDuration;
    bool showEnter;
} ttlData_t;    

extern ttlData_t ttlStorage;

extern menus_t activeMenu;

// edit various menus
// is called up in main.cpp
void manageMenu();



void showStartScreen();
//zum Starten Enter drücken
//optional: "E" eingeben für Settings

void showPauseScreen();

void showLeaderboard();
//zeigt die besten Spieldurchläufe inkl. Punktestand an

void showSettings();     //optional
//startet Settungs-Menü


// show info screen
void showInfoScreen();

void menuHandleInput(SDL_Event event);     //als Übergabeparameter: int(?) event -> welcher Datentyp hängt von SDL ab
//switch case für welcher Modus
//switch case für welche Taste gedrückt wurde


