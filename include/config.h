#pragma once

// global configuration macros
#define MAX_MAP_SIZE 10
#define MAX_MAP_FIELDS (MAX_MAP_SIZE*MAX_MAP_SIZE)
// logging settings
#define DEBUG_OUTPUT_ENABLED
#define INFO_OUTPUT_ENABLED

// struct for storing game configuration
typedef struct config_t
{
  const int windowSize;            // feste Größe des Spielfensters
  //Breite und Höhe sind gleich -> Spielfeld ist quadratisch
  int blockSizePx;                 // Pixelgröße von einem Block
  //wird über windowSize/mapHeight berechnet
  int cycleDurationMs;             // ms between each game loop iterartion (game speed)
  int difficulty;                  // 0-3   //Schwierigkeitsgrad
  int snakeDefaultLength;          // = 2    //Länge der Schlange
  const char *leaderboardFilename; // Dateiname des Leaderboards
} config_t;

// global config struct defined in config.c
extern config_t config;

