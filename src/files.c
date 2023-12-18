#include "game.h"
#include "menu.h"
#include "files.h"



//global struct for storing all data of the 10 best players
playerScore_t topScores[];



//==========================
//==== savePlayerScores ====
//==========================
 void savePlayerScore(const char *filename/*int score, int difficulty, const char *playerName,  const char *map*/) 
 {   
    playerScore_t playerScore;

    // copy data into struct
    playerScore.score = game.snake.length - config.snakeDefaultLength;
    playerScore.difficulty = config.difficulty;
    strcpy(playerScore.playerName, ttlStorage.userName);
    //strcpy(playerScore.map, "testmap");
    
    strcpy(playerScore.map, storedMaps[ttlStorage.userSelectedMap - 1]->name);
    

    FILE *file;
    // open file
    file = fopen(filename, "ab");

    // write data in file
    if (file != NULL) 
    {
        fwrite(&playerScore, sizeof(playerScore_t), 1, file);
        fclose(file);

        LOGI("Spielergebnis wurde erfolgreich in die Binaerdatei gespeichert.\n");
    } 
    else 
    {
        LOGI("Fehler beim Öffnen der Datei!\n");
    }
}


//==========================
//==== readTopScores ======
//==========================
// number of reads depends on  'MAX_PRINTED_SCORES'
void readTopScores(const char *filename)
{
    FILE *filePtr;
    playerScore_t tempPlayerScore;
    int recordsInFile;
    int highestPlayerScore;
    int count = 0;              // increase up to 'MAX_PRINTED_SCORES'

    // determine the number of contents in the file
    recordsInFile = countRecordsInFile(filename);
    // if failure
    if(recordsInFile == -1)
    {
        game.gameState = EXIT;
        return;
    }

    filePtr = fopen(filename, "rb");

    // fail with file opening
    if (filePtr == NULL) 
    {
        LOGI("Datei:  Fehler beim Öffnen der Datei für die besten 10 Ergebnisse!\n");
        game.gameState = EXIT;
        return;
    }
    

    LOGI("Datensaetze in Datei: %d\n", recordsInFile);


    //---- search for the highest score------
    for (int i = 0; i < recordsInFile; i++) 
    {
        fread(&tempPlayerScore, sizeof(playerScore_t), 1, filePtr);
        if(tempPlayerScore.score > highestPlayerScore)
        {
            highestPlayerScore == tempPlayerScore.score;
        }
    }
    
    //--- decrease highest score -----
    while((count < MAX_PRINTED_SCORES) && (count < MAX_PRINTED_SCORES))
    {   
        // set file pointer to start of the file
        rewind(filePtr);    

        // search for the highest score and then save it in topScores
        for (int i = 0; i < recordsInFile; i++) 
        {   
            fread(&tempPlayerScore, sizeof(playerScore_t), 1, filePtr);

            // current highscore found
            if(tempPlayerScore.score == highestPlayerScore)    
            {
                topScores[count] = tempPlayerScore;
                LOGI("score: %d  name: %s  schwierigkeit: %d  map: %s\n", topScores[count].score, topScores[count].playerName, topScores[count].difficulty, topScores[count].map); 
                count++;
            }

            // leave if MAX_PRINTED_SCORES is reached
            if(count >= MAX_PRINTED_SCORES)
            {
                break;
            }
        }
        highestPlayerScore--;
    }

    fclose(filePtr);
}



//==========================
//==== readTop10Scores =====
//==========================
// return the number of various scores of the file
int countRecordsInFile(const char *filename) 
{
    FILE *file;
    file = fopen(filename, "rb");

    // failure
    if (file == NULL) 
    {
        LOGI("Datei: Fehler beim Öffnen der Datei!\n");
        return -1; 
    }

    fseek(file, 0, SEEK_END);    // Gehe zum Dateiende
    long fileSize = ftell(file); // Hole die Größe der Datei in Bytes
    fclose(file);

    int recordSize = sizeof(playerScore_t);
    int numberOfRecords = fileSize / recordSize; // Berechne die Anzahl der Datensätze

    return numberOfRecords;
}
