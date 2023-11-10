#pragma once

void showStartScreen();
//zum Starten Enter drücken
//optional: "E" eingeben für Settings

void showLeaderboard();
//zeigt die besten Spieldurchläufe inkl. Punktestand an

void showSettings();     //optional
//startet Settungs-Menü

void menuHandleInput(int event);     //als Übergabeparameter: int(?) event -> welcher Datentyp hängt von SDL ab
//switch case für welcher Modus
//switch case für welche Taste gedrückt wurde
