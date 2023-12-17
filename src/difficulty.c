#include "difficulty.h"

//----------------------------------------------------------------
// All functions/options regarding/affecting the difficulty level
//  -> collected in one file for easy adjustment
//----------------------------------------------------------------


//======================================
//== difficulty_getFoodPlacementParam ==
//======================================
// set parameters for food placement by current difficulty level
void difficulty_getFoodPlacementParam(float *minDist, float *maxDist)
{
    switch (config.difficulty)
    {
    default:
    case 0:
    case 1: //EASY/default: always place far away
        *minDist = 3.0; // new food has to be at least minDist blocks away from any object
        *maxDist = 5.0; // new food has to be closer than maxDist to an object
        break;
    case 2: //MEDIUM: place next to OR further away
        *minDist = 1.0;
        *maxDist = 4.0;
        break;
    case 3: //HARD: always place next to block
        *minDist = 1.0;
        *maxDist = 1.0;
        break;
    }
    return;
}
