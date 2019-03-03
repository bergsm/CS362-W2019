#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "randomGame.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUMELEM(x) (sizeof(x) / sizeof((x)[0]))
#define asserttrue(bool) if(bool) printf("TEST PASSED!\n"); else printf("TEST FAILED: '" #bool "' on line %d.\n", __LINE__);

#define TESTCARD "smithy"

// smithy card test
void cardtest2()
{
	//struct gameState* testG = newGame();
	struct gameState testG;
	//int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, gardens};

	int handpos, choice1, choice2, choice3, bonus;
	handpos = choice1 = choice2 = choice3 = bonus = 0;

	//int seed = 1234;

	// initialize a game state and player cards

	printf("Testing Card: %s\n", TESTCARD);

    for (int n=0; n<2000; n++)
    {
        // initializeGame(2, k, seed, testG);
        if (randomizeGame(adventurer, &testG) != 0)
        {
            printf("Randomize unsuccessful\n");
            continue;
        }

        printf("Test #%d\n", n);
        int p = whoseTurn(&testG);

        // store old deck and hand counts
        int oldHandCount = numHandCards(&testG);
        int oldDeckCount = testG.deckCount[p];

        printf("TEST 0: testing cardEffect returns\n");

        asserttrue(cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus) == 0);

        // store new deck and hand counts
        int newHandCount = numHandCards(&testG);
        int newDeckCount = testG.deckCount[p];

        // test 1 number of cards in the deck has changed
        printf("TEST 1: testing number of cards in player's hand has changed\n");
        asserttrue(oldHandCount != newHandCount);

        // test 2 number of cards in the player's hand has changed
        printf("TEST 2: testing number of cards in deck has changed\n");
        asserttrue(oldDeckCount != newDeckCount);
    }
}

int main(int argc, char *argv[])
{
    cardtest2();
    return 0;
}
