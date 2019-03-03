#ifndef _RANDOMGAME_H
#define _RANDOMGAME_H

#include "dominion.h"

int isIn(int, int[], int);
/* helper function used to check if an int is part of a DS */

int randomizeGame(int, struct gameState *state);
/* Used for generating a random game state */

void initializeKingCards(int, int*);
/* generate random set of kindom cards */

#endif
