  struct config_t{
    int mapWidth;  // =10     //Kartenbreite
    int mapHeight;    // =10    //Kartenhöhe
    int cycleDurationMs; //ms between each game loop iterartion (game speed)
    int difficulty; //0-3   //Schwierigkeitsgrad
    int snakeDefaultLength;   // = 2    //Länge der Schlange
    const char *leaderboardFilename;    //Dateiname des Leaderboards
  }
