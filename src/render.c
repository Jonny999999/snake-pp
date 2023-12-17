#include "render.h"
#include "SDL.h"
#include "game.h"
#include "snake.h"
#include "food.h"
#include "config.h"
#include "menu.h"
#include "common.h"
#include <stdio.h>



void renderGame(){
  SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
  SDL_RenderClear(game.renderer);

  SDL_Rect rect;    //Rechteck anlegen
  rect.w = config.blockSizePx;    //Breite festlegen
  rect.h = config.blockSizePx;    //Höhe festlegen

//_______Head kreieren__________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255);   //RGB-Farbe Kopf
  rect.x = (game.snake.headX * config.blockSizePx);   //Abstand links
  rect.y = (game.snake.headY * config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern


//______Tail kreieren_________________________________________________________________
  for(int i = 1; i<game.snake.length; i++){
    SDL_SetRenderDrawColor(game.renderer, 15, 179, 15, 255);   //RGB-Farbe Tail
    rect.x = (game.snake.tail[i][0] * config.blockSizePx);   //Abstand links
    rect.y = (game.snake.tail[i][1] * config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  }

//______Portal kreieren________________________________________________________________________
  for (int i = 0; i < game.map.portalCount; i++)
  {
    switch(i) {     //Farben je nach Start-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(game.renderer, 90, 150, 255, 255); break;   //Start: hellblau
      case 1: SDL_SetRenderDrawColor(game.renderer, 255, 150, 255, 255); break;      //Start: rosa
      default: SDL_SetRenderDrawColor(game.renderer, 255, 150, 150, 255); break;      //Start: hellrot
    }

    //Start-Portal
    rect.x = (game.map.portals[i].posX * config.blockSizePx);
    rect.y = (game.map.portals[i].posY * config.blockSizePx);

    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern

    switch(i) {   //Farben je nach Ausgangs-Portal-Nr.
      case 0: SDL_SetRenderDrawColor(game.renderer, 45, 45, 255, 255); break;   //Ausgang: dunkelblau
      case 1: SDL_SetRenderDrawColor(game.renderer, 204, 0, 204, 255); break;      //Ausgang: violett
      default: SDL_SetRenderDrawColor(game.renderer, 255, 50, 0, 255); break;      //Ausgang: rot
    }

    //Ausgangs-Portal
    rect.x = (game.map.portals[i].targetX * config.blockSizePx);
    rect.y = (game.map.portals[i].targetY * config.blockSizePx);

    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern
  }


//_______Food kreieren_________________________________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 255, 200, 0, 255);   //RGB-Farbe Food
  rect.x = (game.foodX*config.blockSizePx);   //Abstand links
  rect.y = (game.foodY* config.blockSizePx);   //Abstand rechts
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
   SDL_SetRenderDrawColor(game.renderer, 255, 140, 0, 255);   //RGB-Farbe Food Rahmen
     SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern



//______Collisions kreieren_________________________________________________________________________
  for(int i = 0; i < game.map.collisionCount; i++){
    SDL_SetRenderDrawColor(game.renderer, 112, 128, 144, 255);   //RGB-Farbe Wand
    rect.x = (game.map.collisions[i].posX*config.blockSizePx);   //Abstand links
    rect.y = (game.map.collisions[i].posY* config.blockSizePx);   //Abstand rechts
    SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
    SDL_SetRenderDrawColor(game.renderer, 80, 90, 100, 255);   //RGB-Farbe Wand-Rand
    SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern
  }

//_________________Augen___________________________________________________
  SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
  rect.w = config.blockSizePx/4;    //Breite festlegen
  rect.h = config.blockSizePx/4;    //Höhe festlegen
  if (game.snake.direction == LEFT || game.snake.direction == RIGHT){
  //oberes Auge  
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/2.5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  //unteres Auge
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/2.5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/1.7; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  
  } else {
  //linkes Auge  
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/5;
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/2.5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  //rechtes Auge
  rect.x = (game.snake.headX * config.blockSizePx) + config.blockSizePx/1.7;   //Abstand links
  rect.y = (game.snake.headY * config.blockSizePx) + config.blockSizePx/2.5; 
  SDL_RenderFillRect(game.renderer, &rect);    //Rechteck rendern
  }
  SDL_RenderDrawRect(game.renderer, &rect);    //Rechteck rendern

//______Fenster aktualisieren____________________________________________
  SDL_RenderPresent(game.renderer);    //Fenster aktualisieren

}



//--------------------------------------------------------------
//-----------------START MENU-----------------------------------
//--------------------------------------------------------------
void renderStartMenu()
{   
    //=========== only first loop ================
    if(ttlStorage.lastTimeStep == 0)
    {
        ttlStorage.ptrFont_200 = TTF_OpenFont("../fonts/Quirkus.ttf", ttlStorage.fontSize_200);
        ttlStorage.ptrFont_30 = TTF_OpenFont("../fonts/Quirkus.ttf", ttlStorage.fontSize_30);


        SDL_Color textColor1 = {255, 0, 255}; // rosa Text
        SDL_Color textColor2 = {255, 200, 0}; // oranger Text
        SDL_Color textColor3 = {0, 255, 0};   // grüner Text
        SDL_Color textColor4 = {255, 0, 0}; // rot Text
        SDL_Color textColor5 = {0, 255, 255};   // türkiser Text
        SDL_Color textColor6 = {255, 255, 255}; // weißer Text

        ttlStorage.textColour[0] = textColor1;    // rosa
        ttlStorage.textColour[1] = textColor2;    // orange
        ttlStorage.textColour[2] = textColor3;    // grün
        ttlStorage.textColour[3] = textColor4;    // rot
        ttlStorage.textColour[4] = textColor5;    // türkis
        ttlStorage.textColour[5] = textColor6;    // weiß
        
        // text in start screen
        const char* textLines[] = {
            "Snake++",
            "In Pixeln bunt, sie schlaengelt flink,",
            "Durch Mauern, Portale, ohne Blink.",
            "Starte das Spiel, sei klug und schnell,",
            "Die Schlange wartet, auf dein Pixel-Ziel!",
            "-- ENTER --"
        };


        // render game name (SNAKE++) bigger than poem 
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_200, textLines[0], ttlStorage.textColour[0]);
        ttlStorage.textTextures[0] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);

        // render poem
        for (int i = 1; i < (MAX_LINES_STARTSCREEN - 1); ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_30, textLines[i], ttlStorage.textColour[i]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
        }

        // render ENTER
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_30, textLines[MAX_LINES_STARTSCREEN-1], ttlStorage.textColour[5]);
        ttlStorage.textTextures[MAX_LINES_STARTSCREEN-1] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);
    }


    //=========== is always performerd ================
    SDL_RenderClear(game.renderer);

    int textWidth, textHeight;

    // print game name
    ttlStorage.textPrintPosition = (config.windowSize) / 9;   // print position for game name (SNAKE++)
    SDL_QueryTexture(ttlStorage.textTextures[0], NULL, NULL, &textWidth, &textHeight);
    SDL_Rect dstRect = { (config.windowSize - textWidth) / 2, ttlStorage.textPrintPosition, textWidth, textHeight };
    SDL_RenderCopy(game.renderer, ttlStorage.textTextures[0], NULL, &dstRect);
    
    // print poem    
    ttlStorage.textPrintPosition = (config.windowSize) / 2.7;     // change print position for poem
    for (int i = 1; i < (MAX_LINES_STARTSCREEN-1); ++i) {
        SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);

        SDL_Rect dstRect = { (config.windowSize - textWidth) / 2, ttlStorage.textPrintPosition, textWidth, textHeight };
        SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
        ttlStorage.textPrintPosition += textHeight;             // increase print position
    }        
    //print ENTER every second cycle
    if(ttlStorage.showEnter)
    {
      ttlStorage.textPrintPosition = (config.windowSize / 1.5);   // print position for ENTER
      SDL_QueryTexture(ttlStorage.textTextures[MAX_LINES_STARTSCREEN-1], NULL, NULL, &textWidth, &textHeight);
      SDL_Rect dstRect1 = { (config.windowSize - textWidth) / 2, ttlStorage.textPrintPosition, textWidth, textHeight };
      SDL_RenderCopy(game.renderer, ttlStorage.textTextures[MAX_LINES_STARTSCREEN-1], NULL, &dstRect1);
    }
    
    // update screen 
    SDL_RenderPresent(game.renderer);
    ttlStorage.lastTimeStep = GET_TIME_MS();

    return;
}


//--------------------------------------------------------------
//-------------------SETTINGS-----------------------------------
//--------------------------------------------------------------
void renderSettings()
{   
    int textWidth, textHeight;    // auxiliary variables for printing

    // text in menu settings
    static char* textLinesInMenu[MAX_LINES_SETTINGS] = {
        "Fuer Infos zum Gameplay, sowie einigen Shortcuts druecken Sie bitte F1",
        " ",
        " ",
        "Bitte geben Sie ihren Nickname ein: ",
        " ",
        " ",
        "Bitte geben Sie ein Schwierigkeitslevel ein:",
        "1 fuer Einfach  -  2 fuer Fortgeschritten  -  3 fuer Profi",
        " ",
        " ",
        "Bitte waehlen Sie eine Map:",
        "1 fuer Klein  -  2 fuer Mittel  -  3 fuer Gross",
        " ",
         "-- ENTER --"
    };


    //=========== only first loop ================
    if(ttlStorage.lastTimeStep == 0)
    {  
      printf("In first loop\n");
        ttlStorage.ptrFont_20 = TTF_OpenFont("../fonts/Prototype.ttf", ttlStorage.fontSize_20);
        SDL_StartTextInput();     // start text input
    }

    

    //=========dependent of which text is currently entered(userName, difficultyLevel, userSelectedMap) =========
    switch(ttlStorage.inputStatus)
    {
    //=== no user inputs ===
    case 0:
        //--- rendering ---
        for (int i = 0; i < 4; ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLinesInMenu[i], ttlStorage.textColour[5]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
            
        }
        
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, ttlStorage.textInput, ttlStorage.textColour[5]);        
        ttlStorage.textTextures[4] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);
        SDL_RenderClear(game.renderer);

        //--- printing ---
        ttlStorage.textPrintPosition = 0;    // first print position
        for (int i = 0; i < 5; ++i) 
        {
            SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);
            SDL_Rect dstRect = { 1, ttlStorage.textPrintPosition, textWidth, textHeight };
            SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
            ttlStorage.textPrintPosition += textHeight;             // increase print position
        }   
        break;


    // === one user input ===
    case 1:
        textLinesInMenu[4] = ttlStorage.userName;  
        //--- rendering ---
        for (int i = 0; i < 8; ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLinesInMenu[i], ttlStorage.textColour[5]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
            
        }
        
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, ttlStorage.textInput, ttlStorage.textColour[5]);        
        ttlStorage.textTextures[8] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);
        SDL_RenderClear(game.renderer);

        //---printing ---
        ttlStorage.textPrintPosition = 0;    // first print position
        for (int i = 0; i < 9; ++i) 
        {
            SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);
            SDL_Rect dstRect = { 1, ttlStorage.textPrintPosition, textWidth, textHeight };
            SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
            ttlStorage.textPrintPosition += textHeight;             // increase print position
        }   
        break;

    //=== two user inputs ===
    case 2:
        textLinesInMenu[8] = &(ttlStorage.userDifficultyLevel);  
        //--- rendering ---
        for (int i = 0; i < 12; ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLinesInMenu[i], ttlStorage.textColour[5]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
            
        }
        
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, ttlStorage.textInput, ttlStorage.textColour[5]);        
        ttlStorage.textTextures[12] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);
        SDL_RenderClear(game.renderer);

        //---printing ---
        ttlStorage.textPrintPosition = 0;    // first print position
        for (int i = 0; i < 13; ++i) 
        {
            SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);
            SDL_Rect dstRect = { 1, ttlStorage.textPrintPosition, textWidth, textHeight };
            SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
            ttlStorage.textPrintPosition += textHeight;             // increase print position
        }   
        break;

    //=== user inputs completely
    case 3:
        textLinesInMenu[12] = &(ttlStorage.userSelectedMap);  
        //--- rendering ---
        for (int i = 0; i < (MAX_LINES_SETTINGS - 1); ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLinesInMenu[i], ttlStorage.textColour[5]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
            
        }
        
        ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLinesInMenu[MAX_LINES_SETTINGS - 1], ttlStorage.textColour[5]);        
        ttlStorage.textTextures[MAX_LINES_SETTINGS - 1] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
        SDL_FreeSurface(ttlStorage.textSurface);
        SDL_RenderClear(game.renderer);

        //---printing ---
        ttlStorage.textPrintPosition = 0;    // first print position
        for (int i = 0; i < (MAX_LINES_SETTINGS - 1); ++i) 
        {
            SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);
            SDL_Rect dstRect = { 1, ttlStorage.textPrintPosition, textWidth, textHeight };
            SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
            ttlStorage.textPrintPosition += textHeight;             // increase print position
        }   

    //print ENTER every second cycle
        if(ttlStorage.showEnter)
        {
          ttlStorage.textPrintPosition = (config.windowSize / 1.5);   // print position for ENTER
          SDL_QueryTexture(ttlStorage.textTextures[MAX_LINES_SETTINGS-1], NULL, NULL, &textWidth, &textHeight);
          SDL_Rect dstRect1 = { (config.windowSize - textWidth) / 2, ttlStorage.textPrintPosition, textWidth, textHeight };
          SDL_RenderCopy(game.renderer, ttlStorage.textTextures[MAX_LINES_SETTINGS-1], NULL, &dstRect1);
        }  
        break;
    }

    // update screen
    SDL_RenderPresent(game.renderer);
    ttlStorage.lastTimeStep = GET_TIME_MS();

    return;
}

//--------------------------------------------------------------
//-------------------INFO SCREEN--------------------------------
//--------------------------------------------------------------
void renderInfoScreen()
{
    //=========== only first loop ================
    if(ttlStorage.lastTimeStep == 0)
    {
        // text in start screen
        const char* textLines[] = {
            "          STEUERUNG:     W (nach oben)",
            "                                  A  (nach links)",
            "                                  S  (nach unten)",
            "                                  D  (nach rechts) ",
            "                    oder:      Pfeiltasten ",
            " ",
            " ",
            "                  PAUSE:     p",
            "                     oder:     Leertaste",
            " ", 
            " ",            
            "SPIEL VERLASSEN:     q ",
            " ",
            " ",
            " ",
            "By Jonas Schoenberger, Johannes Graf und Julia Steinberger",
            "-- ENTER --"
        };
        
        
        // render setting screen
        for (int i = 0; i < MAX_LINES_INFOSCREEN; ++i) 
        {     
            ttlStorage.textSurface = TTF_RenderText_Solid(ttlStorage.ptrFont_20, textLines[i], ttlStorage.textColour[5]);        
            ttlStorage.textTextures[i] = SDL_CreateTextureFromSurface(game.renderer, ttlStorage.textSurface);
            SDL_FreeSurface(ttlStorage.textSurface);
        }
    }


    //=========== is always performerd ================
    SDL_RenderClear(game.renderer);

    int textWidth, textHeight;

    // print settings    
    ttlStorage.textPrintPosition = 0;    // first print position
    for (int i = 0; i < (MAX_LINES_INFOSCREEN - 1); ++i) {
        
        SDL_QueryTexture(ttlStorage.textTextures[i], NULL, NULL, &textWidth, &textHeight);

        SDL_Rect dstRect = { 1, ttlStorage.textPrintPosition, textWidth, textHeight };
        SDL_RenderCopy(game.renderer, ttlStorage.textTextures[i], NULL, &dstRect);
        ttlStorage.textPrintPosition += textHeight;             // increase print position
    }        

    //print ENTER every second cycle
    if(ttlStorage.showEnter)
    {
      ttlStorage.textPrintPosition = (config.windowSize / 1.5);   // print position for ENTER
      SDL_QueryTexture(ttlStorage.textTextures[MAX_LINES_INFOSCREEN-1], NULL, NULL, &textWidth, &textHeight);
      SDL_Rect dstRect1 = { (config.windowSize - textWidth) / 2, ttlStorage.textPrintPosition, textWidth, textHeight };
      SDL_RenderCopy(game.renderer, ttlStorage.textTextures[MAX_LINES_INFOSCREEN-1], NULL, &dstRect1);
    }


    // update screen 
    SDL_RenderPresent(game.renderer);
    ttlStorage.lastTimeStep = GET_TIME_MS();

    return;
}



int CreateSDLWindow(){
    // Erstelle ein SDL-Fenster
  game.window = SDL_CreateWindow("Snake", 350, 50, config.windowSize, config.windowSize, SDL_WINDOW_OPENGL);
    if (game.window == NULL) {
        printf("Fenster konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

  game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (game.renderer == NULL) {
        printf("Renderer konnte nicht erstellt werden! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
	}

void DestroySDLWindow(){
      // Zerstöre das Fenster und beende SDL

    TTF_CloseFont(ttlStorage.ptrFont_20);
    TTF_CloseFont(ttlStorage.ptrFont_30);
    TTF_CloseFont(ttlStorage.ptrFont_200);

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);

    TTF_Quit();
    SDL_Quit();
}

