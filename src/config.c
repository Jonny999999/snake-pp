#include "config.h"

//define global struct for configuration values
//default values defined here: (note: gets modified by map.c or menu.c)
config_t config = {
    .windowSize = 800,
    .blockSizePx = 800/10, //default map is 10x10 blocks
    .cycleDurationMs = CYCLE_DURATIONS_MS,
    .difficulty = 1,
    .snakeDefaultLength = 2,
    .leaderboardFilename = "player_scores.bin",
    //.defaultMapName = "default"      //10x10
    .defaultMapName = "intermediate" //15x15
    //.defaultMapName = "empty"        //20x10
};