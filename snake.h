
typedef enum SnakeDirection{DOWN=0, UP, LEFT, RIGHT};       //Bewegungsrichtung

struct snake_t {
    int length;         //aktuelle Länge der Schlange
    int headX, headY;       //aktuelle Position der Schlange
    snakeDirection_t direction;
    int tail[512][2] ={0};
    bool isAlive;       //lebt die Schlange noch oder ist sie mit sich selbst kollidiert?
}

void snakeInit();
//Snake mit bestimmter Startlänge an Startposition erstellen
//Speicherbereich reservieren

void snakegrow();
//Snake wird um 1 Glied länger (nach Fressen)

void snakeMove();
//bewegt die Schlang einen Schritt in die aktuelle Richtung
//ruft lokale Variable dir von snakeSetDir auf

void snakeSetDir(enum dir);      //Richtung als Übergabeparameter
//definiert aktuelle Bewegungsrichtung der Schlange

bool snakeIsAlive();
//Überprüfen, ob Schlange noch lebt
//Prüft Kollision mit sich selbst

void snakeSetHeadPos();     //optional
//für handlePortals
//generiert zufällige Zielsposition, wohin sich die Schlange nach Betreten eines Portals bewegt