#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "food.h"
#include "common.h"
#include "map.h"
#include "game.h"



//--------------------------------------------
//----- getRandomPositionWithMinDistance -----
//--------------------------------------------
// local function used in placeFood that returns random coordinates that have 
// at least in_minDist blocks distance to every Collision, portal and snake block on the current map.
void getRandomPositionWithMinDistance(int *outX, int *outY, float *out_minDist, int *out_triesNeeded, float in_minDist)
{
    //--- config ---
    static const int maxTries = 50; // each maxTries the limits above get loosened

    //--- get game frame ---
    // get 2d array containing position of all objects of current game state
    int gameFrame[MAX_MAP_SIZE][MAX_MAP_SIZE] = {{0}};
    renderGameToArray(gameFrame, game.map, game.snake);
    int foodX, foodY;

    //--- search random location ---
    // search random location for food that is within the defined min distance
    int tries = 0;
    //stores distance to closest block for return value
    float minActualDistance = MAX_MAP_SIZE;
newValues:
    while (1)
    {
        // generate random coodinates within map range
        foodX = rand() % game.map.width;
        foodY = rand() % game.map.height;
        tries++;
        // loop through all coordinates of current game/map
        for (int y = 0; y < game.map.height; y++)
        {
            for (int x = 0; x < game.map.width; x++)
            {
                if (gameFrame[y][x] > 0) // any object is present
                {
                    // calculate from random-coordinate to current block
                    float dist = sqrt(pow(foodX - x, 2) + pow(foodY - y, 2));
                    // save minimum distance
                    if (dist < minActualDistance) minActualDistance = dist;
                    // verify minimum distance is kept
                    if (dist < in_minDist) //too close
                    {
                        LOGD("food: distance: min=%.1f now=%.1f => placed too close => reroll...\n", in_minDist, dist);
                        // prevent deadlock if no suitable position exists - loosen limits every k*maxTries
                        if (tries % maxTries == 0)
                        {
                            //decrease min distance but not below 1
                            if ((in_minDist -= 0.1) < 1) in_minDist = 1;
                            LOGI("[WARN] food: too much tries achieving min dist -> loosen limit to %.1f\n", in_minDist);
                        }
                        //reset stored distance and reroll coordinates
                        minActualDistance = MAX_MAP_SIZE;
                        goto newValues;
                    }
                }
            }
        }
        //success: no block closer than minDist to randomly generated coordinates -> break loop
        break;
    }
    // return variables
    *out_minDist = minActualDistance;
    *outX = foodX;
    *outY = foodY;
    *out_triesNeeded = tries;
}



//=========================
//======= placeFood =======
//=========================
//function that spawns food respecting the following rules:
// - not at Collision, Snake-tail, Snake-head, portal-in, portal-out position (objects)
// - not closer to an object than minDist (if possible)
// - not further from an object than maxDist (if possible)
void placeFood()
{
    //--- config ---
    static const float minDist = 3; // new food has to be at least minDist blocks away from any object
    float maxDist = 5; // new food has to be closer than maxDist to an object
    static const int maxTries = 25; // each maxTries the limit maxDist get loosened (prevents deadlock)
    // TODO calculate this range using configured difficulty level
    // e.g. in hard difficulty the maxDist could be <2 so it is always placed close to a collision

    //--- variables ---
    int foodX, foodY, triesMax = 0, triesMin;
    float currentMinDist;

    //--- generate random food position within min/max range ---
    LOGD("food: generating random position + verifying min/max distance...\n");
    do
    {
        // prevent deadlock when position respecting maxDist not found
        triesMax++;
        if (triesMax % maxTries == 0)
        {
            maxDist += 0.1;
            LOGI("[WARN] food: too many tries for MAX_DIST -> loosen limits to max=%.1f\n", maxDist);
        }
        // generate random coordinates respecting minimum distance to objects
        getRandomPositionWithMinDistance(&foodX, &foodY, &currentMinDist, &triesMin, minDist);
        //restart when max distance limit exceeded
    } while (currentMinDist > maxDist);

    //--- update position ---
    LOGI("food: placed food at x=%d, y=%d (took %d = %d*%d tries)\n", foodX, foodY, triesMax * triesMin, triesMax, triesMin);
    game.foodX = foodX;
    game.foodY = foodY;
    return;
}



//=============================
//===== foodPlacementTest =====
//=============================
// indefinitely spawn food and print the map to console until the program is killed
// for testing and adjusting the food placement algorithm
void startFoodPlacementTest()
{
    while (1)
    {
        loadMapByName("default");
        placeFood();
        printMap(game.map);
        DELAY(100);
    }
}



//==========================
//======= checkEaten =======
//==========================
//returns true when snake head is at current food position
bool checkEaten()
{
    return (game.snake.headX == game.foodX && game.snake.headY == game.foodY);
}
