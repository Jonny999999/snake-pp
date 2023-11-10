#pragma once
#include <stdbool.h>

void placeFood();
// platziert zufällig (mit bestimmtem Algorithmus) Fressen auf dem Spielfeld
// darf nicht auf der Schlange oder auf Wänden sein

bool checkEaten();
// Überprüft, ob Snake gefressen hat -> true wenn gefressen
// Vergleich mit gameData_t foodX, foodY