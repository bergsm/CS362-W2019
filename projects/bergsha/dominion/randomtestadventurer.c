#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define asserttrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

#define TESTCARD "adventurer"

// adventurer card test
void randomtestadventurer()
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

    // main testing loop

        // set values of testG to random (but logical) values
        // set total supply of treasure cards to >= 2

        // store old deck and hand counts
        int oldHandCount = numHandCards(testG);
        int oldDeckCount = testG->deckCount[0];
        //TODO store discard count

        // assert the card did not fail to play
        asserttrue(cardEffect(adventurer, choice1, choice2, choice3, testG, handpos, &bonus) == 0)

        // store new deck and hand counts
        int newHandCount = numHandCards(testG);
        int newDeckCount = testG->deckCount[0];
        //TODO store discard count

        // test 1 number of cards in the deck has changed
        printf("TEST 1: testing number of cards in player's hand has changed\n");
        asserttrue(oldHandCount != newHandCount);

        // test 2 number of cards in the player's hand has changed
        printf("TEST 2: testing number of cards in deck has changed\n");
        asserttrue(oldDeckCount != newDeckCount);

        //TODO test that discard pile has changed
        // test 3 number of cards in the discard pile has changed
        printf("TEST 3: testing number of cards in deck has changed\n");
        asserttrue(oldDeckCount != newDeckCount);

        //TODO test that discard pile has changed
        // test 4 number of cards in the player's hand has increased by 2
        printf("TEST 3: testing number of cards in deck has changed\n");
        asserttrue(oldDeckCount != newDeckCount);
}

int main(int argc, char *argv[])
{
    randomtestadventurer();
    return 0;
}
