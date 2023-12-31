#pragma once

#include <string.h>
#include "game.h"
#include "snake.h"
#include "menu.h"
#include "SDL.h"

void renderGame();
//erstellt aus Spielfeldstruktur die graphische Anzeige mit SDL-Framework

int CreateSDLWindow();

void DestroySDLWindow();

void renderStartMenu();

void renderSettings();

void renderInfoScreen();

void renderLeaderboard();