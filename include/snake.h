#pragma once

#include <stdbool.h>
#include "config.h"

typedef enum snakeDirection_t
{
    DOWN = 0,
    UP,
    LEFT,
    RIGHT
} snakeDirection_t; // Bewegungsrichtung

typedef struct snake_t
{
    int length; // aktuelle Länge der Schlange
    int headX;
    int headY; // aktuelle Position der Schlange
    snakeDirection_t direction;
    int tail[MAX_MAP_SIZE*MAX_MAP_SIZE][2];
    bool isAlive; // lebt die Schlange noch oder ist sie mit sich selbst kollidiert?
} snake_t;

void snakeInit();
// Snake mit bestimmter Startlänge an Startposition erstellen

void snakeGrow();
// Snake wird um 1 Glied länger (nach Fressen)

void snakeMove();
// bewegt die Schlange einen Schritt in die aktuelle Richtung
// ruft lokale Variable dir von snakeSetDir auf

void snakeSetDir(snakeDirection_t dir); // Richtung als Übergabeparameter
// definiert aktuelle Bewegungsrichtung der Schlange

bool snakeIsAlive();
// Überprüfen, ob Schlange noch lebt
// Prüft Kollision mit sich selbst

void snakeSetHeadPos(); // optional
// für handlePortals
// generiert zufällige Zielsposition, wohin sich die Schlange nach Betreten eines Portals bewegt