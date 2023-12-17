#pragma once
#include "config.h"

//----------------------------------------------------------------
// All functions/options regarding/affecting the difficulty level
//  -> collected in one file for easy adjustment
//----------------------------------------------------------------



// set parameters for food placement by current difficulty level
void difficulty_getFoodPlacementParam(float * minDist, float * maxDist);