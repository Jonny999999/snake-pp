#pragma once

// global configuration macros
#define MAX_MAP_SIZE 10

// struct for storing game configuration
typedef struct config_t
{
  int mapWidth;                    // =10     //Kartenbreite
  int mapHeight;                   // =10    //Kartenhöhe
  int cycleDurationMs;             // ms between each game loop iterartion (game speed)
  int difficulty;                  // 0-3   //Schwierigkeitsgrad
  int snakeDefaultLength;          // = 2    //Länge der Schlange
  const char *leaderboardFilename; // Dateiname des Leaderboards
} config_t;

// global config struct defined in config.c
extern config_t config;
