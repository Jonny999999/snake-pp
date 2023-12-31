#include "snake.h"
#include "game.h"   //for access to global 'game' struct

bool snakeSetDirectionIsAllowed = true;

void snakeInit()
{
    
    //-----------------------------------
    //-------------Default---------------
    //-----------------------------------

    // length 
    config.snakeDefaultLength = 2;                   // inkl head
    game.snake.length = config.snakeDefaultLength;

    // coordinates of head
    game.snake.headX = game.map.width / 2; 
    game.snake.headY = game.map.height / 2;

    // movement direction
    game.snake.direction = 3;    // left

    // coordinates of tail
    game.snake.tail[0][0] = game.snake.headX;   // X-coordinate
    game.snake.tail[0][1] = game.snake.headY;   // Y-coordinate
    game.snake.tail[1][0] = game.snake.headX - 1;   // X-coordinate
    game.snake.tail[1][1] = game.snake.headY - 1;   // Y-coordinate

    // alive 
    game.snake.isAlive = true;
    return;
}

void snakeGrow()
{
    game.snake.length++;
    // tail part is attached left of last tail part
    // maybe problem while rendering --> MUST BE SOLVED THEN
    game.snake.tail[game.snake.length - 1][0] = game.snake.tail[game.snake.length - 2][0];
    game.snake.tail[game.snake.length - 1][1] = game.snake.tail[game.snake.length - 2][1];
    return;
}

void snakeMove()
{   
    int i = game.snake.length - 1;  // counter for snake moving
    
    snakeSetDirectionIsAllowed = true;   // direction can be changed now

    // update head position automatically
    snakeUpdateHeadPos();

    // tail part of[x,y][0,1] get coordinates of tail part before
    while(i)
    {
        game.snake.tail[i][0] = game.snake.tail[i-1][0];        
        game.snake.tail[i][1] = game.snake.tail[i-1][1];
        i--;
    }
    game.snake.tail[0][0] = game.snake.headX;
    game.snake.tail[0][1] = game.snake.headY;

    return;
}

void snakeSetDir(snakeDirection_t dir)
{   
    // if direction mustn changed
    if(!snakeSetDirectionIsAllowed)
    {
        return;
    }

    // check, if snake should be move in opposite direction -> new direction stays old direction
    switch(dir)
    {
        case DOWN:
            if(game.snake.direction == UP)
                return;
            else    
                break;

        case UP:
            if(game.snake.direction == DOWN)
                return;
            else    
                break;

        case LEFT:
            if(game.snake.direction == RIGHT)
                return;
            else    
                break;

        case RIGHT:
            if(game.snake.direction == LEFT)
                return;
            else    
                break;

    }
    game.snake.direction = dir;
    snakeSetDirectionIsAllowed = false;     // direction cannot updated until next snakeMove
    return;
}

bool snakeIsAlive()
{
    for(int i = 1; i < game.snake.length; i++)
    {
        if(game.snake.tail[i][0] == game.snake.headX && game.snake.tail[i][1] == game.snake.headY)
            return false;
    }
    return true;
}

void snakeSetHeadPos(int xPos, int yPos)
{
    game.snake.headX = xPos;
    game.snake.headY = yPos;
    game.snake.tail[0][0] = xPos;
    game.snake.tail[0][1] = yPos;
    return;
}


void snakeUpdateHeadPos()
{
    switch(game.snake.direction)
    {   
        // DOWN
        case DOWN:
            game.snake.headX = game.snake.tail[0][0];
            game.snake.headY = game.snake.tail[0][1] + 1;
            if(game.snake.headY >= game.map.height) 
                game.snake.headY = 0;
            break;

        // UP
        case UP:
            game.snake.headX = game.snake.tail[0][0];
            game.snake.headY = game.snake.tail[0][1] - 1;
            if(game.snake.headY < 0)
                game.snake.headY = game.map.height - 1;
            break;

        // LEFT
        case LEFT:
            game.snake.headX = game.snake.tail[0][0] - 1;
            game.snake.headY = game.snake.tail[0][1];
            if(game.snake.headX < 0)
                game.snake.headX = game.map.width - 1;
            break;

        // RIGHT
        case RIGHT:
            game.snake.headX = game.snake.tail[0][0] + 1;
            game.snake.headY = game.snake.tail[0][1];
            if(game.snake.headX >= game.map.width) 
                game.snake.headX = 0;
            break;
    }
    return;
}