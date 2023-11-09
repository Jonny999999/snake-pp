#pragma once

// global configuration macros
#define MAX_MAP_SIZE 10
#define MAX_PORTALS 5              // Maximalanzahl an Portale

// struct for storing game configuration
typedef struct config_t
{
  const int windowSize;            // feste Größe des Spielfensters
  int mapWidth;                    // =10     //Kartenbreite
  int mapHeight;                   // =10    //Kartenhöhe
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

