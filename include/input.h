#pragma once

// checks for and processes queued SDL input events and passes them 
// to menu.c or controls snake depending on current game.gameState 
// => has to be run repeatedly from main()
void processInputEvent();