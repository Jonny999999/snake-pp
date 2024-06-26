#pragma once

// global configuration macros
#define MAX_MAP_SIZE 20
#define MAX_MAP_FIELDS (MAX_MAP_SIZE*MAX_MAP_SIZE)
#define CYCLE_DURATIONS_MS 400

// logging settings
//#define DEBUG_OUTPUT_ENABLED
#define INFO_OUTPUT_ENABLED
#define ERROR_OUTPUT_ENABLED
//#define RENDER_GAME_TO_CONSOLE



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
  const char *defaultMapName;      // Name der map die initial geladen wird
} config_t;

// global config struct defined in config.c
extern config_t config;

