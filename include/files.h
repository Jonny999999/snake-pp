#pragma once
#include "config.h"

#define MAX_PRINTED_SCORES  5


// struct that store player score at the end of the game
typedef struct playerScore_t
{
    int score;
    char playerName[30];
    int difficulty;
    char map[30];
} playerScore_t;

// global struct for storing the 10 best players after reading it from the file (defined in files.c)
extern playerScore_t topScores[MAX_PRINTED_SCORES];

// function which saves score in a .bin file
void savePlayerScore(const char *filename);

// function which reads the 10 best finisher from the .bin file
void readTopScores(const char *filename);

// counts records in file
int countRecordsInFile(const char *filename); 