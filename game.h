typedef enum gameState_t {PAUSED=0, MENU, RUNNING};

struct gameData_t{
    snake_t snake;
    int mapCollisions[int MAX_MAP_SIZE][int MAX_MAP_SIZE];        //Position der Wände
    int mapPortals [int MAX_MAP_SIZE][int MAX_MAP_SIZE];        //Position der Portale

    int foodX, foodY;       //Positon des Futters (es gibt immer nur 1 Futter)
    int lifesRemaining;         //implementieren wir nicht!!
    int timestampLastRun;
    bool isPaused;
    gameState_t gameState;
}

void gameInit();
//ruft snakeInit auf
//ruft place Food auf

void handleCollision();
//Überprüft, ob Snake mit Gegenstand/Wand kollidiert ist

void handlePortals();       //optional
//Prüft, ob Snake sich auf einem Portal befindet

void gameLoop();
//macht immer: handleKeyboardEvents();
//if TickDue: Snakemove(), TickTimerReset
//optional: ruft checkCollision auf
//ruft place food auf
//ruft checkEaten auf
//if checkEaten then snakeGrow
//ruft snakeMove auf

