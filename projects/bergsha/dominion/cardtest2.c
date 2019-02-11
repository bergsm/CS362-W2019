#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define asserttrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

#define TESTCARD "smithy"

// smithy card test
void cardtest2()
{
	struct gameState* testG = newGame();
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, gardens};

	int handpos, choice1, choice2, choice3, bonus;
	handpos = choice1 = choice2 = choice3 = bonus = 0;

	int seed = 1234;

	// initialize a game state and player cards
	initializeGame(2, k, seed, testG);

	printf("Testing Card: %s", TESTCARD);

	// store old deck and hand counts
	int oldHandCount = numHandCards(testG);
	int oldDeckCount = testG->deckCount[0];

	cardEffect(smithy, choice1, choice2, choice3, testG, handpos, &bonus);

	// store new deck and hand counts
	int newHandCount = numHandCards(testG);
	int newDeckCount = testG->deckCount[0];

	// test 1 number of cards in the deck has changed
	printf("TEST 1: testing number of cards in in player's hand has changed\n");
	asserttrue(oldHandCount != newHandCount);

	// test 2 number of cards in the player's hand has changed
	printf("TEST 2: testing number of cards in in player's hand has changed\n");
	asserttrue(oldDeckCount != newDeckCount);
}

int main(int argc, char *argv[])
{
    cardtest2();
    return 0;
}
