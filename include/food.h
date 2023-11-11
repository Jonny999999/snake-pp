#pragma once

#include <stdbool.h>

//function that spawns food respecting the following rules:
// - not at Collision, Snake-tail, Snake-head, portal-in, portal-out position (objects)
// - not closer to an object than minDist (if possible)
// - not further from an object than maxDist (if possible)
// maxDist and minDist are currently defined in food.c
void placeFood();


//function that returns true when snake head is at current food position
bool checkEaten();


// indefinitely spawn food and print the map to console until the program is killed
// for testing and adjusting the food placement algorithm
void startFoodPlacementTest();